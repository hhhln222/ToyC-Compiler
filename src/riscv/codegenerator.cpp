#include "codegenerator.h"
#include <stdexcept>
#include <sstream>
#include <cctype>

CodeGenerator::CodeGenerator() : stackOffset(0) {
    // 尝试打开日志文件，以追加模式打开，不存在则创建
    logFile.open("RegAndStackLog.txt", std::ios::out | std::ios::trunc);
}

// 析构函数：关闭日志文件
CodeGenerator::~CodeGenerator() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

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

void CodeGenerator::emitPrologue(const std::string& funcName, int frameSize) {
    std::string exitLabel = funcName + "_func_end";
    currentFuncExitLabel = exitLabel;
    emit(funcName + ":");
    logFile<<funcName + ":"<<std::endl;
    emit("  addi sp, sp, -" + std::to_string(frameSize));
    
    // 保存返回地址ra
    emit("  sw ra, " + std::to_string(frameSize - 4) + "(sp)");
    
    // 保存s0寄存器
    emit("  sw s0, " + std::to_string(frameSize - 8) + "(sp)");
    
    emit("  addi s0, sp, " + std::to_string(frameSize));
}

void CodeGenerator::emitEpilogue(int frameSize) {
    
    // 恢复s0寄存器
    emit("  lw s0, " + std::to_string(frameSize - 8) + "(sp)");
    
    // 恢复返回地址ra
    emit("  lw ra, " + std::to_string(frameSize - 4) + "(sp)");
    
    emit("  addi sp, sp, " + std::to_string(frameSize));
    emit("  ret");
}

void CodeGenerator::emitFunction(const FunctionInfo& func) {
    // 重置标签映射
    labelMap.clear();
    usedLabels.clear();
    regAlloc.reset();
    varStackMap.clear();
    paramStrings.clear();
    stackOffset = 0;
    
    int tempVarSize = func.tempVarCount;
    int paramCount = func.params.size();
    int varCount = func.varCount - paramCount; // 有效变量数量（排除参数）

    // 判断当前函数是否为main
    bool isMainFunction = (func.name == "main");
    
    std::vector<int> usedSRegisters;
    std::map<std::string, std::string> sRegToVar; // 记录s寄存器到变量的映射

    // 非main函数才处理s寄存器保存（根据变量数量决定保存哪些）
    if (!isMainFunction) {
        // 计算需要保存的s寄存器数量：最多11个（s1-s11），最少为变量数量
        int sRegNeedCount = std::min(varCount, 11);
        // 若变量数量超过11，则保存全部s1-s11
        if (varCount > 11) {
            sRegNeedCount = 11;
        }

        // 生成需要保存的s寄存器列表（s1到sN，N为需要的数量）
        for (int i = 1; i <= sRegNeedCount; ++i) {
            usedSRegisters.push_back(i);
        }

        // 记录这些s寄存器与变量的绑定关系
        for (int i : usedSRegisters) {
            std::string reg = "s" + std::to_string(i);
            // 查找该寄存器绑定的变量
            for (const auto& [var, info] : regAlloc.getVarInfoMap()) {
                if (info.reg == reg) {
                    sRegToVar[reg] = var;
                    regAlloc.freeReg(var); // 临时解除绑定
                    break;
                }
            }
        }
    }

    // 计算栈帧大小：ra(4) + s0(4) + 需保存的s寄存器*4 + 普通变量*4 + 临时变量*4
    int frameSize = 4 * (2 + 
                         (!isMainFunction ? usedSRegisters.size() : 0) + 
                         varCount +  // 新增：普通变量空间
                         tempVarSize);
    // 确保栈帧按16字节对齐
    if (frameSize % 16 != 0) {
        frameSize += 16 - (frameSize % 16);
    }
    
    emitPrologue(func.name, frameSize);

    // 非main函数保存s寄存器到栈
    if (!isMainFunction) {
        int offset = frameSize - 12; 
        for (int reg : usedSRegisters) {
            emit("  sw s" + std::to_string(reg) + ", " + std::to_string(offset) + "(sp)");
            offset -= 4;
        }
    }

    // 计算普通变量的栈偏移基准（从栈帧底部向上分配）
    // 偏移计算：跳过ra(4)、s0(4)、保存的s寄存器(usedSRegisters.size()*4)
    int varBaseOffset = -4 * (2 + usedSRegisters.size()) - 4;
    
    // (假设func.normalVarIds)
    for (const std::string& var : func.normalVarIds) {
        varStackMap[var] = varBaseOffset;  // 记录变量到偏移的映射
        varBaseOffset -= 4;  // 每个变量占4字节（32位）
    }
    
    // 更新栈偏移指针（跳过普通变量区域）
    stackOffset = varBaseOffset;

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

    emit(currentFuncExitLabel + ":");

    // 非main函数恢复s寄存器并重建绑定
    if (!isMainFunction) {
        int offset = frameSize - 12;
        for (int reg : usedSRegisters) {
            std::string regStr = "s" + std::to_string(reg);
            emit("  lw " + regStr + ", " + std::to_string(offset) + "(sp)");
            offset -= 4;

            // 恢复后重建变量与寄存器的绑定
            if (sRegToVar.count(regStr)) {
                std::string var = sRegToVar.at(regStr);
                regAlloc.bindVarToReg(var, regStr);
            }
        }
    }
    
    emitEpilogue(frameSize);
}

void CodeGenerator::generateAssignment(const IRInstruction& inst) {
    std::string destReg = getRegorLoad(inst.result);
    std::string destVar = inst.result->toString();
    OperandType destType = inst.result->type;

    // 处理常量赋值：直接使用li指令加载
    if (inst.arg1 && inst.arg1->isConstant()) {
        int constantValue = inst.arg1->getConstantValue();
        // 生成li指令加载常量到目标寄存器
        emit("  li " + destReg + ", " + std::to_string(constantValue));
        
        // 处理变量的栈写回（与之前逻辑一致）
        if (destType == OperandType::VARIABLE && varStackMap.count(destVar)) {
            int offset = varStackMap[destVar];
            emit("  sw " + destReg + ", " + std::to_string(offset) + "(s0)");

            if (!varInitialized[destVar]) {
                logFile << "变量 '" << destVar << "' 首次赋值(常量)，初始化栈偏移: " << offset << std::endl;
                varInitialized[destVar] = true;
            } else {
                logFile << "变量 '" << destVar << "' 后续赋值(常量)，更新栈偏移: " << offset << std::endl;
            }

            regAlloc.freeReg(destVar);
        }
        return; // 常量处理完毕，直接返回
    }

    // 非常量赋值：原有逻辑
    std::string srcReg = getRegorLoad(inst.arg1);
    std::string srcVar = inst.arg1 ? inst.arg1->toString() : "";

    // 执行寄存器间赋值
    if (srcReg != destReg) {
        emit("  mv " + destReg + ", " + srcReg);
    }

    // 处理普通变量的栈写回
    if (destType == OperandType::VARIABLE && varStackMap.count(destVar)) {
        int offset = varStackMap[destVar];
        emit("  sw " + destReg + ", " + std::to_string(offset) + "(s0)");

        if (!varInitialized[destVar]) {
            logFile << "变量 '" << destVar << "' 首次赋值，初始化栈偏移: " << offset << std::endl;
            varInitialized[destVar] = true;
        } else {
            logFile << "变量 '" << destVar << "' 后续赋值，更新栈偏移: " << offset << std::endl;
        }

        regAlloc.freeReg(destVar);
    }

    // 处理源操作数的寄存器释放
    if (inst.arg1) {
        if (inst.arg1->isConstant()) {
            regAlloc.freeReg(srcVar);
        } else if (inst.arg1->type == OperandType::VARIABLE && varStackMap.count(srcVar)) {
            regAlloc.freeReg(srcVar);
        }
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
    std::string rs2 = getRegorLoad(inst.arg2);
    std::string rd = getRegorLoad(inst.result);
    std::string rs1Var = inst.arg1->toString();
    std::string rs2Var = inst.arg2->toString();
    std::string rdVar = inst.result->toString();

    emit("  " + op + " " + rd + ", " + rs1 + ", " + rs2);
    
    // 处理结果为栈中普通变量的情况：写回栈中
    if (inst.arg1->type == OperandType::VARIABLE && varStackMap.count(rs1Var)) {
        // 释放临时寄存器
        regAlloc.freeReg(rs1Var);
    }

    if (inst.arg2->type == OperandType::VARIABLE && varStackMap.count(rs2Var)) {
        // 释放临时寄存器
        regAlloc.freeReg(rs2Var);
    }

    // 处理结果为栈中普通变量的情况：写回栈中
    if (inst.result->type == OperandType::VARIABLE && varStackMap.count(rdVar)) {
        int offset = varStackMap[rdVar];
        // 写回栈中
        emit("  sw " + rd + ", " + std::to_string(offset) + "(s0)");
        // 释放临时寄存器
        regAlloc.freeReg(rdVar);
    }

    // 释放常量寄存器
    if(inst.arg1 && inst.arg1->isConstant()) {
        regAlloc.freeReg(inst.arg1->toString());
    }
    if(inst.arg2 && inst.arg2->isConstant()) {
        regAlloc.freeReg(inst.arg2->toString());
    }
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
            std::string rs1Var = inst.arg1->toString();
        
            if (inst.arg1->type == OperandType::VARIABLE && varStackMap.count(rs1Var)) {
                regAlloc.freeReg(rs1Var);
            }
            if(inst.arg1->isConstant()) regAlloc.freeReg(inst.arg1->toString());
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
        "a0","a1", "a2", "a3", "a4", "a5", "a6", "a7"
    };

    logFile << inst.arg1->toString() + "函数调用准备：" << std::endl;

    std::string destReg;
    if (inst.result) {
        destReg = getRegorLoad(inst.result);
    }

    std::vector<std::string> savedRegisters;
    for (const auto& reg : callerSaved) {
        if (regAlloc.isRegInUse(reg) && reg != destReg) {
            savedRegisters.push_back(reg);
        }
    }

    int paramCount = paramStrings.size(); 
    int regParamCount = std::min(paramCount, 8);
    int stackParamCount = std::max(0, paramCount - 8);
    int stackParamSize = stackParamCount * 4;
    int saveRegSize = savedRegisters.size() * 4;
    int totalStackNeed = saveRegSize + stackParamSize;
    int alignPadding = (16 - (totalStackNeed % 16)) % 16;
    int totalStackSize = totalStackNeed + alignPadding;

    if (totalStackSize > 0) {
        emit("  addi sp, sp, -" + std::to_string(totalStackSize));
    }

    // 保存调用者寄存器到栈，并记录寄存器到变量的映射
    int offset = alignPadding;
    std::map<std::string, std::string> regToVar;
    for (const auto& reg : savedRegisters) {
        // 保存寄存器值到栈
        offset += 4;
        emit("  sw " + reg + ", " + std::to_string(totalStackSize - offset) + "(sp)");
    }

    // 处理寄存器参数（a0-a7）
    for (int i = 0; i < regParamCount; ++i) {
        const auto& arg = paramStrings[i];
        std::string destReg = "a" + std::to_string(i);
        std::shared_ptr<Operand> operand;
        
        if (isNumber(arg)) {
            operand = std::make_shared<Operand>(OperandType::CONSTANT, arg, -1);
        } else if (arg[0] == 't') {
            operand = std::make_shared<Operand>(OperandType::TEMP, arg.substr(1), -1);
        } else {
            operand = std::make_shared<Operand>(OperandType::VARIABLE, arg, -1);
        }
        
        if (isNumber(arg)) {
            emit("  li " + destReg + ", " + arg);
            regAlloc.freeReg(arg);
        } else {
            std::string srcReg = getRegorLoad(operand);
            emit("  mv " + destReg + ", " + srcReg);
            
            if (operand->type == OperandType::VARIABLE && varStackMap.count(arg)) {
                regAlloc.freeReg(arg);
            }
        }
    }

    // 处理栈参数
    for (int i = 0; i < stackParamCount; ++i) {
        int stackParamOffset = (stackParamCount - 1 - i) * 4;
        const auto& arg = paramStrings[8 + i];
        std::shared_ptr<Operand> operand;
        
        if (isNumber(arg)) {
            operand = std::make_shared<Operand>(OperandType::CONSTANT, arg, -1);
        } else if (arg[0] == 't') {
            operand = std::make_shared<Operand>(OperandType::TEMP, arg.substr(1), -1);
        } else {
            operand = std::make_shared<Operand>(OperandType::VARIABLE, arg, -1);
        }

        std::string argReg = getRegorLoad(operand);
        emit("  sw " + argReg + ", " + std::to_string(stackParamOffset) + "(sp)");
        
        if (operand->type == OperandType::VARIABLE && varStackMap.count(arg)) {
            regAlloc.freeReg(arg);
        }
        if (isNumber(arg)) {
            regAlloc.freeReg(arg);
        }
    }

    resetParamStrings();
    std::string funcName = inst.arg1->toString();
    emit("  call " + funcName);

    if (inst.result) {
        regAlloc.bindVarToReg(inst.result->toString(),destReg);
        emit("  mv " + destReg + ", a0");
    }

    // 恢复寄存器并重建绑定
    int index = savedRegisters.size() - 1;
    for (auto it = savedRegisters.rbegin(); it != savedRegisters.rend(); ++it, --index) {
        int restoreOffset = alignPadding + 4 * (index + 1);
        emit("  lw " + *it + ", " + std::to_string(totalStackSize - restoreOffset) + "(sp)");
    }

    if (totalStackSize > 0) {
        emit("  addi sp, sp, " + std::to_string(totalStackSize));
    }

    logFile << inst.arg1->toString() + "函数调用结束：" << std::endl;
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
        if(inst.arg1->isConstant()){
            // 直接生成li指令加载常量
            emit("  li a0, " + inst.arg1->toString());
        } else {
            std::string retReg = getRegorLoad(inst.arg1);
            std::string retVar = inst.arg1->toString();
            emit("  mv a0, " + retReg);
            if (inst.arg1->type == OperandType::VARIABLE && varStackMap.count(retVar)) {
                // 释放临时寄存器
                regAlloc.freeReg(retReg);
            }
        }
    }
    emit("  j " + currentFuncExitLabel);
}

void CodeGenerator::generateComparison(const IRInstruction& inst) {

    // 处理NOT单目运算
    if (inst.opcode == IROpcode::NOT) {
        std::string rs1 = getRegorLoad(inst.arg1);
        std::string rd = getRegorLoad(inst.result);
        std::string srcVar = inst.arg1->toString();
        std::string destVar = inst.result->toString();
    
        // 逻辑非：将非0值变为0，0变为1
        emit("  mv " + rd + ", " + rs1);
        emit("  xori " + rd + ", " + rd + ", 1");  // 异或1实现取反
        emit("  andi " + rd + ", " + rd + ", 1");  // 确保结果只有0或1
        
        // 处理结果为栈中普通变量的情况：写回栈中
        if (inst.arg1->type == OperandType::VARIABLE && varStackMap.count(srcVar)) {
            // 释放临时寄存器
            regAlloc.freeReg(srcVar);
        }

        // 处理结果为栈中普通变量的情况：写回栈中
        if (inst.result->type == OperandType::VARIABLE && varStackMap.count(destVar)) {
            int offset = varStackMap[srcVar];
            // 写回栈中
            emit("  sw " + rd + ", " + std::to_string(offset) + "(s0)");
            // 释放临时寄存器
            regAlloc.freeReg(srcVar);
        }
        if(inst.arg1->isConstant()) regAlloc.freeReg(inst.arg1->toString());
        return;
    }

    std::string rs1 = getRegorLoad(inst.arg1);
    std::string rs2 = getRegorLoad(inst.arg2);
    std::string rd = getRegorLoad(inst.result);
    std::string rs1Var = inst.arg1->toString();
    std::string rs2Var = inst.arg2->toString();
    std::string rdVar = inst.result->toString();
    
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

    if (inst.arg1->type == OperandType::VARIABLE && varStackMap.count(rs1Var)) {
        regAlloc.freeReg(rs1Var);
    }

    if (inst.arg2->type == OperandType::VARIABLE && varStackMap.count(rs2Var)) {
        regAlloc.freeReg(rs2Var);
    }

    // 处理结果为栈中普通变量的情况：写回栈中
    if (inst.result->type == OperandType::VARIABLE && varStackMap.count(rdVar)) {
        int offset = varStackMap[rdVar];
        // 写回栈中
        emit("  sw " + rd + ", " + std::to_string(offset) + "(s0)");
        // 释放临时寄存器
        regAlloc.freeReg(rdVar);
    }

    // 释放常量寄存器
    if(inst.arg1 && inst.arg1->isConstant()) {
        regAlloc.freeReg(inst.arg1->toString());
    }
    if(inst.arg2 && inst.arg2->isConstant()) {
        regAlloc.freeReg(inst.arg2->toString());
    }
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

// 辅助函数：判断是否为临时变量（假设以't'开头）
bool isTempVar(const std::string& var) {
    return !var.empty() && var[0] == 't';
}

// 栈分配逻辑（spillReg）：相同名称的临时变量复用同一偏移
void CodeGenerator::spillReg(AllocationResult result) {
    if (!result.isSpill) return;
    std::string var = result.spill.varName;
    if (isNumber(var)) return;

    // 普通变量：固定分配，不复用（沿用之前逻辑）
    if (!isTempVar(var)) {
        if (varStackMap.count(var)) {
            logRegisterSpill(var, result.spill.reg, varStackMap[var]);
            return; // 已分配则跳过
        }
        stackOffset -= 4;
        varStackMap[var] = stackOffset;
        logRegisterSpill(var, result.spill.reg, stackOffset);
        emit("  sw " + result.spill.reg + ", " + std::to_string(stackOffset) + "(s0)");
        return;
    }

    // 临时变量：按名称复用（核心逻辑）
    if (varStackMap.count(var)) {
        // 同名临时变量已存在，直接复用其偏移
        int offset = varStackMap[var];
        logRegisterSpill(var, result.spill.reg, offset);
        emit("  sw " + result.spill.reg + ", " + std::to_string(offset) + "(s0)");
    } else {
        // 新临时变量，首次分配并记录偏移
        stackOffset -= 4;
        varStackMap[var] = stackOffset;
        logRegisterSpill(var, result.spill.reg, stackOffset);
        emit("  sw " + result.spill.reg + ", " + std::to_string(stackOffset) + "(s0)");
    }
}

std::string CodeGenerator::getRegorLoad(const std::shared_ptr<Operand> operand) {
    if (!operand) {
        throw std::runtime_error("getRegorLoad: 空操作数");
    }

    std::string var = operand->toString();
    OperandType opType = operand->type;

    // 1. 已在寄存器中，直接返回
    if (regAlloc.isInReg(var)) {
        std::string reg = regAlloc.getReg(var);
        logFile << "变量 '" << var << "' 已在寄存器: " << reg << std::endl;
        return reg;
    }

    // 处理普通变量（已预分配栈空间）
    if (opType == OperandType::VARIABLE) {
        if (!varStackMap.count(var)) {
            throw std::runtime_error("变量 '" + var + "' 未预分配栈空间");
        }

        if (varStackMap.count(var)&&varStackMap[var]>=0) {
            AllocationResult alloc = regAlloc.allocateReg(var, OperandType::TEMP);
            spillReg(alloc);
            int offset = varStackMap[var];
            emit("  lw " + alloc.reg + ", " + std::to_string(offset) + "(s0)");
            logFile << "参数 '" << var << "' 分配寄存器: " << alloc.reg << std::endl;
            return alloc.reg;
        }

        AllocationResult alloc = regAlloc.allocateReg(var, opType);
        spillReg(alloc);
        std::string reg = alloc.reg;

        // 判断是否为首次使用（未初始化）
        if (!varInitialized[var]) { 
            logFile << "变量 '" << var << "' 首次使用，分配寄存器: " << reg << std::endl;
            return reg; // 首次使用不加载，等待赋值初始化
        } else {
            // 非首次使用，从栈加载
            int offset = varStackMap[var];
            emit("  lw " + reg + ", " + std::to_string(offset) + "(s0)");
            logFile << "变量 '" << var << "' 从栈偏移 " << offset << " 加载到寄存器: " << reg << std::endl;
            return reg;
        }
    }

    // 4. 处理临时变量
    if (operand->isTEMP()) {
        AllocationResult alloc = regAlloc.allocateReg(var, OperandType::TEMP);
        spillReg(alloc);
        if (varStackMap.count(var)) {
            int offset = varStackMap[var];
            emit("  lw " + alloc.reg + ", " + std::to_string(offset) + "(s0)");
            logFile << "参数 '" << var << "' 分配寄存器: " << alloc.reg << std::endl;
            return alloc.reg;
        }
        logFile << "临时变量 '" << var << "' 分配寄存器: " << alloc.reg << std::endl;
        return alloc.reg;
    }

    // 5. 处理常量
    if (operand->isConstant()) {
        AllocationResult alloc = regAlloc.allocateReg(var, OperandType::CONSTANT);
        spillReg(alloc);
        emit("  li " + alloc.reg + ", " + var);
        logFile << "常量 '" << var << "' 加载到寄存器: " << alloc.reg << std::endl;
        return alloc.reg;
    }

    // 未知类型处理
    throw std::runtime_error("getRegorLoad: 不支持的操作数类型 - " + var);
}

// 寄存器溢出日志函数实现
void CodeGenerator::logRegisterSpill(const std::string& var, 
                                    const std::string& reg, 
                                    int stackOffset) {
    if (!logFile.is_open()) {
        return;
    }
    if(!isTempVar(var)){
        if(varStackMap.count(var)){
            logFile << "普通变量 '" << var <<  " 在栈中，栈偏移: " << stackOffset << std::endl;
        }
        logFile << "普通变量 '" << var << "' 从寄存器 " << reg  << " 溢出到栈偏移: " << stackOffset << std::endl;
    }

    if(varStackMap.count(var)){
        logFile << "临时变量 '" << var <<  " 在栈中，栈偏移: " << stackOffset << std::endl;
    }
    logFile << "临时变量 '" << var << "' 从寄存器 " << reg  << " 溢出到栈偏移: " << stackOffset << std::endl;
    
}