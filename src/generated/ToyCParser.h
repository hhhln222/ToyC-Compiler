
// Generated from ToyC.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"




class  ToyCParser : public antlr4::Parser {
public:
  enum {
    INT = 1, VOID = 2, IF = 3, ELSE = 4, WHILE = 5, BREAK = 6, CONTINUE = 7, 
    RETURN = 8, OR = 9, AND = 10, LT = 11, GT = 12, LE = 13, GE = 14, EQ = 15, 
    NE = 16, ADD = 17, SUB = 18, MUL = 19, DIV = 20, MOD = 21, NOT = 22, 
    ASSIGN = 23, SEMI = 24, COMMA = 25, LPAREN = 26, RPAREN = 27, LBRACE = 28, 
    RBRACE = 29, ID = 30, NUMBER = 31, LINE_COMMENT = 32, COMMENT = 33, 
    WS = 34
  };

  enum {
    RuleCompUnit = 0, RuleFuncDef = 1, RuleParam = 2, RuleStmt = 3, RuleBlock = 4, 
    RuleExpr = 5, RuleLOrExpr = 6, RuleLAndExpr = 7, RuleRelExpr = 8, RuleAddExpr = 9, 
    RuleMulExpr = 10, RuleUnaryExpr = 11, RulePrimaryExpr = 12
  };

  explicit ToyCParser(antlr4::TokenStream *input);

  ToyCParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~ToyCParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class CompUnitContext;
  class FuncDefContext;
  class ParamContext;
  class StmtContext;
  class BlockContext;
  class ExprContext;
  class LOrExprContext;
  class LAndExprContext;
  class RelExprContext;
  class AddExprContext;
  class MulExprContext;
  class UnaryExprContext;
  class PrimaryExprContext; 

  class  CompUnitContext : public antlr4::ParserRuleContext {
  public:
    CompUnitContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<FuncDefContext *> funcDef();
    FuncDefContext* funcDef(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CompUnitContext* compUnit();

  class  FuncDefContext : public antlr4::ParserRuleContext {
  public:
    FuncDefContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    BlockContext *block();
    antlr4::tree::TerminalNode *INT();
    antlr4::tree::TerminalNode *VOID();
    std::vector<ParamContext *> param();
    ParamContext* param(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FuncDefContext* funcDef();

  class  ParamContext : public antlr4::ParserRuleContext {
  public:
    ParamContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INT();
    antlr4::tree::TerminalNode *ID();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ParamContext* param();

  class  StmtContext : public antlr4::ParserRuleContext {
  public:
    StmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    StmtContext() = default;
    void copyFrom(StmtContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  ContinueStmtContext : public StmtContext {
  public:
    ContinueStmtContext(StmtContext *ctx);

    antlr4::tree::TerminalNode *CONTINUE();
    antlr4::tree::TerminalNode *SEMI();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  IfStmtContext : public StmtContext {
  public:
    IfStmtContext(StmtContext *ctx);

    antlr4::tree::TerminalNode *IF();
    antlr4::tree::TerminalNode *LPAREN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RPAREN();
    std::vector<StmtContext *> stmt();
    StmtContext* stmt(size_t i);
    antlr4::tree::TerminalNode *ELSE();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ExprStmtContext : public StmtContext {
  public:
    ExprStmtContext(StmtContext *ctx);

    ExprContext *expr();
    antlr4::tree::TerminalNode *SEMI();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  WhileStmtContext : public StmtContext {
  public:
    WhileStmtContext(StmtContext *ctx);

    antlr4::tree::TerminalNode *WHILE();
    antlr4::tree::TerminalNode *LPAREN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RPAREN();
    StmtContext *stmt();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  AssignStmtContext : public StmtContext {
  public:
    AssignStmtContext(StmtContext *ctx);

    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *ASSIGN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *SEMI();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  BreakStmtContext : public StmtContext {
  public:
    BreakStmtContext(StmtContext *ctx);

    antlr4::tree::TerminalNode *BREAK();
    antlr4::tree::TerminalNode *SEMI();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  BlockStmtContext : public StmtContext {
  public:
    BlockStmtContext(StmtContext *ctx);

    BlockContext *block();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  EmptyStmtContext : public StmtContext {
  public:
    EmptyStmtContext(StmtContext *ctx);

    antlr4::tree::TerminalNode *SEMI();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  DeclStmtContext : public StmtContext {
  public:
    DeclStmtContext(StmtContext *ctx);

    antlr4::tree::TerminalNode *INT();
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *ASSIGN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *SEMI();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ReturnStmtContext : public StmtContext {
  public:
    ReturnStmtContext(StmtContext *ctx);

    antlr4::tree::TerminalNode *RETURN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *SEMI();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  StmtContext* stmt();

  class  BlockContext : public antlr4::ParserRuleContext {
  public:
    BlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<StmtContext *> stmt();
    StmtContext* stmt(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BlockContext* block();

  class  ExprContext : public antlr4::ParserRuleContext {
  public:
    ExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    LOrExprContext *lOrExpr();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExprContext* expr();

  class  LOrExprContext : public antlr4::ParserRuleContext {
  public:
    LOrExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    LOrExprContext() = default;
    void copyFrom(LOrExprContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  MulLOrExprContext : public LOrExprContext {
  public:
    MulLOrExprContext(LOrExprContext *ctx);

    LOrExprContext *lOrExpr();
    antlr4::tree::TerminalNode *OR();
    LAndExprContext *lAndExpr();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  SingleLOrContext : public LOrExprContext {
  public:
    SingleLOrContext(LOrExprContext *ctx);

    LAndExprContext *lAndExpr();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  LOrExprContext* lOrExpr();
  LOrExprContext* lOrExpr(int precedence);
  class  LAndExprContext : public antlr4::ParserRuleContext {
  public:
    LAndExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    LAndExprContext() = default;
    void copyFrom(LAndExprContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  SingleLAndContext : public LAndExprContext {
  public:
    SingleLAndContext(LAndExprContext *ctx);

    RelExprContext *relExpr();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  MulLAndExprContext : public LAndExprContext {
  public:
    MulLAndExprContext(LAndExprContext *ctx);

    LAndExprContext *lAndExpr();
    antlr4::tree::TerminalNode *AND();
    RelExprContext *relExpr();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  LAndExprContext* lAndExpr();
  LAndExprContext* lAndExpr(int precedence);
  class  RelExprContext : public antlr4::ParserRuleContext {
  public:
    RelExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    RelExprContext() = default;
    void copyFrom(RelExprContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  SingleRelContext : public RelExprContext {
  public:
    SingleRelContext(RelExprContext *ctx);

    AddExprContext *addExpr();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  MulRelExprContext : public RelExprContext {
  public:
    MulRelExprContext(RelExprContext *ctx);

    RelExprContext *relExpr();
    AddExprContext *addExpr();
    antlr4::tree::TerminalNode *LT();
    antlr4::tree::TerminalNode *GT();
    antlr4::tree::TerminalNode *LE();
    antlr4::tree::TerminalNode *GE();
    antlr4::tree::TerminalNode *EQ();
    antlr4::tree::TerminalNode *NE();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  RelExprContext* relExpr();
  RelExprContext* relExpr(int precedence);
  class  AddExprContext : public antlr4::ParserRuleContext {
  public:
    AddExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    AddExprContext() = default;
    void copyFrom(AddExprContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  MulAddExprContext : public AddExprContext {
  public:
    MulAddExprContext(AddExprContext *ctx);

    AddExprContext *addExpr();
    MulExprContext *mulExpr();
    antlr4::tree::TerminalNode *ADD();
    antlr4::tree::TerminalNode *SUB();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  SingleAddContext : public AddExprContext {
  public:
    SingleAddContext(AddExprContext *ctx);

    MulExprContext *mulExpr();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  AddExprContext* addExpr();
  AddExprContext* addExpr(int precedence);
  class  MulExprContext : public antlr4::ParserRuleContext {
  public:
    MulExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    MulExprContext() = default;
    void copyFrom(MulExprContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  SingleMulContext : public MulExprContext {
  public:
    SingleMulContext(MulExprContext *ctx);

    UnaryExprContext *unaryExpr();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  MulMulExprContext : public MulExprContext {
  public:
    MulMulExprContext(MulExprContext *ctx);

    MulExprContext *mulExpr();
    UnaryExprContext *unaryExpr();
    antlr4::tree::TerminalNode *MUL();
    antlr4::tree::TerminalNode *DIV();
    antlr4::tree::TerminalNode *MOD();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  MulExprContext* mulExpr();
  MulExprContext* mulExpr(int precedence);
  class  UnaryExprContext : public antlr4::ParserRuleContext {
  public:
    UnaryExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    UnaryExprContext() = default;
    void copyFrom(UnaryExprContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  MulUnaryOpContext : public UnaryExprContext {
  public:
    MulUnaryOpContext(UnaryExprContext *ctx);

    UnaryExprContext *unaryExpr();
    antlr4::tree::TerminalNode *ADD();
    antlr4::tree::TerminalNode *SUB();
    antlr4::tree::TerminalNode *NOT();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  SingleUnaryContext : public UnaryExprContext {
  public:
    SingleUnaryContext(UnaryExprContext *ctx);

    PrimaryExprContext *primaryExpr();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  UnaryExprContext* unaryExpr();

  class  PrimaryExprContext : public antlr4::ParserRuleContext {
  public:
    PrimaryExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    PrimaryExprContext() = default;
    void copyFrom(PrimaryExprContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  IdentifierContext : public PrimaryExprContext {
  public:
    IdentifierContext(PrimaryExprContext *ctx);

    antlr4::tree::TerminalNode *ID();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ParenthesizedExprContext : public PrimaryExprContext {
  public:
    ParenthesizedExprContext(PrimaryExprContext *ctx);

    antlr4::tree::TerminalNode *LPAREN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RPAREN();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FunctionCallContext : public PrimaryExprContext {
  public:
    FunctionCallContext(PrimaryExprContext *ctx);

    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  NumberLiteralContext : public PrimaryExprContext {
  public:
    NumberLiteralContext(PrimaryExprContext *ctx);

    antlr4::tree::TerminalNode *NUMBER();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  PrimaryExprContext* primaryExpr();


  bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;

  bool lOrExprSempred(LOrExprContext *_localctx, size_t predicateIndex);
  bool lAndExprSempred(LAndExprContext *_localctx, size_t predicateIndex);
  bool relExprSempred(RelExprContext *_localctx, size_t predicateIndex);
  bool addExprSempred(AddExprContext *_localctx, size_t predicateIndex);
  bool mulExprSempred(MulExprContext *_localctx, size_t predicateIndex);

  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

