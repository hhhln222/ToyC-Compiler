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

void CodeGenerator::emitPrologue(const std::string& funcName, int frameSize) {
    emit(funcName + ":");
    emit("addi sp, sp, -" + std::to_string(frameSize));
    emit("sw ra, " + std::to_string(frameSize-4) + "(sp)");
    emit("sw s0, " + std::to_string(frameSize-8) + "(sp)");
    emit("addi s0, sp, " + std::to_string(frameSize));
}

void CodeGenerator::emitEpilogue(int frameSize) {
    emit("lw s0, " + std::to_string(frameSize-8) + "(sp)");
    emit("lw ra, " + std::to_string(frameSize-4) + "(sp)");
    emit("addi sp, sp, " + std::to_string(frameSize));
    emit("ret");
}

void CodeGenerator::emitFunction(const FunctionInfo& func) {
    // 重置标签映射
    labelMap.clear();
    usedLabels.clear();
    
    // 计算栈帧大小（简化版：每个变量4字节）
    int frameSize = 4 * (func.params.size() + 5); // 参数+局部变量+保留空间
    
    emitPrologue(func.name, frameSize);
    
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
            case IROpcode::RETURN: generateReturn(inst); break;
            default: break;
        }
    }
    
    emitEpilogue(frameSize);
}

std::string CodeGenerator::getRegOrLoad(const std::shared_ptr<Operand>& op) {
    if (!op) return "";
    
    if (op->type != OperandType::CONSTANT && 
        regAlloc.isInReg(op->toString())) {
        return regAlloc.allocateReg(op->toString());
    }

    std::string reg;
    if (op->type == OperandType::CONSTANT) {
        reg = regAlloc.allocateReg("const_" + op->value);
        emit("li " + reg + ", " + op->value);
    } else {
        reg = regAlloc.allocateReg(op->toString());
        if (varStackMap.count(op->value)) {
            emit(RiscVUtils::emitLoad(reg, varStackMap[op->value]));
        }
    }
    return reg;
}

void CodeGenerator::storeIfTemp(const std::shared_ptr<Operand>& op, const std::string& reg) {
    if (op && op->type == OperandType::TEMP) {
        if (!varStackMap.count(op->value)) {
            varStackMap[op->value] = stackOffset;
            stackOffset -= 4;
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
    std::string destReg = regAlloc.allocateReg(inst.result->toString());
    
    if (srcReg != destReg) {
        emit("mv " + destReg + ", " + srcReg);
    }
    
    storeIfTemp(inst.result, destReg);
    regAlloc.freeReg(inst.arg1->toString());
    regAlloc.freeReg(inst.result->toString());
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
    std::string rd = regAlloc.allocateReg(inst.result->toString());
    
    if (isMulDiv) {
        // 对于乘除法，添加M扩展标记
        emit(".option rvc");  // 可选：启用压缩指令
        emit(".option arch, +m");  // 启用M扩展
    }
    
    emit(op + " " + rd + ", " + rs1 + ", " + rs2);
    
    if (isMulDiv) {
        // 恢复默认选项
        emit(".option rvc");  // 可选
        emit(".option arch, -m");  // 禁用M扩展
    }
    
    storeIfTemp(inst.result, rd);
    regAlloc.freeReg(inst.arg1->toString());
    regAlloc.freeReg(inst.arg2->toString());
    regAlloc.freeReg(inst.result->toString());
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
            emit("j " + validLabel);
            break;
        }
        case IROpcode::IF_GOTO: {
            std::string condReg = getRegOrLoad(inst.arg1);
            std::string validLabel = generateValidLabel(inst.label);
            emit("bnez " + condReg + ", " + validLabel);
            regAlloc.freeReg(inst.arg1->toString());
            break;
        }
        default: break;
    }
}

void CodeGenerator::generateFunctionCall(const IRInstruction& inst) {
    // 保存调用者保存的寄存器
    emit("addi sp, sp, -16");
    emit("sw ra, 0(sp)");
    emit("sw a0, 4(sp)");
    emit("sw a1, 8(sp)");
    emit("sw a2, 12(sp)");
    
    // 设置参数（假设最多3个参数）
    if (inst.arg1) {
        std::string argReg = getRegOrLoad(inst.arg1);
        emit("mv a0, " + argReg);
        regAlloc.freeReg(inst.arg1->toString());
    }
    
    emit("call " + inst.arg1->toString());
    
    // 恢复寄存器
    emit("lw a2, 12(sp)");
    emit("lw a1, 8(sp)");
    emit("lw a0, 4(sp)");
    emit("lw ra, 0(sp)");
    emit("addi sp, sp, 16");
    
    // 处理返回值
    if (inst.result) {
        std::string rd = regAlloc.allocateReg(inst.result->toString());
        emit("mv " + rd + ", a0");
        storeIfTemp(inst.result, rd);
        regAlloc.freeReg(inst.result->toString());
    }
}

void CodeGenerator::generateReturn(const IRInstruction& inst) {
    if (inst.arg1) {
        std::string retReg = getRegOrLoad(inst.arg1);
        emit("mv a0, " + retReg);
        regAlloc.freeReg(inst.arg1->toString());
    }
}

void CodeGenerator::generateComparison(const IRInstruction& inst) {
    std::string rs1 = getRegOrLoad(inst.arg1);
    std::string rs2 = getRegOrLoad(inst.arg2);
    std::string rd = regAlloc.allocateReg(inst.result->toString());
    
    switch (inst.opcode) {
        case IROpcode::LT: 
            emit("slt " + rd + ", " + rs1 + ", " + rs2);
            break;
        case IROpcode::GT: 
            emit("slt " + rd + ", " + rs2 + ", " + rs1);
            break;
        case IROpcode::LE: 
            emit("slt " + rd + ", " + rs2 + ", " + rs1);
            emit("xori " + rd + ", " + rd + ", 1");
            break;
        case IROpcode::GE:
            emit("slt " + rd + ", " + rs1 + ", " + rs2);
            emit("xori " + rd + ", " + rd + ", 1");
            break;
        case IROpcode::EQ:
            emit("xor " + rd + ", " + rs1 + ", " + rs2);
            emit("seqz " + rd + ", " + rd);
            break;
        case IROpcode::NE:
            emit("xor " + rd + ", " + rs1 + ", " + rs2);
            emit("snez " + rd + ", " + rd);
            break;
        default:
            throw std::runtime_error("Unsupported comparison operator");
    }
    
    storeIfTemp(inst.result, rd);
    // regAlloc.freeReg(inst.arg1->toString());
    // regAlloc.freeReg(inst.arg2->toString());
    regAlloc.freeReg(inst.result->toString());
}