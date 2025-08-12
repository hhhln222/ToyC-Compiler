#include "SemanticAnalyzer.h"

SemanticAnalyzer::SemanticAnalyzer()
    : errorCount(0), loopDepth(0), currentFunctionReturnType(""),
      inFunction(false), hasReturnOnAllPaths(false), isMainChecked(false), mainCount(0) {
    scopes.push_back({});
}

// 访问编译单元的入口
std::any SemanticAnalyzer::visitCompUnit(ToyCParser::CompUnitContext *ctx) {
    mainCount = 0;
    functionTable.clear();
    functionDefined.clear();
    isMainChecked = false;
    // 检查所有函数定义
    for (auto funcDefCtx : ctx->funcDef()) {
        std::string funcName = funcDefCtx->ID()->getText();
        // 检查函数重名
        if (functionTable.count(funcName)) {
            reportError("函数 '" + funcName + "' 重复定义", funcDefCtx->start->getLine());
        } else {
            SymbolInfo funcInfo;
            funcInfo.type = SymbolInfo::FUNCTION;
            funcInfo.returnType = funcDefCtx->INT() ? "int" : "void";
            for (auto paramCtx : funcDefCtx->param()) {
                funcInfo.paramTypes.push_back("int");
            }
            functionTable[funcName] = funcInfo;
            functionDefined[funcName] = false;
        }
        // 检查main
        if (funcName == "main") {
            mainCount++;
            if (!funcDefCtx->INT() || !funcDefCtx->param().empty()) {
                reportError("main函数必须为int main()且无参数", funcDefCtx->start->getLine());
            }
        }
    }
    if (mainCount != 1) {
        reportError("必须有且只有一个int main()", ctx->start->getLine());
    }
    // 访问所有函数体
    for (auto funcDefCtx : ctx->funcDef()) {
        visit(funcDefCtx);
    }
    return nullptr;
}

// 访问函数定义
std::any SemanticAnalyzer::visitFuncDef(ToyCParser::FuncDefContext *ctx) {
    std::string funcName = ctx->ID()->getText();
    if (inFunction) {
        reportError("不允许在函数体内声明函数", ctx->start->getLine());
        return nullptr;
    }
    inFunction = true;
    currentFunctionName = funcName;
    currentFunctionReturnType = ctx->INT() ? "int" : "void";
    functionDefined[funcName] = true;
    // 新建作用域
    scopes.push_back({});
    // 参数加入作用域
    for (auto paramCtx : ctx->param()) {
        std::string paramName = paramCtx->ID()->getText();
        if (scopes.back().count(paramName)) {
            reportError("参数 '" + paramName + "' 重复定义", paramCtx->start->getLine());
        } else {
            SymbolInfo paramInfo;
            paramInfo.type = SymbolInfo::VARIABLE;
            paramInfo.varType = "int";
            scopes.back()[paramName] = paramInfo;
        }
    }
    // 检查return路径
    hasReturnOnAllPaths = false;
    visit(ctx->block());
    if (currentFunctionReturnType == "int" && !hasReturnOnAllPaths) {
        reportError("int型函数所有路径必须return int", ctx->start->getLine());
    }
    scopes.pop_back();
    inFunction = false;
    currentFunctionName = "";
    currentFunctionReturnType = "";
    return nullptr;
}

// 访问变量声明语句
std::any SemanticAnalyzer::visitDeclStmt(ToyCParser::DeclStmtContext *ctx) {
    std::string varName = ctx->ID()->getText();
    if (scopes.back().count(varName)) {
        reportError("变量 '" + varName + "' 重复声明", ctx->start->getLine());
    }
    if (!ctx->expr()) {
        reportError("变量声明必须初始化", ctx->start->getLine());
    }
    SymbolInfo varInfo;
    varInfo.type = SymbolInfo::VARIABLE;
    varInfo.varType = "int";
    scopes.back()[varName] = varInfo;
    visit(ctx->expr());
    return nullptr;
}

// 访问赋值语句
std::any SemanticAnalyzer::visitAssignStmt(ToyCParser::AssignStmtContext *ctx) {
    std::string varName = ctx->ID()->getText();
    SymbolInfo* symbol = lookupSymbol(varName);
    if (!symbol) {
        reportError("变量 '" + varName + "' 未声明", ctx->start->getLine());
    }
    // 检查右值类型
    std::string exprType = getExprType(ctx->expr());
    if (exprType == "void") {
        reportError("不能将void型函数调用作为赋值右值", ctx->start->getLine());
    }
    return nullptr;
}

// 访问if语句
std::any SemanticAnalyzer::visitIfStmt(ToyCParser::IfStmtContext *ctx) {
    std::string condType = getExprType(ctx->expr());
    if (condType == "void") {
        reportError("if条件不能为void型函数调用", ctx->start->getLine());
    }
    visit(ctx->stmt(0));
    if (ctx->stmt().size() > 1) {
        visit(ctx->stmt(1));
    }
    return nullptr;
}

// 访问while语句
std::any SemanticAnalyzer::visitWhileStmt(ToyCParser::WhileStmtContext *ctx) {
    std::string condType = getExprType(ctx->expr());
    if (condType == "void") {
        reportError("while条件不能为void型函数调用", ctx->start->getLine());
    }
    loopDepth++;
    visit(ctx->stmt());
    loopDepth--;
    return nullptr;
}

// 访问break语句
std::any SemanticAnalyzer::visitBreakStmt(ToyCParser::BreakStmtContext *ctx) {
    if (loopDepth == 0) {
        reportError("break只能出现在循环中", ctx->start->getLine());
    }
    return nullptr;
}

// 访问continue语句
std::any SemanticAnalyzer::visitContinueStmt(ToyCParser::ContinueStmtContext *ctx) {
    if (loopDepth == 0) {
        reportError("continue只能出现在循环中", ctx->start->getLine());
    }
    return nullptr;
}

// 访问return语句
std::any SemanticAnalyzer::visitReturnStmt(ToyCParser::ReturnStmtContext *ctx) {
    if (currentFunctionReturnType == "int") {
        if (!ctx->expr()) {
            reportError("int型函数return必须有返回值", ctx->start->getLine());
        } else {
            std::string retType = getExprType(ctx->expr());
            if (retType != "int") {
                reportError("int型函数return必须返回int", ctx->start->getLine());
            }
        }
        hasReturnOnAllPaths = true;
    } else if (currentFunctionReturnType == "void") {
        if (ctx->expr()) {
            reportError("void型函数return不能有返回值", ctx->start->getLine());
        }
    }
    return nullptr;
}

// 访问表达式
std::any SemanticAnalyzer::visitExpr(ToyCParser::ExprContext *ctx) {
    return visitChildren(ctx);
}

// 访问标识符
std::any SemanticAnalyzer::visitIdentifier(ToyCParser::IdentifierContext *ctx) {
    std::string varName = ctx->ID()->getText();
    SymbolInfo* symbol = lookupSymbol(varName);
    if (!symbol) {
        reportError("变量 '" + varName + "' 未声明", ctx->start->getLine());
    }
    return nullptr;
}

// 访问数字字面量
std::any SemanticAnalyzer::visitNumberLiteral(ToyCParser::NumberLiteralContext *ctx) {
    return nullptr;
}

std::any SemanticAnalyzer::visitBlockStmt(ToyCParser::BlockStmtContext *ctx) {
    scopes.push_back({});
    visit(ctx->block());
    scopes.pop_back();
    return nullptr;
}
std::any SemanticAnalyzer::visitEmptyStmt(ToyCParser::EmptyStmtContext *ctx) { return nullptr; }
std::any SemanticAnalyzer::visitExprStmt(ToyCParser::ExprStmtContext *ctx) { return visit(ctx->expr()); }
std::any SemanticAnalyzer::visitParam(ToyCParser::ParamContext *ctx) { return nullptr; }
std::any SemanticAnalyzer::visitBlock(ToyCParser::BlockContext *ctx) {
    for (auto stmt : ctx->stmt()) visit(stmt);
    return nullptr;
}
// 其他表达式类型直接visitChildren
std::any SemanticAnalyzer::visitMulAddExpr(ToyCParser::MulAddExprContext *ctx) { return visitChildren(ctx); }
std::any SemanticAnalyzer::visitSingleAdd(ToyCParser::SingleAddContext *ctx) { return visitChildren(ctx); }
std::any SemanticAnalyzer::visitSingleMul(ToyCParser::SingleMulContext *ctx) { return visitChildren(ctx); }
std::any SemanticAnalyzer::visitSingleUnary(ToyCParser::SingleUnaryContext *ctx) { return visitChildren(ctx); }
std::any SemanticAnalyzer::visitSingleRel(ToyCParser::SingleRelContext *ctx) { return visitChildren(ctx); }
std::any SemanticAnalyzer::visitSingleLAnd(ToyCParser::SingleLAndContext *ctx) { return visitChildren(ctx); }
std::any SemanticAnalyzer::visitSingleLOr(ToyCParser::SingleLOrContext *ctx) { return visitChildren(ctx); }
std::any SemanticAnalyzer::visitMulRelExpr(ToyCParser::MulRelExprContext *ctx) { return visitChildren(ctx); }
std::any SemanticAnalyzer::visitMulMulExpr(ToyCParser::MulMulExprContext *ctx) { return visitChildren(ctx); }
std::any SemanticAnalyzer::visitMulUnaryOp(ToyCParser::MulUnaryOpContext *ctx) { return visitChildren(ctx); }
std::any SemanticAnalyzer::visitMulLAndExpr(ToyCParser::MulLAndExprContext *ctx) { return visitChildren(ctx); }
std::any SemanticAnalyzer::visitMulLOrExpr(ToyCParser::MulLOrExprContext *ctx) { return visitChildren(ctx); }
std::any SemanticAnalyzer::visitParenthesizedExpr(ToyCParser::ParenthesizedExprContext *ctx) { return visit(ctx->expr()); }
std::any SemanticAnalyzer::visitFunctionCall(ToyCParser::FunctionCallContext *ctx) { 
    std::string funcName = ctx->ID()->getText();
    if (!functionTable.count(funcName)) {
        reportError("函数 '" + funcName + "' 未声明", ctx->start->getLine());
        return "int";
    }
    if (!functionDefined[funcName]) {
        reportError("函数 '" + funcName + "' 必须先声明后调用", ctx->start->getLine());
    }
    return functionTable[funcName].returnType;
}

// 辅助函数：查找变量
SymbolInfo* SemanticAnalyzer::lookupSymbol(const std::string& name) {
    for (int i = scopes.size() - 1; i >= 0; --i) {
        if (scopes[i].count(name)) {
            return &scopes[i][name];
        }
    }
    return nullptr;
}

// 报告语义错误
void SemanticAnalyzer::reportError(const std::string& message, int line) {
    std::cerr << "Semantic Error (Line " << line << "): " << message << std::endl;
    errorCount++;
}

// 获取表达式类型
std::string SemanticAnalyzer::getExprType(antlr4::ParserRuleContext* ctx) {
    // 只处理函数调用和字面量、变量
    if (auto call = dynamic_cast<ToyCParser::FunctionCallContext*>(ctx)) {
        std::string funcName = call->ID()->getText();
        if (functionTable.count(funcName)) {
            return functionTable[funcName].returnType;
        }
        return "int";
    }
    if (auto id = dynamic_cast<ToyCParser::IdentifierContext*>(ctx)) {
        return "int";
    }
    if (auto num = dynamic_cast<ToyCParser::NumberLiteralContext*>(ctx)) {
        return "int";
    }
    // 递归处理子节点
    for (size_t i = 0; i < ctx->children.size(); ++i) {
        auto child = dynamic_cast<antlr4::ParserRuleContext*>(ctx->children[i]);
        if (child) {
            std::string t = getExprType(child);
            if (t == "void") return "void";
        }
    }
    return "int";
}