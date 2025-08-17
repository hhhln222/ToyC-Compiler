#include "utils.h"
#include <stdexcept> 
#include <algorithm>
#include <vector>
#include <string>
#include <iterator>


RegisterAllocator::RegisterAllocator() 
    : initialTempRegs({"t0", "t1", "t2", "t3", "t4", "t5", "t6"}),
      initialParamRegs({"a0", "a1", "a2", "a3", "a4", "a5", "a6", "a7"}),
      initialSavedRegs({"s1", "s2", "s3", "s4", "s5", "s6", "s7", "s8", "s9", "s10", "s11"})
{
    reset();
    typeVarQueues.clear();
}

// 重置分配器状态
void RegisterAllocator::reset() {
    freeTempRegs = initialTempRegs;
    freeParamRegs = initialParamRegs;
    freeSavedRegs = initialSavedRegs;
    varInfoMap.clear();
    typeVarQueues.clear();
}


// 分配寄存器
AllocationResult RegisterAllocator::allocateReg(const std::string& var, OperandType operandType) {
    
    OperandType type = (operandType==OperandType::CONSTANT)? OperandType::TEMP:operandType;
    // 变量已在寄存器中：直接返回
    if (isInReg(var)) {
        return {
            .reg = varInfoMap[var].reg,
            .spill = {"", "", OperandType::TEMP}, // 无溢出：默认值
            .isSpill = false
        };
    }

    // 选择目标寄存器池
    std::vector<std::string>* targetPool = nullptr;
    switch (type) {
        case OperandType::CONSTANT:
        case OperandType::TEMP:
            targetPool = &freeTempRegs; break;
        case OperandType::PARAM:   
            targetPool = &freeParamRegs; break;
        case OperandType::VARIABLE:
            targetPool = &freeSavedRegs; break;
        default: 
            throw std::runtime_error("Invalid operand type");
    }

    // 寄存器池有可用寄存器：直接分配，无溢出
    if (!targetPool->empty()) {
        std::string reg = targetPool->front();
        targetPool->erase(targetPool->begin());
        
        varInfoMap[var] = {
            reg,
            type,
        };

        typeVarQueues[type].push_back(var); // 新变量入队列尾部

        return {
            .reg = reg,
            .spill = {"", "", OperandType::TEMP},  // 无溢出：默认值
            .isSpill = false
        };
    }

    // 寄存器不足：参数寄存器不处理，直接报错
    if (type == OperandType::PARAM) {
        throw std::runtime_error("Register exhausted for PARAM type (not handled)");
    }

    // 临时/变量寄存器不足：使用FIFO策略
    auto& queue = typeVarQueues[type];
    if (queue.empty()) {
        throw std::runtime_error("No reusable registers for type: " + std::to_string(static_cast<int>(type)));
    }

    // 取出最早分配的变量（队列前端）
    std::string fifoVar = queue.front();
    queue.pop_front();

    // 生成溢出信息
    const auto& fifoInfo = varInfoMap.at(fifoVar);
    SpilledVar spilled{
        .varName = fifoVar,
        .reg = fifoInfo.reg,
        .type = fifoInfo.type
    };

    // 复用寄存器
    std::string reusedReg = fifoInfo.reg;
    varInfoMap.erase(fifoVar);
    varInfoMap[var] = {reusedReg, type};
    
    // 新变量加入队列尾部
    queue.push_back(var);

    // 返回分配结果和溢出信息
    return {reusedReg, spilled, true};
}

// 释放寄存器
void RegisterAllocator::freeReg(const std::string& var) {
    auto it = varInfoMap.find(var);
    if (it == varInfoMap.end()) return;
    
    const std::string& reg = it->second.reg;
    OperandType type = it->second.type;

    // 从FIFO队列中删除变量
    auto& queue = typeVarQueues[type];
    for (auto iter = queue.begin(); iter != queue.end(); ++iter) {
        if (*iter == var) {
            queue.erase(iter);
            break;
        }
    }
    
    // 归还到对应寄存器池
    switch (type) {
        case OperandType::CONSTANT:
        case OperandType::TEMP:
            freeTempRegs.push_back(reg);
            break;
        case OperandType::PARAM:
            freeParamRegs.push_back(reg);
            break;
        case OperandType::VARIABLE:
            freeSavedRegs.push_back(reg);
            break;
    }
    
    varInfoMap.erase(it);
}

// 检查变量是否在寄存器中
bool RegisterAllocator::isInReg(const std::string& var) const {
    for (const auto& [varName, info] : varInfoMap) {
        if (var == varName) {
            return true;
        }
    }
    return false;
}

// 获取变量绑定的寄存器
std::string RegisterAllocator::getReg(const std::string& var) const {
    auto it = varInfoMap.find(var);
     if (it == varInfoMap.end()) {
       throw std::runtime_error("Variable not in register: " + var);
    }
    return it->second.reg;
}

bool RegisterAllocator::isRegInUse(const std::string& reg) const {
    // 遍历所有已分配的变量信息，检查是否有变量使用目标寄存器
    for (const auto& pair : varInfoMap) {
        if (pair.second.reg == reg) {
            return true;
        }
    }
    return false;
}

namespace RiscVUtils {
    std::string emitBinaryOp(const std::string& op, 
                           const std::string& rd, 
                           const std::string& rs1, 
                           const std::string& rs2) {
        return "  " + op + " " + rd + ", " + rs1 + ", " + rs2;
    }

    std::string emitCall(const std::string& func, int paramCount) {
        return "  call " + func + " # " + std::to_string(paramCount) + " parameters";
    }
    
};

bool RegisterAllocator::hasFreeRegForType(const std::shared_ptr<Operand> operand) const {
    OperandType type = operand->type;
    switch (type) {
        case OperandType::CONSTANT:
        case OperandType::TEMP:
            // 临时变量对应临时寄存器池（t0-t6）
            return !freeTempRegs.empty();
        case OperandType::VARIABLE:
            // 普通变量（如参数）对应参数寄存器池（a0-a7）
            // 注：若VARIABLE包含非参数变量，可根据实际逻辑调整（如扩展类型枚举）
            return !freeParamRegs.empty();
        default:
            // 未知类型返回false（或抛出异常）
            throw std::invalid_argument("Unknown OperandType when checking free registers");
    }
}

void RegisterAllocator::bindVarToReg(const std::string& var, const std::string& reg) {
    // 1. 忽略a开头的寄存器（不处理其绑定）
    if (reg.size() > 0 && reg[0] == 'a') {
        return; // 直接返回，不进行绑定操作
    }

    // 2. 校验寄存器格式合法性（字母+数字组合）
    if (reg.size() < 2 || !std::isalpha(reg[0]) || !std::isdigit(reg.substr(1)[0])) {
        throw std::runtime_error("bindVarToReg: 寄存器 " + reg + " 格式无效（应为字母+数字，如s1、t0）");
    }

    // 3. 解析寄存器类型和编号
    char regType = reg[0];
    int regNum;
    try {
        regNum = std::stoi(reg.substr(1));
    } catch (...) {
        throw std::runtime_error("bindVarToReg: 寄存器 " + reg + " 数字部分无效");
    }

    // 4. 根据变量名判断预期的寄存器类型
    char expectedType;
    if (std::isdigit(var[0]) || (var.size() > 0 && var[0] == 't')) {
        // 变量名以数字或t开头 → 预期绑定临时寄存器（t系列）
        expectedType = 't';
    } else {
        // 其他变量 → 预期绑定变量寄存器（s系列）
        expectedType = 's';
    }

    // 5. 校验寄存器类型与预期匹配
    if (regType != expectedType) {
        throw std::runtime_error("bindVarToReg: 变量 " + var + " 预期绑定" + expectedType + 
                               "类型寄存器，实际为" + regType);
    }

    // 6. 校验寄存器范围合法性
    bool isValid = false;
    switch (regType) {
        case 't':  // 临时寄存器 t0-t6
            isValid = (regNum >= 0 && regNum <= 6);
            break;
        case 's':  // 变量寄存器 s0-s11
            isValid = (regNum >= 0 && regNum <= 11);
            break;
        default:
            isValid = false; // 理论上不会走到这里，因为已过滤a开头寄存器
    }
    if (!isValid) {
        throw std::runtime_error("bindVarToReg: 寄存器 " + reg + " 不在有效范围内");
    }

    // 建立绑定关系（覆盖原有绑定）
    varInfoMap[var] = {reg, 
                      (expectedType == 't' ? OperandType::TEMP : OperandType::VARIABLE)};
}