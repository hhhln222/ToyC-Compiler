#include "codegenerator.h"
#include <stdexcept>
#include <sstream>
#include <cctype>

CodeGenerator::CodeGenerator() : stackOffset(0) {}

void CodeGenerator::generate(const std::vector<FunctionInfo>& irFunctions) {
    emit(".global main");
    emit(".text");
    
    // 生成每个函数
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

void CodeGenerator::emitPrologue(const std::string& funcName, int frameSize, int valConut) {
    // 生成唯一退出标签（格式：.<函数名>_func_end）
    std::string exitLabel = "." + funcName + "_func_end";
    // 记录当前函数的退出标签，供return指令使用
    currentFuncExitLabel = exitLabel;
    emit(funcName + ":");
    emit("  addi sp, sp, -" + std::to_string(frameSize));
    emit("  sw ra, " + std::to_string(frameSize-4) + "(sp)");
    for (int i = 0; i <= valConut; ++i) {
        int offset = frameSize - 8 - i * 4;  // 计算每个寄存器的栈偏移
        emit("  sw s" + std::to_string(i) + ", " + std::to_string(offset) + "(sp)");
    }
    emit("  addi s0, sp, " + std::to_string(frameSize));
}

void CodeGenerator::emitEpilogue(int frameSize, int valConut) {
    emit(currentFuncExitLabel + ":");
    for (int i = 0; i <= valConut; ++i) {
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
    varStackMap.clear();
    stackOffset = 0;
    
    int tempVarSize = func.endTempCounter - func.startTempCounter;
    int paramCount = func.params.size();
    int localConut = func.varCount;
    int valConut = (localConut > 11)?11:localConut;
    int frameSize = 4 * (2 + localConut + paramCount + tempVarSize);
    // 确保栈帧大小按16字节对齐
    if (frameSize % 16 != 0) {
        frameSize += 16 - (frameSize % 16);
    }

    emitPrologue(func.name, frameSize, valConut);

    // 保存参数到栈帧
    int paramOffset = frameSize - 4 * (2 + localConut); // 参数在栈帧中的偏移量
    for (int i = 0; i < func.params.size() && i < 8; i++) {
        std::string reg = "a" + std::to_string(i);
        int offset = paramOffset - 4;
        paramOffset-=4;
        emit("  sw " + reg + ", " + std::to_string(offset) + "(sp)");
        
        varStackMap[func.params[i]->toString()] = offset;
    }
    stackOffset = paramOffset;
    
    // 生成函数体指令
    for (const auto& inst : func.instructions) {
        switch (inst.opcode) {
            case IROpcode::ASSIGN: generateAssignment(inst); break;
            case IROpcode::ADD: case IROpcode::SUB: case IROpcode::MUL: 
            case IROpcode::DIV: case IROpcode::MOD: generateArithmetic(inst); break;
            case IROpcode::LT: case IROpcode::GT: case IROpcode::LE: 
            case IROpcode::GE: case IROpcode::EQ: case IROpcode::NE: generateComparison(inst); break;
            case IROpcode::GOTO: case IROpcode::IF_GOTO: case IROpcode::LABEL: generateControlFlow(inst); break;
            case IROpcode::CALL: generateFunctionCall(inst); break;
            case IROpcode::PARAM: generateParam(inst); break;
            case IROpcode::RETURN: generateReturn(inst); break;
            default: break;
        }
    }
    
    emitEpilogue(frameSize, valConut);
}

std::string CodeGenerator::getRegOrLoad(const std::shared_ptr<Operand>& op) {
    if (!op) return "";

    if (op->type != OperandType::CONSTANT && regAlloc.isInReg(op->toString())) {
        return regAlloc.allocateReg(op->toString(),op->type);
    }

    std::string reg;
    if (op->type == OperandType::CONSTANT) {
        reg = regAlloc.allocateReg("const_" + op->value,op->type);
        emit("  li " + reg + ", " + op->value);
    } 
    else {
        while (true) {
            try {
                reg = regAlloc.allocateReg(op->toString(), op->type);
                break;
            } catch (const std::runtime_error& e) {
                auto spillInsts = regAlloc.spillRegister();
                for (const auto& inst : spillInsts) {
                    emit(inst);
                }
            }
        }
        
        // 检查是否是参数或局部变量
        if (varStackMap.find(op->value) != varStackMap.end()) {
            int offset = varStackMap[op->value];
            emit(RiscVUtils::emitLoad(reg, offset));
        }
        if (op->type == OperandType::PARAM && op->index >= 8) {
            int offset = 16 + (op->index - 8) * 4; // 在调用者栈帧中的位置
            emit("  lw " + reg + ", " + std::to_string(offset) + "(s0)");
        } 
    }
    return reg;
}

void CodeGenerator::storeIfTemp(const std::shared_ptr<Operand>& op, const std::string& reg) {
    if (op && op->type == OperandType::TEMP) {
        if (!varStackMap.count(op->value)) {
            stackOffset -= 4;
            varStackMap[op->value] = stackOffset;
        }
        emit(RiscVUtils::emitStore(reg, varStackMap[op->value]));
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

void CodeGenerator::generateAssignment(const IRInstruction& inst) {
    std::string srcReg = getRegOrLoad(inst.arg1);
    std::string destReg = regAlloc.allocateReg(inst.result->toString(),inst.result->type);
    
    if (srcReg != destReg) {
        emit("  mv " + destReg + ", " + srcReg);
    }
    
    storeIfTemp(inst.result, destReg);
    regAlloc.freeReg(inst.arg1->toString());
    // regAlloc.freeReg(inst.result->toString());
}

void CodeGenerator::generateArithmetic(const IRInstruction& inst) {
    std::string op;
    switch (inst.opcode) {
        case IROpcode::ADD: op = "add"; break;
        case IROpcode::SUB: op = "sub"; break;
        case IROpcode::MUL: op = "mul"; break;
        case IROpcode::DIV: op = "div"; break;
        case IROpcode::MOD: op = "rem"; break;
        default: break;
    }
    
    // 检查是否是乘除法指令
    bool isMulDiv = (inst.opcode == IROpcode::MUL || inst.opcode == IROpcode::DIV || inst.opcode == IROpcode::MOD);
    
    std::string rs1 = getRegOrLoad(inst.arg1);
    std::string rs2 = getRegOrLoad(inst.arg2);
    std::string rd = regAlloc.allocateReg(inst.result->toString(),inst.result->type);
    
    emit("  " + op + " " + rd + ", " + rs1 + ", " + rs2);
    
    storeIfTemp(inst.result, rd);
    // regAlloc.freeReg(inst.arg1->toString());
    // regAlloc.freeReg(inst.arg2->toString());
    // regAlloc.freeReg(inst.result->toString());
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
            std::string condReg = getRegOrLoad(inst.arg1);
            std::string validLabel = generateValidLabel(inst.label);
            emit("  bnez " + condReg + ", " + validLabel);
            regAlloc.freeReg(inst.arg1->toString());
            break;
        }
        default: break;
    }
}

void CodeGenerator::generateFunctionCall(const IRInstruction& inst) {
    // 调用者保存寄存器列表
    std::vector<std::string> callerSaved = {};
    for (int i = 0; i < 8; i++) {
        callerSaved.push_back("a" + std::to_string(i));
    }
    
    // 记录需要保存的寄存器
    std::vector<std::string> savedRegisters;
    for (const auto& reg : callerSaved) {
        if (regAlloc.isRegInUse(reg)) {
            savedRegisters.push_back(reg);
        }
    }
    
    // 计算保存寄存器所需的栈空间（确保16字节对齐）
    int saveSize = savedRegisters.size() * 4;
    int alignPadding = (16 - (saveSize % 16)) % 16; // RISC-V调用规范要求栈16字节对齐
    saveSize += alignPadding;
    
    // 先调整栈指针
    if (saveSize > 0) {
        emit("  addi sp, sp, -" + std::to_string(saveSize));
    }
    
    // 保存寄存器到栈（从高地址到低地址）
    int offset = alignPadding; // 跳过对齐填充
    for (const auto& reg : savedRegisters) {
        offset += 4;
        emit("  sw " + reg + ", " + std::to_string(saveSize - offset) + "(sp)");
    }
    
    resetParamCounter();

    // 调用函数
    emit("  call " + inst.arg1->toString());
    
    // 处理返回值
    if (inst.result) {
        std::string destReg = regAlloc.allocateReg(inst.result->toString(), inst.result->type);
        emit("  mv " + destReg + ", a0"); // a0存放返回值
        storeIfTemp(inst.result, destReg);
    }
    
    // 恢复寄存器（按保存的逆序，从低地址到高地址）
    offset = alignPadding;
    for (auto it = savedRegisters.rbegin(); it != savedRegisters.rend(); ++it) {
        offset += 4;
        emit("  lw " + *it + ", " + std::to_string(saveSize - offset) + "(sp)");
    }
    
    // 恢复栈指针
    if (saveSize > 0) {
        emit("  addi sp, sp, " + std::to_string(saveSize));
    }
}

// 重置参数计数器（在函数调用前调用）
void CodeGenerator::resetParamCounter() {
    paramCounter = 0;
}

// 处理param指令
void CodeGenerator::generateParam(const IRInstruction& inst) {
    if (!inst.arg1) return;

    std::string paramReg = getRegOrLoad(inst.arg1);
    
    if (paramCounter < 8) {
        std::string targetReg = "a" + std::to_string(paramCounter);
        if (paramReg != targetReg) {
            emit("  mv " + targetReg + ", " + paramReg);
            regAlloc.freeReg(inst.arg1->toString());
        }
    } else {
        int offset = (paramCounter - 8) * 4;
        emit("  sw " + paramReg + ", " + std::to_string(offset) + "(sp)");
        varStackMap[inst.arg1->value] = offset;
    }
    
    paramCounter++;
}

void CodeGenerator::generateReturn(const IRInstruction& inst) {
    if (inst.arg1) {
        std::string retReg = getRegOrLoad(inst.arg1);
        emit("  mv a0, " + retReg);
        regAlloc.freeReg(inst.arg1->toString());
    }
    emit("  j " + currentFuncExitLabel);  // 跳转到函数统一退出标签
}

void CodeGenerator::generateComparison(const IRInstruction& inst) {
    std::string rs1 = getRegOrLoad(inst.arg1);
    std::string rs2 = getRegOrLoad(inst.arg2);
    std::string rd = regAlloc.allocateReg(inst.result->toString(),inst.result->type);
    
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
        default:
            throw std::runtime_error("Unsupported comparison operator");
    }
    
    storeIfTemp(inst.result, rd);
    // regAlloc.freeReg(inst.arg1->toString());
    // regAlloc.freeReg(inst.arg2->toString());
    regAlloc.freeReg(inst.result->toString());
}