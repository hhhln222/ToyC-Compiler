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
}

// 重置分配器状态
void RegisterAllocator::reset() {
    freeTempRegs = initialTempRegs;
    freeParamRegs = initialParamRegs;
    freeSavedRegs = initialSavedRegs;
    varInfoMap.clear();
    timestamp = 0;
}

// 查找指定类型中最久未使用的寄存器，返回复用的寄存器和溢出变量信息
std::pair<std::string, SpilledVar> findLRUAndSpill(OperandType type, const std::map<std::string, VarInfo>& varInfoMap) {
    std::string lruVar;
    size_t minLastUsed = std::numeric_limits<size_t>::max();

    // 遍历所有变量，找到同类型中最久未使用的
    for (const auto& [varName, info] : varInfoMap) {
        if (info.type == type && info.lastUsed < minLastUsed) {
            minLastUsed = info.lastUsed;
            lruVar = varName;
        }
    }

    // 理论上不会触发（至少有当前类型的寄存器被分配过）
    if (lruVar.empty()) {
        throw std::runtime_error("No reusable registers for type: " + std::to_string(static_cast<int>(type)));
    }

    // 生成溢出变量信息
    const auto& lruInfo = varInfoMap.at(lruVar);
    SpilledVar spilled{
        .varName = lruVar,
        .reg = lruInfo.reg,
        .type = lruInfo.type
    };

    return {lruInfo.reg, spilled}; // 返回复用的寄存器和溢出信息
}

// 分配寄存器
AllocationResult RegisterAllocator::allocateReg(const std::string& var, OperandType type) {
    // 变量已在寄存器中：更新时间戳，返回无溢出结果
    if (isInReg(var)) {
        varInfoMap[var].lastUsed = timestamp++;
        return {
            .reg = varInfoMap[var].reg,
            .spill = {"", "", OperandType::TEMP}  // 无溢出：默认值
        };
    }

    // 选择目标寄存器池
    std::vector<std::string>* targetPool = nullptr;
    switch (type) {
        case OperandType::TEMP:    
        case OperandType::CONSTANT: 
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
            timestamp++
        };

        return {
            .reg = reg,
            .spill = {"", "", OperandType::TEMP}  // 无溢出：默认值
        };
    }

    // 寄存器不足：参数寄存器不处理，直接报错
    if (type == OperandType::PARAM) {
        throw std::runtime_error("Register exhausted for PARAM type (not handled)");
    }

    // 临时/变量寄存器不足：LRU策略溢出，返回溢出信息
    // 查找最久未使用的寄存器
    std::string lruVar;
    size_t minLastUsed = std::numeric_limits<size_t>::max();
    for (const auto& [varName, info] : varInfoMap) {
        if (info.type == type && info.lastUsed < minLastUsed) {
            minLastUsed = info.lastUsed;
            lruVar = varName;
        }
    }

    if (lruVar.empty()) {
        throw std::runtime_error("No reusable registers for type: " + std::to_string(static_cast<int>(type)));
    }

    // 生成溢出信息
    const auto& lruInfo = varInfoMap.at(lruVar);
    SpilledVar spilled{
        .varName = lruVar,
        .reg = lruInfo.reg,
        .type = lruInfo.type
    };

    // 移除LRU变量记录，分配复用寄存器
    std::string reusedReg = lruInfo.reg;
    varInfoMap.erase(lruVar);
    varInfoMap[var] = {reusedReg, type, timestamp++};

    // 返回分配结果和溢出信息
    return {
        .reg = reusedReg,
        .spill = spilled  // 有溢出：填充实际信息
    };
}

// 释放寄存器
void RegisterAllocator::freeReg(const std::string& var) {
    auto it = varInfoMap.find(var);
    if (it == varInfoMap.end()) return;
    
    const std::string& reg = it->second.reg;
    OperandType type = it->second.type;
    
    // 归还到对应寄存器池
    switch (type) {
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
    return varInfoMap.find(var) != varInfoMap.end();
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