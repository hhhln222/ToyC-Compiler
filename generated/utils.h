#pragma once
#include "IRGenerator.h"
#include <string>
#include <vector>
#include <map>
#include <stdexcept>

// 变量信息结构体
struct VarInfo {
    std::string reg;       // 绑定的寄存器
    OperandType type;      // 变量类型
    std::size_t lastUsed;  // 最后使用时间戳（用于LRU溢出策略）
    int spillOffset;       // 溢出到栈的偏移量
};

// RISC-V寄存器分配器
class RegisterAllocator {
public:
    RegisterAllocator();
    std::string allocateReg(const std::string& var, OperandType type);
    void freeReg(const std::string& var);
    bool isInReg(const std::string& var) const;
    std::string getReg(const std::string& var) const;
    std::vector<std::string> spillRegister();
    void reset();
    // 获取所有已分配的变量信息
    const std::map<std::string, VarInfo>& getAllocatedVars() const {
        return varInfoMap;
    }
    std::vector<std::string> getUsedSRegs() const;
    void forceAllocateReg(const std::string& var, OperandType type, const std::string& targetReg);
    bool isRegInUse(const std::string& reg) const;

private:
    std::vector<std::string> freeRegs;                // 空闲寄存器列表
    const std::vector<std::string> initialRegOrder;   // 初始寄存器优先级顺序
    std::map<std::string, VarInfo> varInfoMap;        // 变量信息映射表
    std::set<std::string> usedRegisters;
    std::size_t timestamp = 0;                        // 时间戳计数器
    int nextSpillOffset = -4;                         // 下一个溢出位置的栈偏移
    std::vector<std::string> spillReg(const std::string& reg);// 用于强制绑定时释放目标寄存器
    std::string generateSpillStore(const VarInfo& varInfo);
    std::string generateSpillLoad(const VarInfo& varInfo);
};

// RISC-V指令生成工具
namespace RiscVUtils {
    std::string emitLoad(const std::string& reg, int offset);
    std::string emitStore(const std::string& reg, int offset);
    std::string emitBinaryOp(const std::string& op, 
                           const std::string& rd, 
                           const std::string& rs1, 
                           const std::string& rs2);
    std::string emitCall(const std::string& func, int paramCount);
    std::string emitReturn();
    std::string emitParam(int index, const std::string& reg);
};