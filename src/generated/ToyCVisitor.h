
// Generated from ToyC.g4 by ANTLR 4.12.0

#pragma once


#include "antlr4-runtime.h"
#include "ToyCParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by ToyCParser.
 */
class  ToyCVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by ToyCParser.
   */
    virtual std::any visitCompUnit(ToyCParser::CompUnitContext *context) = 0;

    virtual std::any visitFuncDef(ToyCParser::FuncDefContext *context) = 0;

    virtual std::any visitParam(ToyCParser::ParamContext *context) = 0;

    virtual std::any visitBlockStmt(ToyCParser::BlockStmtContext *context) = 0;

    virtual std::any visitEmptyStmt(ToyCParser::EmptyStmtContext *context) = 0;

    virtual std::any visitExprStmt(ToyCParser::ExprStmtContext *context) = 0;

    virtual std::any visitAssignStmt(ToyCParser::AssignStmtContext *context) = 0;

    virtual std::any visitDeclStmt(ToyCParser::DeclStmtContext *context) = 0;

    virtual std::any visitIfStmt(ToyCParser::IfStmtContext *context) = 0;

    virtual std::any visitWhileStmt(ToyCParser::WhileStmtContext *context) = 0;

    virtual std::any visitBreakStmt(ToyCParser::BreakStmtContext *context) = 0;

    virtual std::any visitContinueStmt(ToyCParser::ContinueStmtContext *context) = 0;

    virtual std::any visitReturnStmt(ToyCParser::ReturnStmtContext *context) = 0;

    virtual std::any visitBlock(ToyCParser::BlockContext *context) = 0;

    virtual std::any visitExpr(ToyCParser::ExprContext *context) = 0;

    virtual std::any visitMulLOrExpr(ToyCParser::MulLOrExprContext *context) = 0;

    virtual std::any visitSingleLOr(ToyCParser::SingleLOrContext *context) = 0;

    virtual std::any visitSingleLAnd(ToyCParser::SingleLAndContext *context) = 0;

    virtual std::any visitMulLAndExpr(ToyCParser::MulLAndExprContext *context) = 0;

    virtual std::any visitSingleRel(ToyCParser::SingleRelContext *context) = 0;

    virtual std::any visitMulRelExpr(ToyCParser::MulRelExprContext *context) = 0;

    virtual std::any visitMulAddExpr(ToyCParser::MulAddExprContext *context) = 0;

    virtual std::any visitSingleAdd(ToyCParser::SingleAddContext *context) = 0;

    virtual std::any visitSingleMul(ToyCParser::SingleMulContext *context) = 0;

    virtual std::any visitMulMulExpr(ToyCParser::MulMulExprContext *context) = 0;

    virtual std::any visitSingleUnary(ToyCParser::SingleUnaryContext *context) = 0;

    virtual std::any visitMulUnaryOp(ToyCParser::MulUnaryOpContext *context) = 0;

    virtual std::any visitIdentifier(ToyCParser::IdentifierContext *context) = 0;

    virtual std::any visitNumberLiteral(ToyCParser::NumberLiteralContext *context) = 0;

    virtual std::any visitParenthesizedExpr(ToyCParser::ParenthesizedExprContext *context) = 0;

    virtual std::any visitFunctionCall(ToyCParser::FunctionCallContext *context) = 0;


};

