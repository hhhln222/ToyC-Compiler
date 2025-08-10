#pragma once
#include <string>
#include <vector>
#include <map>
#include <stdexcept> 
// RISC-V寄存器分配器
class RegisterAllocator {
public:
    RegisterAllocator();
    std::string allocateReg(const std::string& var);
    void freeReg(const std::string& var);
    bool isInReg(const std::string& var) const;
    void spillRegister(); // 寄存器溢出处理

private:
    std::vector<std::string> freeRegs = {
        "a4", "a5",         // 优先分配的寄存器（按顺序）
        "a6", "a7",         // 次优先的参数寄存器
        "t0", "t1", "t2", "t3", "t4", "t5", "t6",  // 临时寄存器
        "a0", "a1", "a2", "a3"  // 最后使用（a0-a3用于参数和返回值，尽量避免提前占用）
    };
    std::map<std::string, std::string> varToReg;
    std::vector<std::string> initialRegOrder = freeRegs;
};

// RISC-V指令生成工具
namespace RiscVUtils {
    std::string emitLoad(const std::string& reg, int offset);
    std::string emitStore(const std::string& reg, int offset);
    std::string emitBinaryOp(const std::string& op, 
                           const std::string& rd, 
                           const std::string& rs1, 
                           const std::string& rs2);
};