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
}


// 分配寄存器
AllocationResult RegisterAllocator::allocateReg(const std::string& var, OperandType type) {
    // 变量已在寄存器中：更新时间戳，返回无溢出结果
    if (isInReg(var)) {
        return {
            .reg = varInfoMap[var].reg,
            .spill = {"", "", OperandType::TEMP}  // 无溢出：默认值
        };
    }

    // 选择目标寄存器池
    std::vector<std::string>* targetPool = nullptr;
    switch (type) {
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
    for (const auto& [varName, info] : varInfoMap) {
        if (info.type == type) {
            lruVar = varName;
        }
    }
    
    std::string error_reg="";
    for (const auto& [varName, info] : varInfoMap) {
        error_reg+=" varName: "+varName+", reg: "+info.reg+"\n";
    }

    if (lruVar.empty()) {
        std::cout<<error_reg;
        throw std::runtime_error("No reusable registers for type: " + std::to_string(static_cast<int>(type)) + ", val: " + var);
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
    varInfoMap[var] = {reusedReg, type};

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
    
    // 优化：排序寄存器池以便优先分配低编号寄存器
    std::sort(freeTempRegs.begin(), freeTempRegs.end());
    std::sort(freeParamRegs.begin(), freeParamRegs.end());
    std::sort(freeSavedRegs.begin(), freeSavedRegs.end());
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