#include "IRGenerator.h"
#include <sstream>
#include <fstream>
#include <iostream>

// 辅助方法实现
std::string IRGenerator::generateTemp() {
    return std::to_string(tempCounter++);
}

std::string IRGenerator::generateLabel() {
    return std::to_string(labelCounter++);
}

void IRGenerator::addInstruction(const IRInstruction& inst) {
    if (currentFunction) {
        currentFunction->instructions.push_back(inst);
    }
}

std::shared_ptr<Operand> IRGenerator::createOperand(const std::string& value, OperandType type) {
    return std::make_shared<Operand>(type, value);
}

// 打印IR代码
void IRGenerator::printIR(const std::string& outputFile) const {
    std::ofstream out(outputFile);
    if (!out.is_open()) {
        std::cerr << "无法打开文件: " << outputFile << std::endl;
        return;
    }
    for (const auto& func : functions) {
        out << "\n=== Function: " << func.name << " ===" << std::endl;
        out << "Return type: " << func.returnType << std::endl;
        if (!func.params.empty()) {
            out << "Parameters: ";
            for (size_t i = 0; i < func.params.size(); ++i) {
                if (i > 0) out << ", ";
                out << func.params[i];
            }
            out << std::endl;
        }
        out << "Instructions:" << std::endl;
        
        for (size_t i = 0; i < func.instructions.size(); ++i) {
            out << "  " << i << ": " << func.instructions[i].toString() << std::endl;
        }
    }
    out.close();
}

// 访问编译单元
std::any IRGenerator::visitCompUnit(ToyCParser::CompUnitContext *ctx) {
    // 访问所有函数定义
    for (auto funcDef : ctx->funcDef()) {
        visit(funcDef);
    }
    return nullptr;
}

// 访问函数定义
std::any IRGenerator::visitFuncDef(ToyCParser::FuncDefContext *ctx) {
    std::string funcName = ctx->ID()->getText();
    std::string returnType = ctx->INT() ? "int" : "void";
    
    // 创建新函数
    functions.emplace_back(funcName, returnType);
    currentFunction = &functions.back();
    
    // 收集参数
    for (auto param : ctx->param()) {
        std::string paramName = param->ID()->getText();
        currentFunction->params.push_back(paramName);
    }
    
    // 访问函数体
    visit(ctx->block());
    
    currentFunction = nullptr;
    return nullptr;
}

// 访问变量声明语句
std::any IRGenerator::visitDeclStmt(ToyCParser::DeclStmtContext *ctx) {
    std::string varName = ctx->ID()->getText();
    
    // 如果有初始化表达式
    if (ctx->expr()) {
        auto exprResult = visit(ctx->expr());
        if (exprResult.has_value()) {
            auto operand = std::any_cast<std::shared_ptr<Operand>>(exprResult);
            auto varOperand = createOperand(varName, OperandType::VARIABLE);
            addInstruction(IRInstruction(IROpcode::ASSIGN, varOperand, operand));
        }
    }
    
    return nullptr;
}

// 访问赋值语句
std::any IRGenerator::visitAssignStmt(ToyCParser::AssignStmtContext *ctx) {
    std::string varName = ctx->ID()->getText();
    auto varOperand = createOperand(varName, OperandType::VARIABLE);
    
    auto exprResult = visit(ctx->expr());
    if (exprResult.has_value()) {
        auto operand = std::any_cast<std::shared_ptr<Operand>>(exprResult);
        addInstruction(IRInstruction(IROpcode::ASSIGN, varOperand, operand));
    }
    
    return nullptr;
}

// 访问if语句
std::any IRGenerator::visitIfStmt(ToyCParser::IfStmtContext *ctx) {
    std::string thenLabel = generateLabel();
    std::string elseLabel = generateLabel();
    std::string endLabel = generateLabel();
    
    // 计算条件表达式
    auto condResult = visit(ctx->expr());
    if (condResult.has_value()) {
        auto condOperand = std::any_cast<std::shared_ptr<Operand>>(condResult);
        
        // 如果条件为真，跳转到then部分
        addInstruction(IRInstruction(IROpcode::IF_GOTO, nullptr, condOperand, nullptr, thenLabel));
        
        // 否则跳转到else部分
        addInstruction(IRInstruction(IROpcode::GOTO, nullptr, nullptr, nullptr, elseLabel));
        
        // then部分标签
        addInstruction(IRInstruction(IROpcode::LABEL, nullptr, nullptr, nullptr, thenLabel));
        
        // 访问then部分
        visit(ctx->stmt(0));
        
        // 跳转到结束
        addInstruction(IRInstruction(IROpcode::GOTO, nullptr, nullptr, nullptr, endLabel));
        
        // else部分标签
        addInstruction(IRInstruction(IROpcode::LABEL, nullptr, nullptr, nullptr, elseLabel));
        
        // 如果有else部分
        if (ctx->stmt().size() > 1) {
            visit(ctx->stmt(1));
        }
        
        // 结束标签
        addInstruction(IRInstruction(IROpcode::LABEL, nullptr, nullptr, nullptr, endLabel));
    }
    
    return nullptr;
}

// 访问while语句
std::any IRGenerator::visitWhileStmt(ToyCParser::WhileStmtContext *ctx) {
    std::string loopLabel = generateLabel();
    std::string bodyLabel = generateLabel();
    std::string endLabel = generateLabel();
    
    // 循环开始标签
    addInstruction(IRInstruction(IROpcode::LABEL, nullptr, nullptr, nullptr, loopLabel));
    
    // 计算条件表达式
    auto condResult = visit(ctx->expr());
    if (condResult.has_value()) {
        auto condOperand = std::any_cast<std::shared_ptr<Operand>>(condResult);
        
        // 如果条件为真，跳转到循环体
        addInstruction(IRInstruction(IROpcode::IF_GOTO, nullptr, condOperand, nullptr, bodyLabel));
        
        // 否则跳转到结束
        addInstruction(IRInstruction(IROpcode::GOTO, nullptr, nullptr, nullptr, endLabel));
        
        // 循环体标签
        addInstruction(IRInstruction(IROpcode::LABEL, nullptr, nullptr, nullptr, bodyLabel));
        
        // 访问循环体
        visit(ctx->stmt());
        
        // 跳回循环开始
        addInstruction(IRInstruction(IROpcode::GOTO, nullptr, nullptr, nullptr, loopLabel));
        
        // 结束标签
        addInstruction(IRInstruction(IROpcode::LABEL, nullptr, nullptr, nullptr, endLabel));
    }
    
    return nullptr;
}

// 访问return语句
std::any IRGenerator::visitReturnStmt(ToyCParser::ReturnStmtContext *ctx) {
    if (ctx->expr()) {
        auto exprResult = visit(ctx->expr());
        if (exprResult.has_value()) {
            auto operand = std::any_cast<std::shared_ptr<Operand>>(exprResult);
            addInstruction(IRInstruction(IROpcode::RETURN, nullptr, operand));
        }
    } else {
        addInstruction(IRInstruction(IROpcode::RETURN));
    }
    
    return nullptr;
}

// 访问代码块
std::any IRGenerator::visitBlock(ToyCParser::BlockContext *ctx) {
    for (auto stmt : ctx->stmt()) {
        visit(stmt);
    }
    return nullptr;
}

// 访问表达式
std::any IRGenerator::visitExpr(ToyCParser::ExprContext *ctx) {
    return visit(ctx->lOrExpr());
}

// 访问标识符
std::any IRGenerator::visitIdentifier(ToyCParser::IdentifierContext *ctx) {
    std::string varName = ctx->ID()->getText();
    return std::make_any<std::shared_ptr<Operand>>(createOperand(varName, OperandType::VARIABLE));
}

// 访问数字字面量
std::any IRGenerator::visitNumberLiteral(ToyCParser::NumberLiteralContext *ctx) {
    std::string value = ctx->NUMBER()->getText();
    return std::make_any<std::shared_ptr<Operand>>(createOperand(value, OperandType::CONSTANT));
}

// 访问函数调用
std::any IRGenerator::visitFunctionCall(ToyCParser::FunctionCallContext *ctx) {
    std::string funcName = ctx->ID()->getText();
    auto funcOperand = createOperand(funcName, OperandType::VARIABLE);
    
    // 处理参数
    std::string paramList = "";
    for (size_t i = 0; i < ctx->expr().size(); ++i) {
        auto paramResult = visit(ctx->expr(i));
        if (paramResult.has_value()) {
            auto paramOperand = std::any_cast<std::shared_ptr<Operand>>(paramResult);
            addInstruction(IRInstruction(IROpcode::PARAM, nullptr, paramOperand));
            if (i > 0) paramList += ", ";
            paramList += paramOperand->toString();
        }
    }
    
    // 生成临时变量存储返回值
    std::string tempVar = generateTemp();
    auto tempOperand = createOperand(tempVar, OperandType::TEMP);
    auto paramListOperand = createOperand(paramList, OperandType::CONSTANT);
    
    addInstruction(IRInstruction(IROpcode::CALL, tempOperand, funcOperand, paramListOperand));
    
    return std::make_any<std::shared_ptr<Operand>>(tempOperand);
}

// 访问算术表达式
std::any IRGenerator::visitMulAddExpr(ToyCParser::MulAddExprContext *ctx) {
    auto leftResult = visit(ctx->addExpr());
    auto rightResult = visit(ctx->mulExpr());
    
    if (leftResult.has_value() && rightResult.has_value()) {
        auto leftOperand = std::any_cast<std::shared_ptr<Operand>>(leftResult);
        auto rightOperand = std::any_cast<std::shared_ptr<Operand>>(rightResult);
        
        std::string tempVar = generateTemp();
        auto tempOperand = createOperand(tempVar, OperandType::TEMP);
        
        IROpcode opcode;
        if (ctx->ADD()) opcode = IROpcode::ADD;
        else opcode = IROpcode::SUB;
        
        addInstruction(IRInstruction(opcode, tempOperand, leftOperand, rightOperand));
        return std::make_any<std::shared_ptr<Operand>>(tempOperand);
    }
    
    return std::any();
}

std::any IRGenerator::visitSingleAdd(ToyCParser::SingleAddContext *ctx) {
    return visit(ctx->mulExpr());
}

std::any IRGenerator::visitSingleMul(ToyCParser::SingleMulContext *ctx) {
    return visit(ctx->unaryExpr());
}

std::any IRGenerator::visitMulMulExpr(ToyCParser::MulMulExprContext *ctx) {
    auto leftResult = visit(ctx->mulExpr());
    auto rightResult = visit(ctx->unaryExpr());
    
    if (leftResult.has_value() && rightResult.has_value()) {
        auto leftOperand = std::any_cast<std::shared_ptr<Operand>>(leftResult);
        auto rightOperand = std::any_cast<std::shared_ptr<Operand>>(rightResult);
        
        std::string tempVar = generateTemp();
        auto tempOperand = createOperand(tempVar, OperandType::TEMP);
        
        IROpcode opcode;
        if (ctx->MUL()) opcode = IROpcode::MUL;
        else if (ctx->DIV()) opcode = IROpcode::DIV;
        else opcode = IROpcode::MOD;
        
        addInstruction(IRInstruction(opcode, tempOperand, leftOperand, rightOperand));
        return std::make_any<std::shared_ptr<Operand>>(tempOperand);
    }
    
    return std::any();
}

// 访问关系表达式
std::any IRGenerator::visitSingleRel(ToyCParser::SingleRelContext *ctx) {
    return visit(ctx->addExpr());
}

std::any IRGenerator::visitMulRelExpr(ToyCParser::MulRelExprContext *ctx) {
    auto leftResult = visit(ctx->relExpr());
    auto rightResult = visit(ctx->addExpr());
    
    if (leftResult.has_value() && rightResult.has_value()) {
        auto leftOperand = std::any_cast<std::shared_ptr<Operand>>(leftResult);
        auto rightOperand = std::any_cast<std::shared_ptr<Operand>>(rightResult);
        
        std::string tempVar = generateTemp();
        auto tempOperand = createOperand(tempVar, OperandType::TEMP);
        
        IROpcode opcode;
        if (ctx->LT()) opcode = IROpcode::LT;
        else if (ctx->GT()) opcode = IROpcode::GT;
        else if (ctx->LE()) opcode = IROpcode::LE;
        else if (ctx->GE()) opcode = IROpcode::GE;
        else if (ctx->EQ()) opcode = IROpcode::EQ;
        else opcode = IROpcode::NE;
        
        addInstruction(IRInstruction(opcode, tempOperand, leftOperand, rightOperand));
        return std::make_any<std::shared_ptr<Operand>>(tempOperand);
    }
    
    return std::any();
}

// 访问逻辑表达式
std::any IRGenerator::visitSingleLAnd(ToyCParser::SingleLAndContext *ctx) {
    return visit(ctx->relExpr());
}

std::any IRGenerator::visitMulLAndExpr(ToyCParser::MulLAndExprContext *ctx) {
    auto leftResult = visit(ctx->lAndExpr());
    auto rightResult = visit(ctx->relExpr());
    
    if (leftResult.has_value() && rightResult.has_value()) {
        auto leftOperand = std::any_cast<std::shared_ptr<Operand>>(leftResult);
        auto rightOperand = std::any_cast<std::shared_ptr<Operand>>(rightResult);
        
        std::string tempVar = generateTemp();
        auto tempOperand = createOperand(tempVar, OperandType::TEMP);
        
        addInstruction(IRInstruction(IROpcode::AND, tempOperand, leftOperand, rightOperand));
        return std::make_any<std::shared_ptr<Operand>>(tempOperand);
    }
    
    return std::any();
}

std::any IRGenerator::visitSingleLOr(ToyCParser::SingleLOrContext *ctx) {
    return visit(ctx->lAndExpr());
}

std::any IRGenerator::visitMulLOrExpr(ToyCParser::MulLOrExprContext *ctx) {
    auto leftResult = visit(ctx->lOrExpr());
    auto rightResult = visit(ctx->lAndExpr());
    
    if (leftResult.has_value() && rightResult.has_value()) {
        auto leftOperand = std::any_cast<std::shared_ptr<Operand>>(leftResult);
        auto rightOperand = std::any_cast<std::shared_ptr<Operand>>(rightResult);
        
        std::string tempVar = generateTemp();
        auto tempOperand = createOperand(tempVar, OperandType::TEMP);
        
        addInstruction(IRInstruction(IROpcode::OR, tempOperand, leftOperand, rightOperand));
        return std::make_any<std::shared_ptr<Operand>>(tempOperand);
    }
    
    return std::any();
}

// 访问一元表达式
std::any IRGenerator::visitSingleUnary(ToyCParser::SingleUnaryContext *ctx) {
    return visit(ctx->primaryExpr());
}

std::any IRGenerator::visitMulUnaryOp(ToyCParser::MulUnaryOpContext *ctx) {
    auto operandResult = visit(ctx->unaryExpr());
    
    if (operandResult.has_value()) {
        auto operand = std::any_cast<std::shared_ptr<Operand>>(operandResult);
        
        std::string tempVar = generateTemp();
        auto tempOperand = createOperand(tempVar, OperandType::TEMP);
        
        IROpcode opcode;
        if (ctx->ADD()) {
            // 正号，直接赋值
            addInstruction(IRInstruction(IROpcode::ASSIGN, tempOperand, operand));
        } else if (ctx->SUB()) {
            // 负号，0减去操作数
            auto zeroOperand = createOperand("0", OperandType::CONSTANT);
            addInstruction(IRInstruction(IROpcode::SUB, tempOperand, zeroOperand, operand));
        } else if (ctx->NOT()) {
            // 逻辑非
            addInstruction(IRInstruction(IROpcode::NOT, tempOperand, operand));
        }
        
        return std::make_any<std::shared_ptr<Operand>>(tempOperand);
    }
    
    return std::any();
}

// 访问括号表达式
std::any IRGenerator::visitParenthesizedExpr(ToyCParser::ParenthesizedExprContext *ctx) {
    return visit(ctx->expr());
}

// 其他必要的访问方法实现
std::any IRGenerator::visitBlockStmt(ToyCParser::BlockStmtContext *ctx) {
    return visit(ctx->block());
}

std::any IRGenerator::visitEmptyStmt(ToyCParser::EmptyStmtContext *ctx) {
    return nullptr;
}

std::any IRGenerator::visitExprStmt(ToyCParser::ExprStmtContext *ctx) {
    return visit(ctx->expr());
}

std::any IRGenerator::visitBreakStmt(ToyCParser::BreakStmtContext *ctx) {
    // TODO: 实现break语句的IR生成
    return nullptr;
}

std::any IRGenerator::visitContinueStmt(ToyCParser::ContinueStmtContext *ctx) {
    // TODO: 实现continue语句的IR生成
    return nullptr;
}

std::any IRGenerator::visitParam(ToyCParser::ParamContext *ctx) {
    return visitChildren(ctx);
} 