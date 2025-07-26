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
        "t0", "t1", "t2", "t3", "t4", "t5", "t6",
        "a0", "a1", "a2", "a3", "a4", "a5", "a6", "a7"
    };
    std::map<std::string, std::string> varToReg;
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