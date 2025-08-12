#include "utils.h"
#include <stdexcept> 
#include <algorithm>
#include <vector>
#include <string>

// 初始化不同数据类型的寄存器列表（按调用约定优先级排序）
RegisterAllocator::RegisterAllocator() 
    : initialRegOrder({
        // 临时寄存器（caller-saved，临时变量优先使用）
        "t0", "t1", "t2", "t3", "t4", "t5", "t6",
        // 参数寄存器（caller-saved，参数优先使用）
        "a0", "a1", "a2", "a3", "a4", "a5", "a6", "a7",
        // 保存寄存器（callee-saved，普通变量优先使用）
        "s1", "s2", "s3", "s4", "s5", "s6", "s7", "s8", "s9", "s10", "s11"
    }) {
    reset();
}

// 重置分配器状态
void RegisterAllocator::reset() {
    freeRegs = initialRegOrder;
    varInfoMap.clear();
    usedRegisters.clear();
    timestamp = 0;
    nextSpillOffset = -4;  // 重置栈偏移（从-4开始，每次减4）
}

// 分配寄存器
std::string RegisterAllocator::allocateReg(const std::string& var, OperandType type) {
    // 检查是否已分配，若已分配则更新时间戳
    if (isInReg(var)) {
        varInfoMap[var].lastUsed = timestamp++;
        return varInfoMap[var].reg;
    }

    // 寄存器不足时触发溢出
    while (freeRegs.empty()) {
        auto spillInsts = spillRegister();
        // 实际应用中需要处理溢出指令（如添加到指令列表）
    }

    // 根据变量类型选择最合适的寄存器
    // 策略：临时变量优先使用t系列，参数优先使用a系列，普通变量优先使用s系列
    std::string selectedReg;
    for (const auto& reg : initialRegOrder) {
        // 检查寄存器是否空闲
        if (std::find(freeRegs.begin(), freeRegs.end(), reg) != freeRegs.end()) {
            // 根据变量类型优化选择
            bool isTempReg = reg.substr(0, 1) == "t";
            bool isParamReg = reg.substr(0, 1) == "a";
            bool isSavedReg = reg.substr(0, 1) == "s";

            // 找到第一个匹配类型的空闲寄存器
            if ((type == OperandType::TEMP && isTempReg) ||
                (type == OperandType::PARAM && isParamReg) ||
                (type == OperandType::VARIABLE && isSavedReg)) {
                selectedReg = reg;
                break;
            }
            
            // 如果没有找到匹配类型的，使用第一个空闲寄存器
            if (selectedReg.empty()) {
                selectedReg = reg;
            }
        }
    }

    if (selectedReg.empty()) {
        throw std::runtime_error("No available register for allocation");
    }

    // 从空闲列表中移除并记录变量信息
    freeRegs.erase(std::remove(freeRegs.begin(), freeRegs.end(), selectedReg), freeRegs.end());
    varInfoMap[var] = {
        selectedReg, 
        type, 
        timestamp++,
        nextSpillOffset  // 记录溢出偏移
    };
    nextSpillOffset -= 4;  // 整数占4字节

    return selectedReg;
}

// 释放寄存器
void RegisterAllocator::freeReg(const std::string& var) {
    auto it = varInfoMap.find(var);
    if (it == varInfoMap.end()) return;

    const auto& varInfo = it->second;
    
    // 将寄存器放回空闲列表并保持初始优先级排序
    freeRegs.push_back(varInfo.reg);
    std::sort(freeRegs.begin(), freeRegs.end(),
        [&](const std::string& a, const std::string& b) {
            auto posA = std::find(initialRegOrder.begin(), initialRegOrder.end(), a);
            auto posB = std::find(initialRegOrder.begin(), initialRegOrder.end(), b);
            return posA < posB;
        });

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

// 溢出寄存器（LRU策略）
std::vector<std::string> RegisterAllocator::spillRegister() {
    std::vector<std::string> spillInsts;
    if (varInfoMap.empty()) {
        throw std::runtime_error("No registers to spill");
    }

    // 选择最近最少使用的变量溢出
    auto lruIt = std::min_element(varInfoMap.begin(), varInfoMap.end(),
        [](const auto& a, const auto& b) {
            return a.second.lastUsed < b.second.lastUsed;
        });
    const auto& spillVar = lruIt->first;
    const auto& spillInfo = lruIt->second;

    // 生成溢出存储指令
    spillInsts.push_back(generateSpillStore(spillInfo));
    
    // 释放被溢出的寄存器
    freeReg(spillVar);

    return spillInsts;
}

std::vector<std::string> RegisterAllocator::getUsedSRegs() const {
    std::vector<std::string> usedSRegs;
    
    // 遍历所有已分配的变量信息
    for (const auto& [var, info] : varInfoMap) {
        // 检查是否为s系列寄存器（保存寄存器）
        if (info.reg.size() >= 2 && info.reg[0] == 's') {
            // 验证是s0-s11范围内的寄存器
            char numChar = info.reg[1];
            if (isdigit(numChar)) {
                int num = numChar - '0';
                // 检查是否是s0-s1或s2-s11
                if ((num >= 0 && num <= 1) || (num >= 2 && num <= 11)) {
                    // 避免重复添加同一个寄存器
                    if (std::find(usedSRegs.begin(), usedSRegs.end(), info.reg) == usedSRegs.end()) {
                        usedSRegs.push_back(info.reg);
                    }
                }
            }
        }
    }
    
    return usedSRegs;
}

bool RegisterAllocator::isRegInUse(const std::string& reg) const {
    // 遍历所有已分配的变量信息，检查是否有变量使用目标寄存器
    for (const auto& pair : varInfoMap) {
        if (pair.second.reg == reg) {
            return true; // 寄存器正在被使用
        }
    }
    return false; // 寄存器未被使用
}

// 生成溢出存储指令
std::string RegisterAllocator::generateSpillStore(const VarInfo& varInfo) {
    return RiscVUtils::emitStore(varInfo.reg, varInfo.spillOffset);
}

// 生成溢出加载指令
std::string RegisterAllocator::generateSpillLoad(const VarInfo& varInfo) {
    return RiscVUtils::emitLoad(varInfo.reg, varInfo.spillOffset);
}

std::vector<std::string> RegisterAllocator::spillReg(const std::string& reg) {
    std::vector<std::string> spillInsts;
    // 查找使用目标寄存器的变量
    for (const auto& pair : varInfoMap) {
        if (pair.second.reg == reg) {
            // 生成溢出存储指令（保存到栈）
            spillInsts.push_back(generateSpillStore(pair.second));
            // 释放该变量占用的寄存器
            freeReg(pair.first);
            break;
        }
    }
    return spillInsts;
}

void RegisterAllocator::forceAllocateReg(const std::string& var, OperandType type, const std::string& targetReg) {
    // 检查目标寄存器是否为合法寄存器
    if (std::find(initialRegOrder.begin(), initialRegOrder.end(), targetReg) == initialRegOrder.end()) {
        throw std::runtime_error("Invalid target register: " + targetReg);
    }

    // 若目标寄存器已被占用，先溢出原有变量
    auto existingVar = std::find_if(varInfoMap.begin(), varInfoMap.end(),
        [&](const std::pair<std::string, VarInfo>& pair) {
            return pair.second.reg == targetReg;
        });
    if (existingVar != varInfoMap.end()) {
        auto spillInsts = spillReg(targetReg);
        // 实际使用时需将溢出指令添加到指令列表（如IR生成器的指令序列）
    }

    // 从空闲列表中移除目标寄存器（若存在）
    auto freeIt = std::find(freeRegs.begin(), freeRegs.end(), targetReg);
    if (freeIt != freeRegs.end()) {
        freeRegs.erase(freeIt);
    }

    // 强制绑定变量到目标寄存器
    varInfoMap[var] = {
        targetReg,        // 绑定到指定寄存器
        type,             // 变量类型
        timestamp++,      // 更新时间戳
        nextSpillOffset   // 记录溢出偏移（若后续被溢出时使用）
    };
    nextSpillOffset -= 4;  // 栈偏移递减（按4字节对齐）
}

namespace RiscVUtils {
    std::string emitLoad(const std::string& reg, int offset) {
        return "  lw " + reg + ", " + std::to_string(offset) + "(sp)";
    }
    
    std::string emitStore(const std::string& reg, int offset) {
        return "  sw " + reg + ", " + std::to_string(offset) + "(sp)";
    }
    
    std::string emitBinaryOp(const std::string& op, 
                           const std::string& rd, 
                           const std::string& rs1, 
                           const std::string& rs2) {
        return "  " + op + " " + rd + ", " + rs1 + ", " + rs2;
    }

    std::string emitCall(const std::string& func, int paramCount) {
        return "  call " + func + " # " + std::to_string(paramCount) + " parameters";
    }
    
    std::string emitReturn() {
        return "  ret";
    }
    
    std::string emitParam(int index, const std::string& reg) {
        if (index < 8) {
            // 使用a0-a7寄存器传递参数
            std::string paramReg = "a" + std::to_string(index);
            return "  mv " + paramReg + ", " + reg;
        } else {
            // 超过8个参数用栈传递
            int offset = (index - 8) * 4;  // 整数占4字节
            return emitStore(reg, offset);
        }
    }
};