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

int countLocalVariables(const FunctionInfo& func) {
    // 1. 收集所有参数名（用于排除参数）
    std::unordered_set<std::string> paramNames;
    for (const auto& param : func.params) {
        paramNames.insert(param);
    }
    
    // 2. 收集所有局部变量（用户定义变量 + 临时变量）
    std::unordered_set<std::string> localVarIdentifiers;
    
    // 遍历所有指令的操作数
    auto processOperand = [&](const std::shared_ptr<Operand>& op) {
        if (!op) return; // 跳过空操作数
        
        // 处理用户定义的局部变量（排除参数）
        if (op->type == OperandType::VARIABLE) {
            // 检查是否为参数
            if (paramNames.find(op->value) == paramNames.end()) {
                localVarIdentifiers.insert(op->value);
            }
        }
        // 处理编译器生成的临时变量（TEMP类型）
        else if (op->type == OperandType::TEMP) {
            // 临时变量的标识是"t"+value，直接用value作为唯一标识
            localVarIdentifiers.insert("t" + op->value);
        }
    };
    
    // 遍历所有指令
    for (const auto& inst : func.instructions) {
        processOperand(inst.result);
        processOperand(inst.arg1);
        processOperand(inst.arg2);
    }
    
    // 3. 集合大小即为局部变量总数（自动去重）
    return localVarIdentifiers.size();
}

void CodeGenerator::emitFunction(const FunctionInfo& func) {
    // 重置标签映射
    labelMap.clear();
    usedLabels.clear();
    
    // 计算栈帧大小
    int localVarSize = countLocalVariables(func);
    // 正确计算：保存ra(4) + s0(4) + 参数(每个4字节) + 局部变量(每个4字节)
    int frameSize = 8 + 4 * (func.params.size() + localVarSize); 
    // 确保栈帧大小按16字节对齐（RISC-V调用约定）
    if (frameSize % 16 != 0) {
        frameSize += 16 - (frameSize % 16);
    }

    emitPrologue(func.name, frameSize);

    // 处理函数参数：保存a0,a1...到栈中，按约定顺序存取
    if (!func.params.empty()) {
        // 1. 保存参数寄存器到栈（a0对应第一个参数，依次类推）
        int paramOffset = -20;  // 初始偏移，与目标汇编一致
        for (int i = 0; i < func.params.size(); ++i) {
            emit("sw a" + std::to_string(i) + ", " + std::to_string(paramOffset) + "(s0)");
            paramOffset -= 4;
        }

        // 2. 从栈加载参数到临时寄存器（a4,a5...）
        paramOffset = -20;  // 重置偏移
        for (int i = 0; i < func.params.size(); ++i) {
            std::string tempReg = "a" + std::to_string(4 + i);  // a4,a5,a6...
            emit("lw " + tempReg + ", " + std::to_string(paramOffset) + "(s0)");
            paramOffset -= 4;
        }
    }
    
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
    
    emitEpilogue(frameSize);
}

std::string CodeGenerator::getRegOrLoad(const std::shared_ptr<Operand>& op) {
    if (!op) return "";

    if (op->type != OperandType::CONSTANT && regAlloc.isInReg(op->toString())) {
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
    std::string destReg = regAlloc.allocateReg(inst.result->toString());
    
    if (srcReg != destReg) {
        emit("mv " + destReg + ", " + srcReg);
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
    emit("call " + inst.arg1->toString());
    resetParamCounter();
}

// 重置参数计数器（在函数调用前调用）
void CodeGenerator::resetParamCounter() {
    paramCounter = 0;
}

// 处理param指令（无索引，自动按顺序映射到a0、a1...）
void CodeGenerator::generateParam(const IRInstruction& inst) {
    if (!inst.arg1) {
        throw std::runtime_error("Invalid parameter operand");
    }

    // 按顺序自动分配参数寄存器：第1个参数→a0，第2个→a1，以此类推
    std::string targetReg = "a" + std::to_string(paramCounter);
    
    // 处理常量参数（直接加载到目标寄存器）
    if (inst.arg1->type == OperandType::CONSTANT) {
        emit("li " + targetReg + ", " + inst.arg1->value);
    } else {
        // 处理变量参数（从内存加载后移动到目标寄存器）
        std::string paramReg = getRegOrLoad(inst.arg1);
        if (paramReg != targetReg) {
            emit("mv " + targetReg + ", " + paramReg);
        }
        regAlloc.freeReg(inst.arg1->toString());
    }
    
    // 参数计数器自增，确保下一个参数使用下一个寄存器
    paramCounter++;
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