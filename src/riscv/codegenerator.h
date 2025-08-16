#pragma once
#include "IRGenerator.h"
#include "utils.h"
#include <string>
#include <vector>
#include <map>
#include <set>
#include <fstream>
#include <string>

class CodeGenerator {
public:
    CodeGenerator();
    ~CodeGenerator();
    void generate(const std::vector<FunctionInfo>& irFunctions);
    std::string getAssemblyCode() const;

private:
    std::string asmCode;
    std::ofstream logFile;
    std::string currentFuncExitLabel;
    RegisterAllocator regAlloc;
    int stackOffset;
    std::map<std::string, int> varStackMap; // 变量栈偏移映射
    std::set<std::string> usedLabels; // 已使用的标签集合
    std::map<std::string, std::string> labelMap; // IR标签到汇编标签的映射
    int paramCounter = 0;  // 用于记录参数顺序的计数器
    std::vector<std::string> paramStrings;

    // 生成函数框架
    void emitPrologue(const std::string& funcName, int frameSize, const std::vector<int>& usedSRegisters);
    void emitEpilogue(int frameSize, const std::vector<int>& usedSRegisters);

    // 指令生成
    void emit(const std::string& instruction);
    void emitFunction(const FunctionInfo& func);
    
    // IR指令处理
    void generateAssignment(const IRInstruction& inst);
    void generateArithmetic(const IRInstruction& inst);
    void generateComparison(const IRInstruction& inst);
    void generateControlFlow(const IRInstruction& inst);
    void generateFunctionCall(const IRInstruction& inst);
    void generateParam(const IRInstruction& inst);
    void generateReturn(const IRInstruction& inst);
    
    // 辅助方法
    void resetParamCounter();
    void resetParamStrings() { paramStrings.clear(); }  // 重置参数数组
    const std::vector<std::string>& getParamStrings() const { return paramStrings; }
    std::string getRegorLoad(const std::shared_ptr<Operand> operand);
    void spillReg(AllocationResult result);
    void logRegisterAllocation(const std::shared_ptr<Operand> operand, const std::string& reg, bool isFromStack = false, int stackOffset = 0);
    void logRegisterSpill(const std::string& var, const std::string& reg, int stackOffset);

    // 标签管理
    std::string generateValidLabel(const std::string& irLabel);
    std::string sanitizeLabel(const std::string& label);
    bool isValidLabel(const std::string& label);
};
