
// Generated from ToyC.g4 by ANTLR 4.12.0

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

  virtual std::any visitBlock(ToyCParser::BlockContext *ctx) override {
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

  virtual std::any visitExpr(ToyCParser::ExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLOrExpr(ToyCParser::LOrExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLAndExpr(ToyCParser::LAndExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRelExpr(ToyCParser::RelExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAddExpr(ToyCParser::AddExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMulExpr(ToyCParser::MulExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUnaryExpr(ToyCParser::UnaryExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIdExpr(ToyCParser::IdExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNumExpr(ToyCParser::NumExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParenExpr(ToyCParser::ParenExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCallExpr(ToyCParser::CallExprContext *ctx) override {
    return visitChildren(ctx);
  }


};

