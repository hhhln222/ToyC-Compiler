#pragma once
#include "IRGenerator.h"
#include "utils.h"
#include <string>
#include <vector>
#include <map>

class CodeGenerator {
public:
    CodeGenerator();
    void generate(const std::vector<FunctionInfo>& irFunctions);
    std::string getAssemblyCode() const;

private:
    std::string asmCode;
    RegisterAllocator regAlloc;
    int stackOffset;
    std::map<std::string, int> varStackMap; // 变量栈偏移映射

    // 生成函数框架
    void emitPrologue(const std::string& funcName, int frameSize);
    void emitEpilogue(int frameSize);

    // 指令生成
    void emit(const std::string& instruction);
    void emitFunction(const FunctionInfo& func);
    
    // IR指令处理
    void generateAssignment(const IRInstruction& inst);
    void generateArithmetic(const IRInstruction& inst);
    void generateComparison(const IRInstruction& inst);
    void generateControlFlow(const IRInstruction& inst);
    void generateFunctionCall(const IRInstruction& inst);
    void generateReturn(const IRInstruction& inst);
    
    // 辅助方法
    std::string getRegOrLoad(const std::shared_ptr<Operand>& op);
    void storeIfTemp(const std::shared_ptr<Operand>& op, const std::string& reg);
};