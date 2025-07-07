#ifndef SEMANTIC_ANALYZER_H
#define SEMANTIC_ANALYZER_H

#include "antlr4-runtime.h"
#include "ToyCBaseVisitor.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

// 定义符号信息结构
struct SymbolInfo {
    enum SymbolType { VARIABLE, FUNCTION };
    SymbolType type;
    std::string varType;    // For VARIABLE (e.g., "int")
    std::string returnType; // For FUNCTION (e.g., "int", "void")
    std::vector<std::string> paramTypes; // For FUNCTION (e.g., {"int", "int"})
    // 你可以根据需要添加更多属性，例如：是否已初始化，是否是常量等
};

class SemanticAnalyzer : public ToyCBaseVisitor {
public:
    SemanticAnalyzer() : errorCount(0), loopDepth(0), currentFunctionReturnType("") {
        // 在最开始创建全局作用域
        scopes.push_back({});
    }

    int getErrorCount() const { return errorCount; }

    // --- 核心访问方法重写 ---

    // 访问编译单元的入口
    virtual std::any visitCompUnit(ToyCParser::CompUnitContext *ctx) override;

    // 访问函数定义
    virtual std::any visitFuncDef(ToyCParser::FuncDefContext *ctx) override;

    // 访问参数
    virtual std::any visitParam(ToyCParser::ParamContext *ctx) override;

    // 访问变量声明语句
    virtual std::any visitDeclStmt(ToyCParser::DeclStmtContext *ctx) override;

    // 访问赋值语句
    virtual std::any visitAssignStmt(ToyCParser::AssignStmtContext *ctx) override;

    // 访问 if 语句
    virtual std::any visitIfStmt(ToyCParser::IfStmtContext *ctx) override;

    // 访问 while 循环语句
    virtual std::any visitWhileStmt(ToyCParser::WhileStmtContext *ctx) override;

    // 访问 break 语句
    virtual std::any visitBreakStmt(ToyCParser::BreakStmtContext *ctx) override;

    // 访问 continue 语句
    virtual std::any visitContinueStmt(ToyCParser::ContinueStmtContext *ctx) override;

    // 访问 return 语句
    virtual std::any visitReturnStmt(ToyCParser::ReturnStmtContext *ctx) override;

    // 访问表达式 (这是一个通用的访问器，需要根据具体表达式类型进行细化)
    virtual std::any visitExpr(ToyCParser::ExprContext *ctx) override;

    // 访问标识符（例如变量使用）
    virtual std::any visitIdentifier(ToyCParser::IdentifierContext *ctx) override;

    // 访问数字字面量
    virtual std::any visitNumberLiteral(ToyCParser::NumberLiteralContext *ctx) override;
    
    virtual std::any visitBlockStmt(ToyCParser::BlockStmtContext *ctx) override;
    virtual std::any visitEmptyStmt(ToyCParser::EmptyStmtContext *ctx) override;
    virtual std::any visitExprStmt(ToyCParser::ExprStmtContext *ctx) override;

    // --- 新增的表达式和语句访问方法声明 ---
    virtual std::any visitMulAddExpr(ToyCParser::MulAddExprContext *ctx) override;
    virtual std::any visitSingleAdd(ToyCParser::SingleAddContext *ctx) override;
    virtual std::any visitSingleMul(ToyCParser::SingleMulContext *ctx) override;
    virtual std::any visitSingleUnary(ToyCParser::SingleUnaryContext *ctx) override;
    virtual std::any visitSingleRel(ToyCParser::SingleRelContext *ctx) override;
    virtual std::any visitSingleLAnd(ToyCParser::SingleLAndContext *ctx) override;
    virtual std::any visitSingleLOr(ToyCParser::SingleLOrContext *ctx) override;
    virtual std::any visitMulRelExpr(ToyCParser::MulRelExprContext *ctx) override;
    virtual std::any visitMulMulExpr(ToyCParser::MulMulExprContext *ctx) override;
    virtual std::any visitMulUnaryOp(ToyCParser::MulUnaryOpContext *ctx) override;
    virtual std::any visitMulLAndExpr(ToyCParser::MulLAndExprContext *ctx) override;
    virtual std::any visitMulLOrExpr(ToyCParser::MulLOrExprContext *ctx) override;
    virtual std::any visitBlock(ToyCParser::BlockContext *ctx) override;
    virtual std::any visitParenthesizedExpr(ToyCParser::ParenthesizedExprContext *ctx) override;
    virtual std::any visitFunctionCall(ToyCParser::FunctionCallContext *ctx) override;

private:
    // 符号表：一个栈，每个元素代表一个作用域（使用哈希表存储符号）
    std::vector<std::unordered_map<std::string, SymbolInfo>> scopes;
    int errorCount;           // 记录语义错误数量
    int loopDepth;            // 用于检查 break/continue 是否在循环内
    std::string currentFunctionReturnType; // 当前正在分析的函数的返回类型

    // 辅助函数：在符号表中查找标识符
    SymbolInfo* lookupSymbol(const std::string& name);

    // 报告语义错误
    void reportError(const std::string& message, int line);
};

#endif // SEMANTIC_ANALYZER_H