#pragma once
#include "IRGenerator.h"
#include <string>
#include <vector>
#include <map>
#include <stdexcept>
#include <algorithm>

// 存储溢出变量的信息
struct SpilledVar {
    std::string varName;  // 变量名
    std::string reg;      // 变量原占用的寄存器
    OperandType type;     // 变量类型
};

// 寄存器分配结果
struct AllocationResult {
    std::string reg;       // 成功分配的寄存器
    SpilledVar spill; // 溢出的变量
};

// 变量信息结构体
struct VarInfo {
    std::string reg;       // 绑定的寄存器
    OperandType type;      // 变量类型
    std::size_t lastUsed;  // 最后使用时间戳
};

// RISC-V寄存器分配器
class RegisterAllocator {
public:
    RegisterAllocator();
    AllocationResult allocateReg(const std::string& var, OperandType type);
    bool isInReg(const std::string& var) const;
    std::string getReg(const std::string& var) const;
    void freeReg(const std::string& var);
    void reset();
    bool isRegInUse(const std::string& reg) const;

private:
    std::vector<std::string> freeTempRegs;    // t0-t6
    std::vector<std::string> freeParamRegs;   // a0-a7
    std::vector<std::string> freeSavedRegs;   // s1-s11
    const std::vector<std::string> initialTempRegs;
    const std::vector<std::string> initialParamRegs;
    const std::vector<std::string> initialSavedRegs;
    
    std::map<std::string, VarInfo> varInfoMap;
    std::size_t timestamp = 0;
};

// RISC-V指令生成工具
namespace RiscVUtils {
    std::string emitBinaryOp(const std::string& op, 
                           const std::string& rd, 
                           const std::string& rs1, 
                           const std::string& rs2);
    std::string emitCall(const std::string& func, int paramCount);
};