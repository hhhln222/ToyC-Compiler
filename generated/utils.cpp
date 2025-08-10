#include "utils.h"
#include <stdexcept> 
#include <algorithm>
#include <vector>
#include <string>
RegisterAllocator::RegisterAllocator() {
    // 初始化时所有寄存器可用
}

std::string RegisterAllocator::allocateReg(const std::string& var) {
    // 如果变量已分配寄存器，直接返回
    if (varToReg.count(var)) {
        return varToReg[var];
    }
    
    // 如果寄存器不足，溢出处理
    if (freeRegs.empty()) {
        spillRegister();
    }
    
    // 从队列前端取寄存器（优先使用a4、a5）
    std::string reg = freeRegs.front();
    freeRegs.erase(freeRegs.begin());  // 移除前端元素
    
    // 记录变量与寄存器的映射
    varToReg[var] = reg;
    return reg;
}

void RegisterAllocator::freeReg(const std::string& var) {
    if (!varToReg.count(var)) {
        return;  // 变量未分配寄存器，直接返回
    }
    
    std::string reg = varToReg[var];
    varToReg.erase(var);
    
    // 将释放的寄存器插入到对应优先级位置（保持顺序）
    // 1. 先从freeRegs中找到该寄存器的正确位置（按初始优先级）
    auto it = std::find(freeRegs.begin(), freeRegs.end(), reg);
    if (it == freeRegs.end()) {
        // 2. 如果不在队列中，插入到符合优先级的位置
        for (size_t i = 0; i < freeRegs.size(); ++i) {
            // 找到第一个优先级低于当前寄存器的位置
            if (std::find(initialRegOrder.begin(), initialRegOrder.end(), freeRegs[i]) >
                std::find(initialRegOrder.begin(), initialRegOrder.end(), reg)) {
                freeRegs.insert(freeRegs.begin() + i, reg);
                return;
            }
        }
        // 如果所有寄存器优先级都更低，插入到末尾
        freeRegs.push_back(reg);
    }
}

bool RegisterAllocator::isInReg(const std::string& var) const {
    return varToReg.count(var);
}

void RegisterAllocator::spillRegister() {
    // 应实现：
    // 1. 选择要溢出的寄存器（如LRU策略）
    // 2. 找到对应的变量
    // 3. 生成存储指令
    // 4. 更新寄存器状态
    throw std::runtime_error("Register spilling not implemented");
}

namespace RiscVUtils {
    std::string emitLoad(const std::string& reg, int offset) {
        return "lw " + reg + ", " + std::to_string(offset) + "(sp)";
    }
    
    std::string emitStore(const std::string& reg, int offset) {
        return "sw " + reg + ", " + std::to_string(offset) + "(sp)";
    }
    
    std::string emitBinaryOp(const std::string& op, 
                           const std::string& rd, 
                           const std::string& rs1, 
                           const std::string& rs2) {
        return op + " " + rd + ", " + rs1 + ", " + rs2;
    }
};