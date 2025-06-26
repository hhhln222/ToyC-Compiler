
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

    virtual std::any visitBlock(ToyCParser::BlockContext *context) = 0;

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

    virtual std::any visitExpr(ToyCParser::ExprContext *context) = 0;

    virtual std::any visitLOrExpr(ToyCParser::LOrExprContext *context) = 0;

    virtual std::any visitLAndExpr(ToyCParser::LAndExprContext *context) = 0;

    virtual std::any visitRelExpr(ToyCParser::RelExprContext *context) = 0;

    virtual std::any visitAddExpr(ToyCParser::AddExprContext *context) = 0;

    virtual std::any visitMulExpr(ToyCParser::MulExprContext *context) = 0;

    virtual std::any visitUnaryExpr(ToyCParser::UnaryExprContext *context) = 0;

    virtual std::any visitIdExpr(ToyCParser::IdExprContext *context) = 0;

    virtual std::any visitNumExpr(ToyCParser::NumExprContext *context) = 0;

    virtual std::any visitParenExpr(ToyCParser::ParenExprContext *context) = 0;

    virtual std::any visitCallExpr(ToyCParser::CallExprContext *context) = 0;


};

