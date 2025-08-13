#include "codegenerator.h"
#include <stdexcept>
#include <sstream>
#include <cctype>

CodeGenerator::CodeGenerator() : stackOffset(0) {}

void CodeGenerator::generate(const std::vector<FunctionInfo>& irFunctions) {
    emit(".global main");
    emit(".text");
    
    for (const auto& func : irFunctions) {
        emitFunction(func);
    }
}

std::string CodeGenerator::getAssemblyCode() const {
    return asmCode;
}

void CodeGenerator::emit(const std::string& instruction) {
    asmCode += instruction + "\n";
}

void CodeGenerator::emitPrologue(const std::string& funcName, int frameSize, int valCount) {
    std::string exitLabel = "." + funcName + "_func_end";
    currentFuncExitLabel = exitLabel;
    emit(funcName + ":");
    emit("  addi sp, sp, -" + std::to_string(frameSize));
    emit("  sw ra, " + std::to_string(frameSize-4) + "(sp)");
    for (int i = 0; i <= valCount; ++i) {
        int offset = frameSize - 8 - i * 4;
        emit("  sw s" + std::to_string(i) + ", " + std::to_string(offset) + "(sp)");
    }
    emit("  addi s0, sp, " + std::to_string(frameSize));
}

void CodeGenerator::emitEpilogue(int frameSize, int valCount) {
    emit(currentFuncExitLabel + ":");
    for (int i = 0; i <= valCount; ++i) {
        int offset = frameSize - 8 - i * 4;  // 计算每个寄存器的栈偏移
        emit("  lw s" + std::to_string(i) + ", " + std::to_string(offset) + "(sp)");
    }
    emit("  lw ra, " + std::to_string(frameSize-4) + "(sp)");
    emit("  addi sp, sp, " + std::to_string(frameSize));
    emit("  ret");
}

void CodeGenerator::emitFunction(const FunctionInfo& func) {
    // 重置标签映射
    labelMap.clear();
    usedLabels.clear();
    regAlloc.reset();
    stackOffset = 0;
    
    int tempVarSize = func.endTempCounter - func.startTempCounter;
    int paramCount = func.params.size();
    int localConut = func.varCount - paramCount;
    int valCount = (localConut > 11)?11:localConut;
    int frameSize = 4 * (2 + valCount + tempVarSize);
    // 确保栈帧大小按16字节对齐
    if (frameSize % 16 != 0) {
        frameSize += 16 - (frameSize % 16);
    }

    emitPrologue(func.name, frameSize, valCount);

    stackOffset = - 4 * (2 + valCount);

    // 处理函数参数
    for (int i = 0; i < func.params.size(); ++i) {
        const auto& param = func.params[i];
        std::string paramName = param->toString();

        if (i < 8) {
            // 将参数寄存器绑定到变量
            regAlloc.allocateReg(paramName, OperandType::PARAM);
        } else {
            // 超过8个的参数通过栈传递
            int paramStackOffset = (func.params.size() - 1 - i) * 4;
            varStackMap[paramName] = paramStackOffset;
        }
    }
    
    // 生成函数体指令
    for (const auto& inst : func.instructions) {
        switch (inst.opcode) {
            case IROpcode::ASSIGN: generateAssignment(inst); break;
            case IROpcode::ADD: case IROpcode::SUB: case IROpcode::MUL: 
            case IROpcode::DIV: case IROpcode::MOD: generateArithmetic(inst); break;
            case IROpcode::AND: case IROpcode::OR: case IROpcode::NOT: 
            case IROpcode::LT: case IROpcode::GT: case IROpcode::LE: 
            case IROpcode::GE: case IROpcode::EQ: case IROpcode::NE: generateComparison(inst); break;
            case IROpcode::GOTO: case IROpcode::IF_GOTO: case IROpcode::LABEL: generateControlFlow(inst); break;
            case IROpcode::CALL: generateFunctionCall(inst); break;
            case IROpcode::PARAM: generateParam(inst); break;
            case IROpcode::RETURN: generateReturn(inst); break;
            default: break;
        }
    }
    
    emitEpilogue(frameSize, valCount);
}

void CodeGenerator::generateAssignment(const IRInstruction& inst) {
    AllocationResult regResult = regAlloc.allocateReg(inst.result->toString(), inst.result->type);
    std::string destReg = regResult.reg;
    spillReg(regResult);
    
    if (inst.arg1->type == OperandType::CONSTANT) {
        emit("  li " + destReg + ", " + inst.arg1->toString());
    } else {
        std::string srcReg = getRegorLoad(inst.arg1); // 获取源操作数的寄存器
        if (srcReg != destReg) {
            emit("  mv " + destReg + ", " + srcReg);
        }
        if(inst.arg1->type == OperandType::TEMP) regAlloc.freeReg(inst.arg1->toString());
    }

}

void CodeGenerator::generateArithmetic(const IRInstruction& inst) {
    std::string op;

    switch (inst.opcode) {
        case IROpcode::ADD: op = "add"; break;
        case IROpcode::SUB: op = "sub"; break;
        case IROpcode::MUL: op = "mul"; break;
        case IROpcode::DIV: op = "div"; break;
        case IROpcode::MOD: op = "rem"; break; 
        default: throw std::runtime_error("Unsupported arithmetic operator");;
    }

    std::string rs1 = getRegorLoad(inst.arg1);
    std::string rs2;
    if(inst.arg2->type==OperandType::CONSTANT){
        AllocationResult regResult = regAlloc.allocateReg(inst.arg2->toString(), inst.arg2->type);
        std::string tempReg = regResult.reg;
        spillReg(regResult);
        emit("  li " + tempReg + ", " + inst.arg2->toString());
        rs2 = tempReg;
    }
    else{
        rs2 = getRegorLoad(inst.arg2);
    }
    AllocationResult regResult = regAlloc.allocateReg(inst.result->toString(), inst.result->type);
    std::string rd = regResult.reg;
    spillReg(regResult);

    emit("  " + op + " " + rd + ", " + rs1 + ", " + rs2);

    if(inst.arg1->type == OperandType::TEMP) regAlloc.freeReg(inst.arg1->toString());
    if(inst.arg2->type == OperandType::TEMP) regAlloc.freeReg(inst.arg2->toString());
}

void CodeGenerator::generateControlFlow(const IRInstruction& inst) {
    switch (inst.opcode) {
        case IROpcode::LABEL: {
            std::string validLabel = generateValidLabel(inst.label);
            emit(validLabel + ":");
            break;
        }
        case IROpcode::GOTO: {
            std::string validLabel = generateValidLabel(inst.label);
            emit("  j " + validLabel);
            break;
        }
        case IROpcode::IF_GOTO: {
            std::string condReg = getRegorLoad(inst.arg1);;
            std::string validLabel = generateValidLabel(inst.label);
            emit("  bnez " + condReg + ", " + validLabel);
            if(inst.arg1->type == OperandType::TEMP) regAlloc.freeReg(inst.arg1->toString());
            break;
        }
        default: break;
    }
}

bool isNumber(std::string arg){
    // 判断参数是否为数字（整数）
    bool isNumber = true;
    // 允许负数（首字符为'-'且后面跟数字）
    int start = 0;
    if (arg[0] == '-') {
        start = 1;
        if (arg.size() == 1) { // 单独的负号不是有效数字
            isNumber = false;
        }
    }
    // 检查剩余字符是否都是数字
    for (int j = start; j < arg.size(); ++j) {
        if (!isdigit(arg[j])) {
           isNumber = false;
                break;
        }
    }
    return isNumber;
}

void CodeGenerator::generateFunctionCall(const IRInstruction& inst) {
    std::vector<std::string> callerSaved = {
        "t0", "t1", "t2", "t3", "t4", "t5", "t6",
        "a0", "a1", "a2", "a3", "a4", "a5", "a6", "a7"
    };

    std::vector<std::string> savedRegisters;
    for (const auto& reg : callerSaved) {
        if (regAlloc.isRegInUse(reg)) {
            savedRegisters.push_back(reg);
        }
    }

    int paramCount = paramStrings.size(); 
    int regParamCount = std::min(paramCount, 8); // 前8个参数用a0-a7
    int stackParamCount = std::max(0, paramCount - 8); // 超过8个的参数用栈传递
    int stackParamSize = stackParamCount * 4;
    int saveRegSize = savedRegisters.size() * 4;
    int totalStackNeed = saveRegSize + stackParamSize;
    int alignPadding = (16 - (totalStackNeed % 16)) % 16;
    int totalStackSize = totalStackNeed + alignPadding;

    if (totalStackSize > 0) {
        emit("  addi sp, sp, -" + std::to_string(totalStackSize));
    }

    // 保存调用者寄存器到栈
    int offset = alignPadding;
    for (const auto& reg : savedRegisters) {
        offset += 4;
        // 栈是向下增长的，保存地址 = sp + (totalStackSize - offset)
        emit("  sw " + reg + ", " + std::to_string(totalStackSize - offset) + "(sp)");
    }

    // 寄存器参数（a0-a7）
    for (int i = 0; i < regParamCount; ++i) {
        const auto& arg = paramStrings[i];
        std::string destReg = "a" + std::to_string(i); // 目标参数寄存器a0-a7
        Operand operand={OperandType::VARIABLE,"",-1};
        std::string actualArg = arg; // 存储处理后的参数名
        if (arg[0] == 't') {
            operand.type = OperandType::TEMP;
            actualArg = arg.substr(1); // 去掉前面的't'
        } else {
            operand.type = OperandType::VARIABLE;
        }
        operand = {operand.type, actualArg, -1}; // 使用处理后的参数名
        if (isNumber(arg)) {
            // 数字常量使用li指令
            emit("  li " + destReg + ", " + arg);
        } else {
            // 变量/标识符使用mv指令（从其绑定的寄存器移动）
            std::shared_ptr<Operand> operandPtr = std::make_shared<Operand>(operand);
            std::string srcReg = getRegorLoad(operandPtr);
            emit("  mv " + destReg + ", " + srcReg);
        }
    }

    // 栈参数
    for (int i = 0; i < stackParamCount; ++i) {
        int stackParamOffset = (stackParamCount - 1 - i) * 4;
        const auto& arg = paramStrings[8 + i];
        std::string argReg;
        Operand operand={OperandType::VARIABLE,"",-1};
        std::string actualArg = arg; // 存储处理后的参数名
        if (arg[0] == 't') {
            operand.type = OperandType::TEMP;
            actualArg = arg.substr(1); // 去掉前面的't'
        } else {
            operand.type = OperandType::VARIABLE;
        }
        operand = {operand.type, actualArg, -1}; // 使用处理后的参数名
        if (isNumber(arg)) {
            // 数字常量使用li指令
            AllocationResult regResult = regAlloc.allocateReg(arg, OperandType::CONSTANT);
            argReg = regResult.reg;
            spillReg(regResult);
            emit("  li " + argReg + ", " + arg);
        } else {
            // 变量/标识符使用mv指令（从其绑定的寄存器移动）
            std::shared_ptr<Operand> operandPtr = std::make_shared<Operand>(operand);
            std::string srcReg = getRegorLoad(operandPtr);
            AllocationResult regResult = regAlloc.allocateReg(arg, OperandType::TEMP);
            argReg = regResult.reg;
            spillReg(regResult);
            emit("  mv " + argReg + ", " + srcReg);
        }
        emit("  sw " + argReg + ", " + std::to_string(stackParamOffset) + "(sp)");
        if(inst.arg1->type == OperandType::TEMP) regAlloc.freeReg(arg);
    }

    resetParamStrings();
    std::string funcName = inst.arg1->toString();
    emit("  call " + funcName);

    if (inst.result) {
        AllocationResult regResult = regAlloc.allocateReg(inst.result->toString(), inst.result->type);
        std::string destReg = regResult.reg;
        spillReg(regResult);
        emit("  mv " + destReg + ", a0"); // 将a0的值移动到结果寄存器
    }

    int index = savedRegisters.size() - 1;  // 从最后保存的寄存器开始恢复
    for (auto it = savedRegisters.rbegin(); it != savedRegisters.rend(); ++it, --index) {
        // 计算该寄存器保存时的偏移量（与保存阶段完全一致）
        int restoreOffset = alignPadding + 4 * (index + 1);
        emit("  lw " + *it + ", " + std::to_string(totalStackSize - restoreOffset) + "(sp)");
    }

    if (totalStackSize > 0) {
        emit("  addi sp, sp, " + std::to_string(totalStackSize));
    }

}

// 重置参数计数器（在函数调用前调用）
void CodeGenerator::resetParamCounter() {
    paramCounter = 0;
}

// 处理param指令
void CodeGenerator::generateParam(const IRInstruction& inst) {
    if (!inst.arg1) return;
    std::string paramStr = inst.arg1->toString();
    paramStrings.push_back(paramStr);
    paramCounter++;
}

void CodeGenerator::generateReturn(const IRInstruction& inst) {
    if (inst.arg1) {
        if(inst.arg1->type==OperandType::CONSTANT){
            emit("  li a0, " + inst.arg1->toString());
        }
        else{
            std::string retReg = getRegorLoad(inst.arg1);
            emit("  mv a0, " + retReg);
            regAlloc.freeReg(inst.arg1->toString());
        }
    }
    emit("  j " + currentFuncExitLabel);  // 跳转到函数统一退出标签
}

void CodeGenerator::generateComparison(const IRInstruction& inst) {

    // 处理NOT单目运算
    if (inst.opcode == IROpcode::NOT) {
        std::string rs1 = getRegorLoad(inst.arg1);
        AllocationResult regResult = regAlloc.allocateReg(inst.result->toString(), inst.result->type);
        std::string rd = regResult.reg;
        spillReg(regResult);
        
        // 逻辑非：将非0值变为0，0变为1
        emit("  mv " + rd + ", " + rs1);
        emit("  xori " + rd + ", " + rd + ", 1");  // 异或1实现取反
        emit("  andi " + rd + ", " + rd + ", 1");  // 确保结果只有0或1
        
        if (inst.arg1->type == OperandType::TEMP) 
            regAlloc.freeReg(inst.arg1->toString());
        return;
    }

    std::string rs1 = getRegorLoad(inst.arg1);
    std::string rs2 = getRegorLoad(inst.arg2);
    AllocationResult regResult = regAlloc.allocateReg(inst.result->toString(),inst.result->type);
    std::string rd = regResult.reg;
    spillReg(regResult);
    
    switch (inst.opcode) {
        case IROpcode::LT: 
            emit("  slt " + rd + ", " + rs1 + ", " + rs2);
            break;
        case IROpcode::GT: 
            emit("  slt " + rd + ", " + rs2 + ", " + rs1);
            break;
        case IROpcode::LE: 
            emit("  slt " + rd + ", " + rs2 + ", " + rs1);
            emit("  xori " + rd + ", " + rd + ", 1");
            break;
        case IROpcode::GE:
            emit("  slt " + rd + ", " + rs1 + ", " + rs2);
            emit("  xori " + rd + ", " + rd + ", 1");
            break;
        case IROpcode::EQ:
            emit("  xor " + rd + ", " + rs1 + ", " + rs2);
            emit("  seqz " + rd + ", " + rd);
            break;
        case IROpcode::NE:
            emit("  xor " + rd + ", " + rs1 + ", " + rs2);
            emit("  snez " + rd + ", " + rd);
            break;
            case IROpcode::AND:
            // 逻辑与：两边都非0则结果为1
            emit("  and " + rd + ", " + rs1 + ", " + rs2);    // 按位与
            emit("  snez " + rd + ", " + rd);                // 非零则置1
            break;
        case IROpcode::OR:
            // 逻辑或：任一边非0则结果为1
            emit("  or " + rd + ", " + rs1 + ", " + rs2);     // 按位或
            emit("  snez " + rd + ", " + rd);                // 非零则置1
            break;
        default:
            throw std::runtime_error("Unsupported comparison operator");
    }

    if(inst.arg1->type == OperandType::TEMP) regAlloc.freeReg(inst.arg1->toString());
    if(inst.arg2->type == OperandType::TEMP) regAlloc.freeReg(inst.arg2->toString());
    
}

// 标签管理方法
std::string CodeGenerator::generateValidLabel(const std::string& irLabel) {
    // 如果已经映射过，直接返回
    if (labelMap.count(irLabel)) {
        return labelMap[irLabel];
    }
    
    // 生成有效的汇编标签
    std::string validLabel = sanitizeLabel(irLabel);
    
    // 确保标签唯一性
    int counter = 1;
    std::string finalLabel = validLabel;
    while (usedLabels.count(finalLabel)) {
        finalLabel = validLabel + "_" + std::to_string(counter++);
    }
    
    // 记录使用的标签
    usedLabels.insert(finalLabel);
    labelMap[irLabel] = finalLabel;
    
    return finalLabel;
}

std::string CodeGenerator::sanitizeLabel(const std::string& label) {
    std::string sanitized = "L_" + label;
    
    // 移除或替换无效字符
    for (char& c : sanitized) {
        if (!std::isalnum(c) && c != '_') {
            c = '_';
        }
    }
    
    // 确保不以数字开头
    if (!sanitized.empty() && std::isdigit(sanitized[0])) {
        sanitized = "L_" + sanitized;
    }
    
    return sanitized;
}

bool CodeGenerator::isValidLabel(const std::string& label) {
    if (label.empty()) return false;
    
    // 检查是否以字母或下划线开头
    if (!std::isalpha(label[0]) && label[0] != '_') {
        return false;
    }
    
    // 检查是否只包含字母、数字和下划线
    for (char c : label) {
        if (!std::isalnum(c) && c != '_') {
            return false;
        }
    }
    
    return true;
}

std::string CodeGenerator::getRegorLoad(const std::shared_ptr<Operand> operand) {
    if (!operand) {
        throw std::runtime_error("Invalid null operand in getRegorLoad");
    }

    // 处理常量：直接分配寄存器并加载值
    if (operand->type == OperandType::CONSTANT) {
        AllocationResult regResult = regAlloc.allocateReg("const_" + operand->toString(), operand->type);
        std::string reg = regResult.reg;
        spillReg(regResult);
        emit("  li " + reg + ", " + operand->toString());
        return reg;
    }

    std::string operandStr = operand->toString();
    
    // 尝试获取已分配的寄存器
    if (regAlloc.isInReg(operandStr)) {
        return regAlloc.getReg(operandStr);
    }

    // std::string error_reg="finding vartoReg: " + operandStr + "\n";
    // for (const auto& [varName, info] : regAlloc.getVarInfoMap()) {
    //     error_reg+=" varName: "+varName+", reg: "+info.reg+"\n";
    // }
    // std::cout<<error_reg;

    // 不在寄存器中，从栈加载
    AllocationResult regResult = regAlloc.allocateReg(operandStr, OperandType::TEMP);
    std::string tempReg = regResult.reg;
    spillReg(regResult);
    int offset = varStackMap[operandStr];
    emit("  lw " + tempReg + ", " + std::to_string(offset) + "(s0)");
    
    return tempReg;
}

void CodeGenerator::spillReg(AllocationResult result){
    // 检查是否有需要溢出到栈的寄存器
    if (result.spill.varName=="") {
        return;
    }

    int offset = stackOffset;
    stackOffset -= 4;
    emit("  sw " + result.spill.reg + ", " + std::to_string(offset) + "(s0)");
    varStackMap[result.spill.varName] = offset;
}