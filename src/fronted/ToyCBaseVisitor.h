
// Generated from ToyC.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "ToyCVisitor.h"


/**
 * This class provides an empty implementation of ToyCVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  ToyCBaseVisitor : public ToyCVisitor {
public:

  virtual std::any visitCompUnit(ToyCParser::CompUnitContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFuncDef(ToyCParser::FuncDefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParam(ToyCParser::ParamContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlockStmt(ToyCParser::BlockStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEmptyStmt(ToyCParser::EmptyStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExprStmt(ToyCParser::ExprStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssignStmt(ToyCParser::AssignStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDeclStmt(ToyCParser::DeclStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIfStmt(ToyCParser::IfStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitWhileStmt(ToyCParser::WhileStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBreakStmt(ToyCParser::BreakStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitContinueStmt(ToyCParser::ContinueStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitReturnStmt(ToyCParser::ReturnStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlock(ToyCParser::BlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpr(ToyCParser::ExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMulLOrExpr(ToyCParser::MulLOrExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSingleLOr(ToyCParser::SingleLOrContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSingleLAnd(ToyCParser::SingleLAndContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMulLAndExpr(ToyCParser::MulLAndExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSingleRel(ToyCParser::SingleRelContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMulRelExpr(ToyCParser::MulRelExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMulAddExpr(ToyCParser::MulAddExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSingleAdd(ToyCParser::SingleAddContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSingleMul(ToyCParser::SingleMulContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMulMulExpr(ToyCParser::MulMulExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSingleUnary(ToyCParser::SingleUnaryContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMulUnaryOp(ToyCParser::MulUnaryOpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIdentifier(ToyCParser::IdentifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNumberLiteral(ToyCParser::NumberLiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParenthesizedExpr(ToyCParser::ParenthesizedExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionCall(ToyCParser::FunctionCallContext *ctx) override {
    return visitChildren(ctx);
  }


};

