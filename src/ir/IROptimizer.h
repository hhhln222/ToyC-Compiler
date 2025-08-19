#ifndef IR_OPTIMIZER_H
#define IR_OPTIMIZER_H

#include "IRGenerator.h"
#include <unordered_map>
#include <vector>
#include <unordered_set>
#include <memory>
#include <algorithm>

// 基本块结构
struct BasicBlock {
    std::string label;  // 基本块入口标号（可为空）
    std::vector<IRInstruction> instructions;  // 块内指令
    std::unordered_set<BasicBlock*> predecessors;  // 前驱基本块
    std::unordered_set<BasicBlock*> successors;    // 后继基本块

    // 构造函数
    BasicBlock(std::string lab = "") : label(std::move(lab)) {}
};

struct LiveRange {
    int start; // 起始指令位置
    int end;   // 结束指令位置
};

class LiveAnalyzer {
public:
    void analyze(const std::vector<IRInstruction>& instructions);
    bool canShareSlot(const std::string& var1, const std::string& var2) const;
    const std::map<std::string, LiveRange>& getLiveRanges() const;
    
private:
    std::map<std::string, LiveRange> liveRanges;
};

// 常量映射：变量名 -> 确定的常量值
using ConstantMap = std::unordered_map<std::string, int>;


class IROptimizer {
public:
    // 对所有函数进行优化
    void optimize(std::vector<FunctionInfo>& functions);
    void printIR(const std::string& outputFile,std::vector<FunctionInfo>& functions);
    void printBasicBlocks(const std::string& outputFile, const std::vector<BasicBlock>& blocks);

private:
    struct BlockConstantInfo {
        ConstantMap in;  // 进入基本块时的常量映射
        ConstantMap out; // 离开基本块时的常量映射
    };
    // 基本块相关
    std::vector<BasicBlock> splitIntoBasicBlocks(FunctionInfo& func);  // 分割基本块
    void buildCFG(std::vector<BasicBlock>& blocks);  // 构建控制流图
    void mergeBasicBlocks(FunctionInfo& func, const std::vector<BasicBlock>& blocks);  // 合并基本块回函数

    // 优化方法适配基本块
    void constantFolding(BasicBlock& block, bool& changed);
    void deadCodeElimination(std::vector<BasicBlock>& blocks, const LiveAnalyzer& liveAnalyzer, bool& changed);
    void algebraicSimplification(BasicBlock& block, bool& changed);
    void copyPropagation(BasicBlock& block, bool& changed);
    void commonSubexpressionElimination(BasicBlock& block, bool& changed);
    void eliminateUnreachableBlocks(std::vector<BasicBlock>& blocks, bool& changed);
    void constantConditionOptimization(std::vector<BasicBlock>& blocks, bool& changed);
    std::vector<BlockConstantInfo> analyzeInterBlockConstants(const std::vector<BasicBlock>& blocks);
    void applyInterBlockConstantPropagation(std::vector<BasicBlock>& blocks, 
                                           const std::vector<BlockConstantInfo>& blockInfos, 
                                           bool& changed);

    // 辅助函数
    std::shared_ptr<Operand> computeBinaryOp(
        IROpcode opcode, 
        const std::shared_ptr<Operand>& arg1, 
        const std::shared_ptr<Operand>& arg2
    );
    void updateVariableCounts(FunctionInfo& func);
    std::shared_ptr<Operand> createConstant(int value) {
        return std::make_shared<Operand>(OperandType::CONSTANT, std::to_string(value), -1);
    }
};

#endif // IR_OPTIMIZER_H