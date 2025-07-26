#include "utils.h"
#include <stdexcept> 
RegisterAllocator::RegisterAllocator() {
    // 初始化时所有寄存器可用
}

std::string RegisterAllocator::allocateReg(const std::string& var) {
    if (varToReg.count(var)) return varToReg[var];
    if (freeRegs.empty()) spillRegister();
    
    std::string reg = freeRegs.back();
    freeRegs.pop_back();
    varToReg[var] = reg;
    return reg;
}

void RegisterAllocator::freeReg(const std::string& var) {
    if (varToReg.count(var)) {
        freeRegs.push_back(varToReg[var]);
        varToReg.erase(var);
    }
}

bool RegisterAllocator::isInReg(const std::string& var) const {
    return varToReg.count(var);
}

void RegisterAllocator::spillRegister() {
    // 简单实现：报错（实际应实现栈溢出）
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