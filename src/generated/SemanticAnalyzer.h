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
    SemanticAnalyzer();

    int getErrorCount() const { return errorCount; }

    // --- 核心访问方法重写 ---
    virtual std::any visitCompUnit(ToyCParser::CompUnitContext *ctx) override;
    virtual std::any visitFuncDef(ToyCParser::FuncDefContext *ctx) override;
    virtual std::any visitParam(ToyCParser::ParamContext *ctx) override;
    virtual std::any visitDeclStmt(ToyCParser::DeclStmtContext *ctx) override;
    virtual std::any visitAssignStmt(ToyCParser::AssignStmtContext *ctx) override;
    virtual std::any visitIfStmt(ToyCParser::IfStmtContext *ctx) override;
    virtual std::any visitWhileStmt(ToyCParser::WhileStmtContext *ctx) override;
    virtual std::any visitBreakStmt(ToyCParser::BreakStmtContext *ctx) override;
    virtual std::any visitContinueStmt(ToyCParser::ContinueStmtContext *ctx) override;
    virtual std::any visitReturnStmt(ToyCParser::ReturnStmtContext *ctx) override;
    virtual std::any visitExpr(ToyCParser::ExprContext *ctx) override;
    virtual std::any visitIdentifier(ToyCParser::IdentifierContext *ctx) override;
    virtual std::any visitNumberLiteral(ToyCParser::NumberLiteralContext *ctx) override;
    virtual std::any visitBlockStmt(ToyCParser::BlockStmtContext *ctx) override;
    virtual std::any visitEmptyStmt(ToyCParser::EmptyStmtContext *ctx) override;
    virtual std::any visitExprStmt(ToyCParser::ExprStmtContext *ctx) override;
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
    std::vector<std::unordered_map<std::string, SymbolInfo>> scopes;
    int errorCount;
    int loopDepth;
    std::string currentFunctionReturnType;
    std::unordered_map<std::string, SymbolInfo> functionTable; // 函数表
    std::unordered_map<std::string, bool> functionDefined; // 检查函数是否已定义
    std::string currentFunctionName;
    bool inFunction;
    bool hasReturnOnAllPaths;
    bool isMainChecked;
    int mainCount;

    SymbolInfo* lookupSymbol(const std::string& name);
    void reportError(const std::string& message, int line);
    void checkReturnOnAllPaths(ToyCParser::FuncDefContext *ctx);
    std::string getExprType(antlr4::ParserRuleContext* ctx);
};

#endif // SEMANTIC_ANALYZER_H