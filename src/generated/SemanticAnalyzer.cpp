#include "SemanticAnalyzer.h"

// 报告语义错误
void SemanticAnalyzer::reportError(const std::string& message, int line) {
    std::cerr << "Semantic Error (Line " << line << "): " << message << std::endl;
    errorCount++;
}

// 在符号表中查找标识符
SymbolInfo* SemanticAnalyzer::lookupSymbol(const std::string& name) {
    // 从当前作用域开始，向外层作用域查找
    for (int i = scopes.size() - 1; i >= 0; --i) {
        if (scopes[i].count(name)) {
            return &scopes[i][name];
        }
    }
    return nullptr; // 未找到
}

// 访问编译单元的入口
std::any SemanticAnalyzer::visitCompUnit(ToyCParser::CompUnitContext *ctx) {
    // 首先访问所有函数定义，将函数签名添加到全局符号表
    for (auto funcDefCtx : ctx->funcDef()) {
        std::string funcName = funcDefCtx->ID()->getText();
        
        // 获取函数返回类型：INT 或 VOID
        std::string returnType = "";
        if (funcDefCtx->INT() != nullptr) {
            returnType = funcDefCtx->INT()->getText();
        } else if (funcDefCtx->VOID() != nullptr) {
            returnType = funcDefCtx->VOID()->getText();
        } else {
            // 如果 grammar 设计良好，这个情况通常不会发生
            reportError("未知函数返回类型 '" + funcName + "'", funcDefCtx->start->getLine());
            returnType = "unknown"; 
        }

        if (scopes[0].count(funcName)) {
            reportError("函数 '" + funcName + "' 的重定义", funcDefCtx->start->getLine());
        } else {
            SymbolInfo funcInfo;
            funcInfo.type = SymbolInfo::FUNCTION;
            funcInfo.returnType = returnType;
            // 收集参数类型
            for (auto paramCtx : funcDefCtx->param()) {
                std::string paramType = "";
                // 修正：根据编译错误，ParamContext 只有 INT()，没有 VOID()
                if (paramCtx->INT() != nullptr) {
                    paramType = paramCtx->INT()->getText();
                } else {
                    // 如果不是 INT，则报告错误，因为 VOID() 不存在
                    reportError("参数类型非预期的类型 for function '" + funcName + "'. 期待 'int'.", paramCtx->start->getLine());
                    paramType = "unknown"; // 使用一个默认值，防止后续错误
                }
                funcInfo.paramTypes.push_back(paramType);
            }
            scopes[0][funcName] = funcInfo;
        }
    }

    // 检查 main 函数是否存在及签名
    if (!scopes[0].count("main")) {
        reportError("未找到 'main' 函数", ctx->stop->getLine()); 
    } else {
        SymbolInfo* mainInfo = &scopes[0]["main"];
        // 假设 'main' 必须是 'int main()'，没有参数
        if (mainInfo->type != SymbolInfo::FUNCTION || mainInfo->returnType != "int" || !mainInfo->paramTypes.empty()) {
            reportError("'main' 函数必须具有签名 'int main()'", ctx->stop->getLine());
        }
    }

    // 继续访问所有子节点，包括函数体内的语句
    return visitChildren(ctx);
}
// 访问函数定义 (现在处理函数体内部的语义)
std::any SemanticAnalyzer::visitFuncDef(ToyCParser::FuncDefContext *ctx) {
    // 确保我们处理的是已经注册在全局符号表中的函数
    std::string funcName = ctx->ID()->getText();
    SymbolInfo* funcInfo = lookupSymbol(funcName); // 查找全局符号表中的函数信息

    if (!funcInfo || funcInfo->type != SymbolInfo::FUNCTION) {
        // 如果这里出现错误，说明 visitCompUnit 中可能漏掉了某些情况，
        // 或者解析树结构不符合预期。但理论上这里应该能找到。
        reportError("内部错误：未找到函数 '" + funcName + "' 的定义", ctx->start->getLine());
        return nullptr;
    }

    // 存储当前函数的返回类型，用于检查 return 语句
    std::string returnType = "";
    if (ctx->INT() != nullptr) {
        returnType = ctx->INT()->getText();
    } else if (ctx->VOID() != nullptr) {
        returnType = ctx->VOID()->getText();
    }
    currentFunctionReturnType = returnType;

    // 进入新的作用域 (函数作用域)
    scopes.push_back({}); 

    // 将参数添加到当前函数作用域
    for (size_t i = 0; i < ctx->param().size(); ++i) {
        auto paramCtx = ctx->param(i);
        std::string paramName = paramCtx->ID()->getText();
        std::string paramType = "";

        if (paramCtx->INT() != nullptr) {
            paramType = paramCtx->INT()->getText();
        } else {
            // 这与 visitCompUnit 中的错误报告一致
            reportError("参数类型非预期 for parameter '" + paramName + "'. 期待 'int'.", paramCtx->start->getLine());
            paramType = "unknown";
        }

        if (scopes.back().count(paramName)) {
            reportError("参数 '" + paramName + "' 的重定义", paramCtx->start->getLine());
        } else {
            SymbolInfo paramInfo;
            paramInfo.type = SymbolInfo::VARIABLE;
            paramInfo.varType = paramType;
            scopes.back()[paramName] = paramInfo;
        }
    }

    // 访问函数体
    visit(ctx->block());

    // 退出当前作用域 (函数作用域)
    scopes.pop_back();

    currentFunctionReturnType = ""; // 重置，防止影响下一个函数

    return nullptr; // 函数定义本身不返回一个值
}

// 访问变量声明语句
std::any SemanticAnalyzer::visitDeclStmt(ToyCParser::DeclStmtContext *ctx) {
    std::string varName = ctx->ID()->getText();
    std::string varType = "";

    // 获取变量类型：INT
    if (ctx->INT() != nullptr) {
        varType = ctx->INT()->getText();
    } else {
        reportError("未知变量类型 for '" + varName + "'. 期待 'int'.", ctx->start->getLine());
        varType = "unknown";
    }

    // 检查当前作用域中是否已存在同名变量
    if (scopes.back().count(varName)) {
        reportError("变量 '" + varName + "' 的重定义", ctx->start->getLine());
    } else {
        SymbolInfo varInfo;
        varInfo.type = SymbolInfo::VARIABLE;
        varInfo.varType = varType;
        scopes.back()[varName] = varInfo; // 将变量添加到当前作用域
    }

    // 如果有初始化表达式
    if (ctx->expr() != nullptr) {
        std::any exprType = visit(ctx->expr()); // 访问表达式获取其类型
        if (exprType.has_value() && std::any_cast<std::string>(exprType) != varType) {
            reportError("变量 '" + varName + "' 初始化类型不匹配. 期待 '" + varType + "'", ctx->expr()->start->getLine());
        }
    }

    return nullptr; // 声明语句本身不返回一个值
}

// 访问参数 (因为在 visitFuncDef 中已经处理了，这里可以简单地访问子节点)
std::any SemanticAnalyzer::visitParam(ToyCParser::ParamContext *ctx) {
    return visitChildren(ctx);
}

// 访问赋值语句
std::any SemanticAnalyzer::visitAssignStmt(ToyCParser::AssignStmtContext *ctx) {
    std::string varName = ctx->ID()->getText();
    SymbolInfo* symbol = lookupSymbol(varName);

    if (!symbol) {
        reportError("Undeclared variable '" + varName + "'", ctx->start->getLine());
        return {};
    }
    if (symbol->type != SymbolInfo::VARIABLE) {
        reportError("Cannot assign to non-variable identifier '" + varName + "'", ctx->start->getLine());
        return {};
    }

    // 检查赋值表达式的类型
    std::any exprResult = visit(ctx->expr());
    if (exprResult.has_value()) {
        std::string exprType = std::any_cast<std::string>(exprResult);
        // 在ToyC中，假定所有变量都是int，所以赋值表达式也必须是int
        if (exprType != symbol->varType) {
            reportError("Type mismatch in assignment to '" + varName + "'. Expected '" + symbol->varType + "', got '" + exprType + "'", ctx->start->getLine());
        }
    }
    return {};
}

// 访问 if 语句
std::any SemanticAnalyzer::visitIfStmt(ToyCParser::IfStmtContext *ctx) {
    std::any condResult = visit(ctx->expr());
    if (condResult.has_value()) {
        std::string condType = std::any_cast<std::string>(condResult);
        if (condType != "int") { // 条件表达式必须是int类型
            reportError("Condition in 'if' statement must be an integer expression, got '" + condType + "'", ctx->start->getLine());
        }
    }
    return visitChildren(ctx);
}

// 访问 while 循环语句
std::any SemanticAnalyzer::visitWhileStmt(ToyCParser::WhileStmtContext *ctx) {
    std::any condResult = visit(ctx->expr());
    if (condResult.has_value()) {
        std::string condType = std::any_cast<std::string>(condResult);
        if (condType != "int") { // 循环条件必须是int类型
            reportError("Condition in 'while' statement must be an integer expression, got '" + condType + "'", ctx->start->getLine());
        }
    }
    loopDepth++; // 增加循环嵌套深度
    std::any result = visitChildren(ctx);
    loopDepth--; // 减少循环嵌套深度
    return result;
}

// 访问 break 语句
std::any SemanticAnalyzer::visitBreakStmt(ToyCParser::BreakStmtContext *ctx) {
    if (loopDepth == 0) {
        reportError("'break' statement used outside of a loop", ctx->start->getLine());
    }
    return visitChildren(ctx);
}

// 访问 continue 语句
std::any SemanticAnalyzer::visitContinueStmt(ToyCParser::ContinueStmtContext *ctx) {
    if (loopDepth == 0) {
        reportError("'continue' statement used outside of a loop", ctx->start->getLine());
    }
    return visitChildren(ctx);
}

// 访问 return 语句
std::any SemanticAnalyzer::visitReturnStmt(ToyCParser::ReturnStmtContext *ctx) {
    if (ctx->expr() != nullptr) { // 有返回表达式
        std::any exprResult = visit(ctx->expr());
        if (exprResult.has_value()) {
            std::string actualReturnType = std::any_cast<std::string>(exprResult);
            if (currentFunctionReturnType == "void") {
                reportError("Void function returns a value", ctx->start->getLine());
            } else if (actualReturnType != currentFunctionReturnType) {
                reportError("Return type mismatch. Expected '" + currentFunctionReturnType + "', got '" + actualReturnType + "'", ctx->start->getLine());
            }
        }
    } else { // 没有返回表达式 (return;)
        if (currentFunctionReturnType != "void") {
            reportError("Non-void function missing return value", ctx->start->getLine());
        }
    }
    return visitChildren(ctx);
}

// 访问表达式 (ExprContext是所有表达式的父规则，需要向下转型到具体类型)
std::any SemanticAnalyzer::visitExpr(ToyCParser::ExprContext *ctx) {
    // 对于ToyC，所有的表达式结果类型都认为是int
    // 实际的类型检查发生在具体的算术/逻辑/关系表达式的visit方法中
    // 这里简单地递归访问子表达式
    if (ctx->lOrExpr() != nullptr) {
        return visit(ctx->lOrExpr());
    }
    return std::any(std::string("int")); // 默认所有表达式都是int类型
}

// 访问标识符（例如变量使用）
std::any SemanticAnalyzer::visitIdentifier(ToyCParser::IdentifierContext *ctx) {
    std::string name = ctx->ID()->getText();
    SymbolInfo* symbolInfo = lookupSymbol(name);

    int line = ctx->start->getLine();

    ToyCParser::FunctionCallContext* funcCallCtx = dynamic_cast<ToyCParser::FunctionCallContext*>(ctx->parent);
    if (funcCallCtx != nullptr) {
        // 这个标识符是函数调用的一部分
        if (!symbolInfo || symbolInfo->type != SymbolInfo::FUNCTION) {
            reportError("Undeclared function '" + name + "' or not a function", line);
            return std::any(std::string("unknown")); // 返回 unknown 类型
        }

        // 参数数量检查 (可以在这里进行，也可以在 visitFunctionCall 中更详细地处理)
        // 确保funcCallCtx->expr()能够正确获取到参数表达式
        if (funcCallCtx->expr().size() != symbolInfo->paramTypes.size()) {
            reportError("Function '" + name + "' called with incorrect number of arguments", line);
            // 仍然返回函数预期返回类型，以便后续分析继续
            return std::any(symbolInfo->returnType);
        }
        return std::any(symbolInfo->returnType);
    } else {
        // 检查是否是变量使用
        if (!symbolInfo || symbolInfo->type != SymbolInfo::VARIABLE) {
            reportError("Undeclared variable '" + name + "' or not a variable", line);
            return std::any(std::string("unknown")); // 返回 unknown 类型
        }
        // 返回变量类型
        return std::any(symbolInfo->varType);
    }
}
// 访问数字字面量
std::any SemanticAnalyzer::visitNumberLiteral(ToyCParser::NumberLiteralContext *ctx) {
    return std::any(std::string("int")); // 所有数字都是int
}

// ... 你还需要实现所有其他 visit* 方法，例如：

std::any SemanticAnalyzer::visitMulAddExpr(ToyCParser::MulAddExprContext *ctx) {
    // 假设左右操作数都是int，结果也是int
    std::any leftType = visit(ctx->addExpr());
    std::any rightType = visit(ctx->mulExpr());

    if (leftType.has_value() && rightType.has_value()) {
        std::string lt = std::any_cast<std::string>(leftType);
        std::string rt = std::any_cast<std::string>(rightType);
        if (lt != "int" || rt != "int") {
            reportError("Arithmetic operations require integer operands", ctx->start->getLine());
            return std::any(std::string("unknown"));
        }
    } else {
        return std::any(std::string("unknown")); // 子表达式有错误
    }
    return std::any(std::string("int")); // 返回结果类型
}

// 对于那些只包含一个子表达式的规则 (例如 single* 规则)，直接访问子节点
std::any SemanticAnalyzer::visitSingleAdd(ToyCParser::SingleAddContext *ctx) {
    return visit(ctx->mulExpr());
}
std::any SemanticAnalyzer::visitSingleMul(ToyCParser::SingleMulContext *ctx) {
    return visit(ctx->unaryExpr());
}
std::any SemanticAnalyzer::visitSingleUnary(ToyCParser::SingleUnaryContext *ctx) {
    return visit(ctx->primaryExpr());
}
std::any SemanticAnalyzer::visitSingleRel(ToyCParser::SingleRelContext *ctx) {
    return visit(ctx->addExpr());
}
std::any SemanticAnalyzer::visitSingleLAnd(ToyCParser::SingleLAndContext *ctx) {
    return visit(ctx->relExpr());
}
std::any SemanticAnalyzer::visitSingleLOr(ToyCParser::SingleLOrContext *ctx) {
    return visit(ctx->lAndExpr());
}
// 对于其他复合表达式，例如 MulRelExpr, MulLAndExpr, MulLOrExpr
std::any SemanticAnalyzer::visitMulRelExpr(ToyCParser::MulRelExprContext *ctx) {
    // 关系运算符 (>, <, ==, !=等)
    std::any leftType = visit(ctx->relExpr());
    std::any rightType = visit(ctx->addExpr());
    if (leftType.has_value() && rightType.has_value()) {
        std::string lt = std::any_cast<std::string>(leftType);
        std::string rt = std::any_cast<std::string>(rightType);
        if (lt != "int" || rt != "int") {
            reportError("Relational operations require integer operands", ctx->start->getLine());
            return std::any(std::string("unknown"));
        }
    } else {
        return std::any(std::string("unknown"));
    }
    return std::any(std::string("int")); // 关系操作结果在ToyC中视为int (0或1)
}

std::any SemanticAnalyzer::visitMulMulExpr(ToyCParser::MulMulExprContext *ctx) {
    std::any leftType = visit(ctx->mulExpr());
    std::any rightType = visit(ctx->unaryExpr());
    if (leftType.has_value() && rightType.has_value()) {
        std::string lt = std::any_cast<std::string>(leftType);
        std::string rt = std::any_cast<std::string>(rightType);
        if (lt != "int" || rt != "int") {
            reportError("Multiplicative operations require integer operands", ctx->start->getLine());
            return std::any(std::string("unknown"));
        }
    } else {
        return std::any(std::string("unknown"));
    }
    return std::any(std::string("int"));
}

std::any SemanticAnalyzer::visitMulUnaryOp(ToyCParser::MulUnaryOpContext *ctx) {
    std::any operandType = visit(ctx->unaryExpr());
    if (operandType.has_value()) {
        std::string ot = std::any_cast<std::string>(operandType);
        if (ot != "int") {
            reportError("Unary operations (+, -, !) require integer operands", ctx->start->getLine());
            return std::any(std::string("unknown"));
        }
    } else {
        return std::any(std::string("unknown"));
    }
    return std::any(std::string("int"));
}


std::any SemanticAnalyzer::visitMulLAndExpr(ToyCParser::MulLAndExprContext *ctx) {
    std::any leftType = visit(ctx->lAndExpr());
    std::any rightType = visit(ctx->relExpr());
    if (leftType.has_value() && rightType.has_value()) {
        std::string lt = std::any_cast<std::string>(leftType);
        std::string rt = std::any_cast<std::string>(rightType);
        if (lt != "int" || rt != "int") {
            reportError("Logical AND operations require integer operands", ctx->start->getLine());
            return std::any(std::string("unknown"));
        }
    } else {
        return std::any(std::string("unknown"));
    }
    return std::any(std::string("int"));
}

std::any SemanticAnalyzer::visitMulLOrExpr(ToyCParser::MulLOrExprContext *ctx) {
    std::any leftType = visit(ctx->lOrExpr());
    std::any rightType = visit(ctx->lAndExpr());
    if (leftType.has_value() && rightType.has_value()) {
        std::string lt = std::any_cast<std::string>(leftType);
        std::string rt = std::any_cast<std::string>(rightType);
        if (lt != "int" || rt != "int") {
            reportError("Logical OR operations require integer operands", ctx->start->getLine());
            return std::any(std::string("unknown"));
        }
    } else {
        return std::any(std::string("unknown"));
    }
    return std::any(std::string("int"));
}

// 访问 Block (块语句)
std::any SemanticAnalyzer::visitBlock(ToyCParser::BlockContext *ctx) {
    return visitChildren(ctx); // 简单地访问所有子语句
}
// 访问其他不涉及特定语义检查的语句，直接访问其子节点
std::any SemanticAnalyzer::visitBlockStmt(ToyCParser::BlockStmtContext *ctx) {
    return visitChildren(ctx);
}
std::any SemanticAnalyzer::visitEmptyStmt(ToyCParser::EmptyStmtContext *ctx) {
    return visitChildren(ctx);
}
std::any SemanticAnalyzer::visitExprStmt(ToyCParser::ExprStmtContext *ctx) {
    return visitChildren(ctx);
}

// 对于PrimaryExpr的不同上下文，例如括号内的表达式
std::any SemanticAnalyzer::visitParenthesizedExpr(ToyCParser::ParenthesizedExprContext *ctx) {
    return visit(ctx->expr());
}
// 对于FunctionCall，部分处理在visitIdentifier中，这里可以补充参数类型检查
std::any SemanticAnalyzer::visitFunctionCall(ToyCParser::FunctionCallContext *ctx) {
    std::string funcName = ctx->ID()->getText();
    SymbolInfo* funcInfo = lookupSymbol(funcName);

    if (!funcInfo || funcInfo->type != SymbolInfo::FUNCTION) {
        // 错误已经在 visitIdentifier 中报告，这里可能不需要重复
        return std::any(std::string("unknown"));
    }

    // 检查参数数量
    if (ctx->expr().size() != funcInfo->paramTypes.size()) {
        // 错误已经在 visitIdentifier 中报告
    }

    // 逐个检查参数类型
    for (size_t i = 0; i < ctx->expr().size() && i < funcInfo->paramTypes.size(); ++i) {
        std::any actualParamType = visit(ctx->expr(i));
        if (actualParamType.has_value()) {
            std::string apt = std::any_cast<std::string>(actualParamType);
            if (apt != funcInfo->paramTypes[i]) { // 假定都是int
                reportError("Type mismatch for argument " + std::to_string(i+1) + " in call to '" + funcName + "'. Expected '" + funcInfo->paramTypes[i] + "', got '" + apt + "'", ctx->start->getLine());
            }
        }
    }
    return std::any(funcInfo->returnType);
}