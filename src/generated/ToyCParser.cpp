
// Generated from ToyC.g4 by ANTLR 4.12.0


#include "ToyCVisitor.h"

#include "ToyCParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct ToyCParserStaticData final {
  ToyCParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  ToyCParserStaticData(const ToyCParserStaticData&) = delete;
  ToyCParserStaticData(ToyCParserStaticData&&) = delete;
  ToyCParserStaticData& operator=(const ToyCParserStaticData&) = delete;
  ToyCParserStaticData& operator=(ToyCParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag toycParserOnceFlag;
ToyCParserStaticData *toycParserStaticData = nullptr;

void toycParserInitialize() {
  assert(toycParserStaticData == nullptr);
  auto staticData = std::make_unique<ToyCParserStaticData>(
    std::vector<std::string>{
      "compUnit", "funcDef", "param", "block", "stmt", "expr", "lOrExpr", 
      "lAndExpr", "relExpr", "addExpr", "mulExpr", "unaryExpr", "primaryExpr"
    },
    std::vector<std::string>{
      "", "'int'", "'void'", "'if'", "'else'", "'while'", "'break'", "'continue'", 
      "'return'", "", "", "'+'", "'-'", "'*'", "'/'", "'%'", "'!'", "'='", 
      "'<'", "'>'", "'<='", "'>='", "'=='", "'!='", "'&&'", "'||'", "'('", 
      "')'", "'{'", "'}'", "','", "';'"
    },
    std::vector<std::string>{
      "", "INT", "VOID", "IF", "ELSE", "WHILE", "BREAK", "CONTINUE", "RETURN", 
      "ID", "NUMBER", "PLUS", "MINUS", "MUL", "DIV", "MOD", "NOT", "ASSIGN", 
      "LT", "GT", "LE", "GE", "EQ", "NE", "AND", "OR", "LPAREN", "RPAREN", 
      "LBRACE", "RBRACE", "COMMA", "SEMI", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,32,166,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,1,0,4,0,28,8,0,11,
  	0,12,0,29,1,1,1,1,1,1,1,1,1,1,1,1,5,1,38,8,1,10,1,12,1,41,9,1,3,1,43,
  	8,1,1,1,1,1,1,1,1,2,1,2,1,2,1,3,1,3,5,3,53,8,3,10,3,12,3,56,9,3,1,3,1,
  	3,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,
  	1,4,1,4,1,4,1,4,1,4,1,4,3,4,83,8,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,
  	4,1,4,1,4,1,4,1,4,1,4,3,4,99,8,4,1,5,1,5,1,6,1,6,1,6,5,6,106,8,6,10,6,
  	12,6,109,9,6,1,7,1,7,1,7,5,7,114,8,7,10,7,12,7,117,9,7,1,8,1,8,1,8,3,
  	8,122,8,8,1,9,1,9,1,9,5,9,127,8,9,10,9,12,9,130,9,9,1,10,1,10,1,10,5,
  	10,135,8,10,10,10,12,10,138,9,10,1,11,1,11,1,11,3,11,143,8,11,1,12,1,
  	12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,5,12,156,8,12,10,12,12,
  	12,159,9,12,3,12,161,8,12,1,12,3,12,164,8,12,1,12,0,0,13,0,2,4,6,8,10,
  	12,14,16,18,20,22,24,0,5,1,0,1,2,1,0,18,23,1,0,11,12,1,0,13,15,2,0,11,
  	12,16,16,177,0,27,1,0,0,0,2,31,1,0,0,0,4,47,1,0,0,0,6,50,1,0,0,0,8,98,
  	1,0,0,0,10,100,1,0,0,0,12,102,1,0,0,0,14,110,1,0,0,0,16,118,1,0,0,0,18,
  	123,1,0,0,0,20,131,1,0,0,0,22,142,1,0,0,0,24,163,1,0,0,0,26,28,3,2,1,
  	0,27,26,1,0,0,0,28,29,1,0,0,0,29,27,1,0,0,0,29,30,1,0,0,0,30,1,1,0,0,
  	0,31,32,7,0,0,0,32,33,5,9,0,0,33,42,5,26,0,0,34,39,3,4,2,0,35,36,5,30,
  	0,0,36,38,3,4,2,0,37,35,1,0,0,0,38,41,1,0,0,0,39,37,1,0,0,0,39,40,1,0,
  	0,0,40,43,1,0,0,0,41,39,1,0,0,0,42,34,1,0,0,0,42,43,1,0,0,0,43,44,1,0,
  	0,0,44,45,5,27,0,0,45,46,3,6,3,0,46,3,1,0,0,0,47,48,5,1,0,0,48,49,5,9,
  	0,0,49,5,1,0,0,0,50,54,5,28,0,0,51,53,3,8,4,0,52,51,1,0,0,0,53,56,1,0,
  	0,0,54,52,1,0,0,0,54,55,1,0,0,0,55,57,1,0,0,0,56,54,1,0,0,0,57,58,5,29,
  	0,0,58,7,1,0,0,0,59,99,3,6,3,0,60,99,5,31,0,0,61,62,3,10,5,0,62,63,5,
  	31,0,0,63,99,1,0,0,0,64,65,5,9,0,0,65,66,5,17,0,0,66,67,3,10,5,0,67,68,
  	5,31,0,0,68,99,1,0,0,0,69,70,5,1,0,0,70,71,5,9,0,0,71,72,5,17,0,0,72,
  	73,3,10,5,0,73,74,5,31,0,0,74,99,1,0,0,0,75,76,5,3,0,0,76,77,5,26,0,0,
  	77,78,3,10,5,0,78,79,5,27,0,0,79,82,3,8,4,0,80,81,5,4,0,0,81,83,3,8,4,
  	0,82,80,1,0,0,0,82,83,1,0,0,0,83,99,1,0,0,0,84,85,5,5,0,0,85,86,5,26,
  	0,0,86,87,3,10,5,0,87,88,5,27,0,0,88,89,3,8,4,0,89,99,1,0,0,0,90,91,5,
  	6,0,0,91,99,5,31,0,0,92,93,5,7,0,0,93,99,5,31,0,0,94,95,5,8,0,0,95,96,
  	3,10,5,0,96,97,5,31,0,0,97,99,1,0,0,0,98,59,1,0,0,0,98,60,1,0,0,0,98,
  	61,1,0,0,0,98,64,1,0,0,0,98,69,1,0,0,0,98,75,1,0,0,0,98,84,1,0,0,0,98,
  	90,1,0,0,0,98,92,1,0,0,0,98,94,1,0,0,0,99,9,1,0,0,0,100,101,3,12,6,0,
  	101,11,1,0,0,0,102,107,3,14,7,0,103,104,5,25,0,0,104,106,3,14,7,0,105,
  	103,1,0,0,0,106,109,1,0,0,0,107,105,1,0,0,0,107,108,1,0,0,0,108,13,1,
  	0,0,0,109,107,1,0,0,0,110,115,3,16,8,0,111,112,5,24,0,0,112,114,3,16,
  	8,0,113,111,1,0,0,0,114,117,1,0,0,0,115,113,1,0,0,0,115,116,1,0,0,0,116,
  	15,1,0,0,0,117,115,1,0,0,0,118,121,3,18,9,0,119,120,7,1,0,0,120,122,3,
  	18,9,0,121,119,1,0,0,0,121,122,1,0,0,0,122,17,1,0,0,0,123,128,3,20,10,
  	0,124,125,7,2,0,0,125,127,3,20,10,0,126,124,1,0,0,0,127,130,1,0,0,0,128,
  	126,1,0,0,0,128,129,1,0,0,0,129,19,1,0,0,0,130,128,1,0,0,0,131,136,3,
  	22,11,0,132,133,7,3,0,0,133,135,3,22,11,0,134,132,1,0,0,0,135,138,1,0,
  	0,0,136,134,1,0,0,0,136,137,1,0,0,0,137,21,1,0,0,0,138,136,1,0,0,0,139,
  	140,7,4,0,0,140,143,3,22,11,0,141,143,3,24,12,0,142,139,1,0,0,0,142,141,
  	1,0,0,0,143,23,1,0,0,0,144,164,5,9,0,0,145,164,5,10,0,0,146,147,5,26,
  	0,0,147,148,3,10,5,0,148,149,5,27,0,0,149,164,1,0,0,0,150,151,5,9,0,0,
  	151,160,5,26,0,0,152,157,3,10,5,0,153,154,5,30,0,0,154,156,3,10,5,0,155,
  	153,1,0,0,0,156,159,1,0,0,0,157,155,1,0,0,0,157,158,1,0,0,0,158,161,1,
  	0,0,0,159,157,1,0,0,0,160,152,1,0,0,0,160,161,1,0,0,0,161,162,1,0,0,0,
  	162,164,5,27,0,0,163,144,1,0,0,0,163,145,1,0,0,0,163,146,1,0,0,0,163,
  	150,1,0,0,0,164,25,1,0,0,0,15,29,39,42,54,82,98,107,115,121,128,136,142,
  	157,160,163
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  toycParserStaticData = staticData.release();
}

}

ToyCParser::ToyCParser(TokenStream *input) : ToyCParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

ToyCParser::ToyCParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  ToyCParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *toycParserStaticData->atn, toycParserStaticData->decisionToDFA, toycParserStaticData->sharedContextCache, options);
}

ToyCParser::~ToyCParser() {
  delete _interpreter;
}

const atn::ATN& ToyCParser::getATN() const {
  return *toycParserStaticData->atn;
}

std::string ToyCParser::getGrammarFileName() const {
  return "ToyC.g4";
}

const std::vector<std::string>& ToyCParser::getRuleNames() const {
  return toycParserStaticData->ruleNames;
}

const dfa::Vocabulary& ToyCParser::getVocabulary() const {
  return toycParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView ToyCParser::getSerializedATN() const {
  return toycParserStaticData->serializedATN;
}


//----------------- CompUnitContext ------------------------------------------------------------------

ToyCParser::CompUnitContext::CompUnitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<ToyCParser::FuncDefContext *> ToyCParser::CompUnitContext::funcDef() {
  return getRuleContexts<ToyCParser::FuncDefContext>();
}

ToyCParser::FuncDefContext* ToyCParser::CompUnitContext::funcDef(size_t i) {
  return getRuleContext<ToyCParser::FuncDefContext>(i);
}


size_t ToyCParser::CompUnitContext::getRuleIndex() const {
  return ToyCParser::RuleCompUnit;
}


std::any ToyCParser::CompUnitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ToyCVisitor*>(visitor))
    return parserVisitor->visitCompUnit(this);
  else
    return visitor->visitChildren(this);
}

ToyCParser::CompUnitContext* ToyCParser::compUnit() {
  CompUnitContext *_localctx = _tracker.createInstance<CompUnitContext>(_ctx, getState());
  enterRule(_localctx, 0, ToyCParser::RuleCompUnit);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(27); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(26);
      funcDef();
      setState(29); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == ToyCParser::INT

    || _la == ToyCParser::VOID);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncDefContext ------------------------------------------------------------------

ToyCParser::FuncDefContext::FuncDefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ToyCParser::FuncDefContext::ID() {
  return getToken(ToyCParser::ID, 0);
}

tree::TerminalNode* ToyCParser::FuncDefContext::LPAREN() {
  return getToken(ToyCParser::LPAREN, 0);
}

tree::TerminalNode* ToyCParser::FuncDefContext::RPAREN() {
  return getToken(ToyCParser::RPAREN, 0);
}

ToyCParser::BlockContext* ToyCParser::FuncDefContext::block() {
  return getRuleContext<ToyCParser::BlockContext>(0);
}

tree::TerminalNode* ToyCParser::FuncDefContext::INT() {
  return getToken(ToyCParser::INT, 0);
}

tree::TerminalNode* ToyCParser::FuncDefContext::VOID() {
  return getToken(ToyCParser::VOID, 0);
}

std::vector<ToyCParser::ParamContext *> ToyCParser::FuncDefContext::param() {
  return getRuleContexts<ToyCParser::ParamContext>();
}

ToyCParser::ParamContext* ToyCParser::FuncDefContext::param(size_t i) {
  return getRuleContext<ToyCParser::ParamContext>(i);
}

std::vector<tree::TerminalNode *> ToyCParser::FuncDefContext::COMMA() {
  return getTokens(ToyCParser::COMMA);
}

tree::TerminalNode* ToyCParser::FuncDefContext::COMMA(size_t i) {
  return getToken(ToyCParser::COMMA, i);
}


size_t ToyCParser::FuncDefContext::getRuleIndex() const {
  return ToyCParser::RuleFuncDef;
}


std::any ToyCParser::FuncDefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ToyCVisitor*>(visitor))
    return parserVisitor->visitFuncDef(this);
  else
    return visitor->visitChildren(this);
}

ToyCParser::FuncDefContext* ToyCParser::funcDef() {
  FuncDefContext *_localctx = _tracker.createInstance<FuncDefContext>(_ctx, getState());
  enterRule(_localctx, 2, ToyCParser::RuleFuncDef);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(31);
    _la = _input->LA(1);
    if (!(_la == ToyCParser::INT

    || _la == ToyCParser::VOID)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(32);
    match(ToyCParser::ID);
    setState(33);
    match(ToyCParser::LPAREN);
    setState(42);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ToyCParser::INT) {
      setState(34);
      param();
      setState(39);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == ToyCParser::COMMA) {
        setState(35);
        match(ToyCParser::COMMA);
        setState(36);
        param();
        setState(41);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(44);
    match(ToyCParser::RPAREN);
    setState(45);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParamContext ------------------------------------------------------------------

ToyCParser::ParamContext::ParamContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ToyCParser::ParamContext::INT() {
  return getToken(ToyCParser::INT, 0);
}

tree::TerminalNode* ToyCParser::ParamContext::ID() {
  return getToken(ToyCParser::ID, 0);
}


size_t ToyCParser::ParamContext::getRuleIndex() const {
  return ToyCParser::RuleParam;
}


std::any ToyCParser::ParamContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ToyCVisitor*>(visitor))
    return parserVisitor->visitParam(this);
  else
    return visitor->visitChildren(this);
}

ToyCParser::ParamContext* ToyCParser::param() {
  ParamContext *_localctx = _tracker.createInstance<ParamContext>(_ctx, getState());
  enterRule(_localctx, 4, ToyCParser::RuleParam);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(47);
    match(ToyCParser::INT);
    setState(48);
    match(ToyCParser::ID);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockContext ------------------------------------------------------------------

ToyCParser::BlockContext::BlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ToyCParser::BlockContext::LBRACE() {
  return getToken(ToyCParser::LBRACE, 0);
}

tree::TerminalNode* ToyCParser::BlockContext::RBRACE() {
  return getToken(ToyCParser::RBRACE, 0);
}

std::vector<ToyCParser::StmtContext *> ToyCParser::BlockContext::stmt() {
  return getRuleContexts<ToyCParser::StmtContext>();
}

ToyCParser::StmtContext* ToyCParser::BlockContext::stmt(size_t i) {
  return getRuleContext<ToyCParser::StmtContext>(i);
}


size_t ToyCParser::BlockContext::getRuleIndex() const {
  return ToyCParser::RuleBlock;
}


std::any ToyCParser::BlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ToyCVisitor*>(visitor))
    return parserVisitor->visitBlock(this);
  else
    return visitor->visitChildren(this);
}

ToyCParser::BlockContext* ToyCParser::block() {
  BlockContext *_localctx = _tracker.createInstance<BlockContext>(_ctx, getState());
  enterRule(_localctx, 6, ToyCParser::RuleBlock);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(50);
    match(ToyCParser::LBRACE);
    setState(54);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 2483101674) != 0)) {
      setState(51);
      stmt();
      setState(56);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(57);
    match(ToyCParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StmtContext ------------------------------------------------------------------

ToyCParser::StmtContext::StmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t ToyCParser::StmtContext::getRuleIndex() const {
  return ToyCParser::RuleStmt;
}

void ToyCParser::StmtContext::copyFrom(StmtContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ExprStmtContext ------------------------------------------------------------------

ToyCParser::ExprContext* ToyCParser::ExprStmtContext::expr() {
  return getRuleContext<ToyCParser::ExprContext>(0);
}

tree::TerminalNode* ToyCParser::ExprStmtContext::SEMI() {
  return getToken(ToyCParser::SEMI, 0);
}

ToyCParser::ExprStmtContext::ExprStmtContext(StmtContext *ctx) { copyFrom(ctx); }


std::any ToyCParser::ExprStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ToyCVisitor*>(visitor))
    return parserVisitor->visitExprStmt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- WhileStmtContext ------------------------------------------------------------------

tree::TerminalNode* ToyCParser::WhileStmtContext::WHILE() {
  return getToken(ToyCParser::WHILE, 0);
}

tree::TerminalNode* ToyCParser::WhileStmtContext::LPAREN() {
  return getToken(ToyCParser::LPAREN, 0);
}

ToyCParser::ExprContext* ToyCParser::WhileStmtContext::expr() {
  return getRuleContext<ToyCParser::ExprContext>(0);
}

tree::TerminalNode* ToyCParser::WhileStmtContext::RPAREN() {
  return getToken(ToyCParser::RPAREN, 0);
}

ToyCParser::StmtContext* ToyCParser::WhileStmtContext::stmt() {
  return getRuleContext<ToyCParser::StmtContext>(0);
}

ToyCParser::WhileStmtContext::WhileStmtContext(StmtContext *ctx) { copyFrom(ctx); }


std::any ToyCParser::WhileStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ToyCVisitor*>(visitor))
    return parserVisitor->visitWhileStmt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IfStmtContext ------------------------------------------------------------------

tree::TerminalNode* ToyCParser::IfStmtContext::IF() {
  return getToken(ToyCParser::IF, 0);
}

tree::TerminalNode* ToyCParser::IfStmtContext::LPAREN() {
  return getToken(ToyCParser::LPAREN, 0);
}

ToyCParser::ExprContext* ToyCParser::IfStmtContext::expr() {
  return getRuleContext<ToyCParser::ExprContext>(0);
}

tree::TerminalNode* ToyCParser::IfStmtContext::RPAREN() {
  return getToken(ToyCParser::RPAREN, 0);
}

std::vector<ToyCParser::StmtContext *> ToyCParser::IfStmtContext::stmt() {
  return getRuleContexts<ToyCParser::StmtContext>();
}

ToyCParser::StmtContext* ToyCParser::IfStmtContext::stmt(size_t i) {
  return getRuleContext<ToyCParser::StmtContext>(i);
}

tree::TerminalNode* ToyCParser::IfStmtContext::ELSE() {
  return getToken(ToyCParser::ELSE, 0);
}

ToyCParser::IfStmtContext::IfStmtContext(StmtContext *ctx) { copyFrom(ctx); }


std::any ToyCParser::IfStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ToyCVisitor*>(visitor))
    return parserVisitor->visitIfStmt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BlockStmtContext ------------------------------------------------------------------

ToyCParser::BlockContext* ToyCParser::BlockStmtContext::block() {
  return getRuleContext<ToyCParser::BlockContext>(0);
}

ToyCParser::BlockStmtContext::BlockStmtContext(StmtContext *ctx) { copyFrom(ctx); }


std::any ToyCParser::BlockStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ToyCVisitor*>(visitor))
    return parserVisitor->visitBlockStmt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DeclStmtContext ------------------------------------------------------------------

tree::TerminalNode* ToyCParser::DeclStmtContext::INT() {
  return getToken(ToyCParser::INT, 0);
}

tree::TerminalNode* ToyCParser::DeclStmtContext::ID() {
  return getToken(ToyCParser::ID, 0);
}

tree::TerminalNode* ToyCParser::DeclStmtContext::ASSIGN() {
  return getToken(ToyCParser::ASSIGN, 0);
}

ToyCParser::ExprContext* ToyCParser::DeclStmtContext::expr() {
  return getRuleContext<ToyCParser::ExprContext>(0);
}

tree::TerminalNode* ToyCParser::DeclStmtContext::SEMI() {
  return getToken(ToyCParser::SEMI, 0);
}

ToyCParser::DeclStmtContext::DeclStmtContext(StmtContext *ctx) { copyFrom(ctx); }


std::any ToyCParser::DeclStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ToyCVisitor*>(visitor))
    return parserVisitor->visitDeclStmt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AssignStmtContext ------------------------------------------------------------------

tree::TerminalNode* ToyCParser::AssignStmtContext::ID() {
  return getToken(ToyCParser::ID, 0);
}

tree::TerminalNode* ToyCParser::AssignStmtContext::ASSIGN() {
  return getToken(ToyCParser::ASSIGN, 0);
}

ToyCParser::ExprContext* ToyCParser::AssignStmtContext::expr() {
  return getRuleContext<ToyCParser::ExprContext>(0);
}

tree::TerminalNode* ToyCParser::AssignStmtContext::SEMI() {
  return getToken(ToyCParser::SEMI, 0);
}

ToyCParser::AssignStmtContext::AssignStmtContext(StmtContext *ctx) { copyFrom(ctx); }


std::any ToyCParser::AssignStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ToyCVisitor*>(visitor))
    return parserVisitor->visitAssignStmt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BreakStmtContext ------------------------------------------------------------------

tree::TerminalNode* ToyCParser::BreakStmtContext::BREAK() {
  return getToken(ToyCParser::BREAK, 0);
}

tree::TerminalNode* ToyCParser::BreakStmtContext::SEMI() {
  return getToken(ToyCParser::SEMI, 0);
}

ToyCParser::BreakStmtContext::BreakStmtContext(StmtContext *ctx) { copyFrom(ctx); }


std::any ToyCParser::BreakStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ToyCVisitor*>(visitor))
    return parserVisitor->visitBreakStmt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- EmptyStmtContext ------------------------------------------------------------------

tree::TerminalNode* ToyCParser::EmptyStmtContext::SEMI() {
  return getToken(ToyCParser::SEMI, 0);
}

ToyCParser::EmptyStmtContext::EmptyStmtContext(StmtContext *ctx) { copyFrom(ctx); }


std::any ToyCParser::EmptyStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ToyCVisitor*>(visitor))
    return parserVisitor->visitEmptyStmt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ReturnStmtContext ------------------------------------------------------------------

tree::TerminalNode* ToyCParser::ReturnStmtContext::RETURN() {
  return getToken(ToyCParser::RETURN, 0);
}

ToyCParser::ExprContext* ToyCParser::ReturnStmtContext::expr() {
  return getRuleContext<ToyCParser::ExprContext>(0);
}

tree::TerminalNode* ToyCParser::ReturnStmtContext::SEMI() {
  return getToken(ToyCParser::SEMI, 0);
}

ToyCParser::ReturnStmtContext::ReturnStmtContext(StmtContext *ctx) { copyFrom(ctx); }


std::any ToyCParser::ReturnStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ToyCVisitor*>(visitor))
    return parserVisitor->visitReturnStmt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ContinueStmtContext ------------------------------------------------------------------

tree::TerminalNode* ToyCParser::ContinueStmtContext::CONTINUE() {
  return getToken(ToyCParser::CONTINUE, 0);
}

tree::TerminalNode* ToyCParser::ContinueStmtContext::SEMI() {
  return getToken(ToyCParser::SEMI, 0);
}

ToyCParser::ContinueStmtContext::ContinueStmtContext(StmtContext *ctx) { copyFrom(ctx); }


std::any ToyCParser::ContinueStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ToyCVisitor*>(visitor))
    return parserVisitor->visitContinueStmt(this);
  else
    return visitor->visitChildren(this);
}
ToyCParser::StmtContext* ToyCParser::stmt() {
  StmtContext *_localctx = _tracker.createInstance<StmtContext>(_ctx, getState());
  enterRule(_localctx, 8, ToyCParser::RuleStmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(98);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<ToyCParser::BlockStmtContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(59);
      block();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<ToyCParser::EmptyStmtContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(60);
      match(ToyCParser::SEMI);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<ToyCParser::ExprStmtContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(61);
      expr();
      setState(62);
      match(ToyCParser::SEMI);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<ToyCParser::AssignStmtContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(64);
      match(ToyCParser::ID);
      setState(65);
      match(ToyCParser::ASSIGN);
      setState(66);
      expr();
      setState(67);
      match(ToyCParser::SEMI);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<ToyCParser::DeclStmtContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(69);
      match(ToyCParser::INT);
      setState(70);
      match(ToyCParser::ID);
      setState(71);
      match(ToyCParser::ASSIGN);
      setState(72);
      expr();
      setState(73);
      match(ToyCParser::SEMI);
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<ToyCParser::IfStmtContext>(_localctx);
      enterOuterAlt(_localctx, 6);
      setState(75);
      match(ToyCParser::IF);
      setState(76);
      match(ToyCParser::LPAREN);
      setState(77);
      expr();
      setState(78);
      match(ToyCParser::RPAREN);
      setState(79);
      stmt();
      setState(82);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
      case 1: {
        setState(80);
        match(ToyCParser::ELSE);
        setState(81);
        stmt();
        break;
      }

      default:
        break;
      }
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<ToyCParser::WhileStmtContext>(_localctx);
      enterOuterAlt(_localctx, 7);
      setState(84);
      match(ToyCParser::WHILE);
      setState(85);
      match(ToyCParser::LPAREN);
      setState(86);
      expr();
      setState(87);
      match(ToyCParser::RPAREN);
      setState(88);
      stmt();
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<ToyCParser::BreakStmtContext>(_localctx);
      enterOuterAlt(_localctx, 8);
      setState(90);
      match(ToyCParser::BREAK);
      setState(91);
      match(ToyCParser::SEMI);
      break;
    }

    case 9: {
      _localctx = _tracker.createInstance<ToyCParser::ContinueStmtContext>(_localctx);
      enterOuterAlt(_localctx, 9);
      setState(92);
      match(ToyCParser::CONTINUE);
      setState(93);
      match(ToyCParser::SEMI);
      break;
    }

    case 10: {
      _localctx = _tracker.createInstance<ToyCParser::ReturnStmtContext>(_localctx);
      enterOuterAlt(_localctx, 10);
      setState(94);
      match(ToyCParser::RETURN);
      setState(95);
      expr();
      setState(96);
      match(ToyCParser::SEMI);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExprContext ------------------------------------------------------------------

ToyCParser::ExprContext::ExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ToyCParser::LOrExprContext* ToyCParser::ExprContext::lOrExpr() {
  return getRuleContext<ToyCParser::LOrExprContext>(0);
}


size_t ToyCParser::ExprContext::getRuleIndex() const {
  return ToyCParser::RuleExpr;
}


std::any ToyCParser::ExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ToyCVisitor*>(visitor))
    return parserVisitor->visitExpr(this);
  else
    return visitor->visitChildren(this);
}

ToyCParser::ExprContext* ToyCParser::expr() {
  ExprContext *_localctx = _tracker.createInstance<ExprContext>(_ctx, getState());
  enterRule(_localctx, 10, ToyCParser::RuleExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(100);
    lOrExpr();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LOrExprContext ------------------------------------------------------------------

ToyCParser::LOrExprContext::LOrExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<ToyCParser::LAndExprContext *> ToyCParser::LOrExprContext::lAndExpr() {
  return getRuleContexts<ToyCParser::LAndExprContext>();
}

ToyCParser::LAndExprContext* ToyCParser::LOrExprContext::lAndExpr(size_t i) {
  return getRuleContext<ToyCParser::LAndExprContext>(i);
}

std::vector<tree::TerminalNode *> ToyCParser::LOrExprContext::OR() {
  return getTokens(ToyCParser::OR);
}

tree::TerminalNode* ToyCParser::LOrExprContext::OR(size_t i) {
  return getToken(ToyCParser::OR, i);
}


size_t ToyCParser::LOrExprContext::getRuleIndex() const {
  return ToyCParser::RuleLOrExpr;
}


std::any ToyCParser::LOrExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ToyCVisitor*>(visitor))
    return parserVisitor->visitLOrExpr(this);
  else
    return visitor->visitChildren(this);
}

ToyCParser::LOrExprContext* ToyCParser::lOrExpr() {
  LOrExprContext *_localctx = _tracker.createInstance<LOrExprContext>(_ctx, getState());
  enterRule(_localctx, 12, ToyCParser::RuleLOrExpr);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(102);
    lAndExpr();
    setState(107);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ToyCParser::OR) {
      setState(103);
      match(ToyCParser::OR);
      setState(104);
      lAndExpr();
      setState(109);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LAndExprContext ------------------------------------------------------------------

ToyCParser::LAndExprContext::LAndExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<ToyCParser::RelExprContext *> ToyCParser::LAndExprContext::relExpr() {
  return getRuleContexts<ToyCParser::RelExprContext>();
}

ToyCParser::RelExprContext* ToyCParser::LAndExprContext::relExpr(size_t i) {
  return getRuleContext<ToyCParser::RelExprContext>(i);
}

std::vector<tree::TerminalNode *> ToyCParser::LAndExprContext::AND() {
  return getTokens(ToyCParser::AND);
}

tree::TerminalNode* ToyCParser::LAndExprContext::AND(size_t i) {
  return getToken(ToyCParser::AND, i);
}


size_t ToyCParser::LAndExprContext::getRuleIndex() const {
  return ToyCParser::RuleLAndExpr;
}


std::any ToyCParser::LAndExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ToyCVisitor*>(visitor))
    return parserVisitor->visitLAndExpr(this);
  else
    return visitor->visitChildren(this);
}

ToyCParser::LAndExprContext* ToyCParser::lAndExpr() {
  LAndExprContext *_localctx = _tracker.createInstance<LAndExprContext>(_ctx, getState());
  enterRule(_localctx, 14, ToyCParser::RuleLAndExpr);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(110);
    relExpr();
    setState(115);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ToyCParser::AND) {
      setState(111);
      match(ToyCParser::AND);
      setState(112);
      relExpr();
      setState(117);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RelExprContext ------------------------------------------------------------------

ToyCParser::RelExprContext::RelExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<ToyCParser::AddExprContext *> ToyCParser::RelExprContext::addExpr() {
  return getRuleContexts<ToyCParser::AddExprContext>();
}

ToyCParser::AddExprContext* ToyCParser::RelExprContext::addExpr(size_t i) {
  return getRuleContext<ToyCParser::AddExprContext>(i);
}

tree::TerminalNode* ToyCParser::RelExprContext::LT() {
  return getToken(ToyCParser::LT, 0);
}

tree::TerminalNode* ToyCParser::RelExprContext::GT() {
  return getToken(ToyCParser::GT, 0);
}

tree::TerminalNode* ToyCParser::RelExprContext::LE() {
  return getToken(ToyCParser::LE, 0);
}

tree::TerminalNode* ToyCParser::RelExprContext::GE() {
  return getToken(ToyCParser::GE, 0);
}

tree::TerminalNode* ToyCParser::RelExprContext::EQ() {
  return getToken(ToyCParser::EQ, 0);
}

tree::TerminalNode* ToyCParser::RelExprContext::NE() {
  return getToken(ToyCParser::NE, 0);
}


size_t ToyCParser::RelExprContext::getRuleIndex() const {
  return ToyCParser::RuleRelExpr;
}


std::any ToyCParser::RelExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ToyCVisitor*>(visitor))
    return parserVisitor->visitRelExpr(this);
  else
    return visitor->visitChildren(this);
}

ToyCParser::RelExprContext* ToyCParser::relExpr() {
  RelExprContext *_localctx = _tracker.createInstance<RelExprContext>(_ctx, getState());
  enterRule(_localctx, 16, ToyCParser::RuleRelExpr);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(118);
    addExpr();
    setState(121);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 16515072) != 0)) {
      setState(119);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 16515072) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(120);
      addExpr();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AddExprContext ------------------------------------------------------------------

ToyCParser::AddExprContext::AddExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<ToyCParser::MulExprContext *> ToyCParser::AddExprContext::mulExpr() {
  return getRuleContexts<ToyCParser::MulExprContext>();
}

ToyCParser::MulExprContext* ToyCParser::AddExprContext::mulExpr(size_t i) {
  return getRuleContext<ToyCParser::MulExprContext>(i);
}

std::vector<tree::TerminalNode *> ToyCParser::AddExprContext::PLUS() {
  return getTokens(ToyCParser::PLUS);
}

tree::TerminalNode* ToyCParser::AddExprContext::PLUS(size_t i) {
  return getToken(ToyCParser::PLUS, i);
}

std::vector<tree::TerminalNode *> ToyCParser::AddExprContext::MINUS() {
  return getTokens(ToyCParser::MINUS);
}

tree::TerminalNode* ToyCParser::AddExprContext::MINUS(size_t i) {
  return getToken(ToyCParser::MINUS, i);
}


size_t ToyCParser::AddExprContext::getRuleIndex() const {
  return ToyCParser::RuleAddExpr;
}


std::any ToyCParser::AddExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ToyCVisitor*>(visitor))
    return parserVisitor->visitAddExpr(this);
  else
    return visitor->visitChildren(this);
}

ToyCParser::AddExprContext* ToyCParser::addExpr() {
  AddExprContext *_localctx = _tracker.createInstance<AddExprContext>(_ctx, getState());
  enterRule(_localctx, 18, ToyCParser::RuleAddExpr);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(123);
    mulExpr();
    setState(128);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ToyCParser::PLUS

    || _la == ToyCParser::MINUS) {
      setState(124);
      _la = _input->LA(1);
      if (!(_la == ToyCParser::PLUS

      || _la == ToyCParser::MINUS)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(125);
      mulExpr();
      setState(130);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MulExprContext ------------------------------------------------------------------

ToyCParser::MulExprContext::MulExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<ToyCParser::UnaryExprContext *> ToyCParser::MulExprContext::unaryExpr() {
  return getRuleContexts<ToyCParser::UnaryExprContext>();
}

ToyCParser::UnaryExprContext* ToyCParser::MulExprContext::unaryExpr(size_t i) {
  return getRuleContext<ToyCParser::UnaryExprContext>(i);
}

std::vector<tree::TerminalNode *> ToyCParser::MulExprContext::MUL() {
  return getTokens(ToyCParser::MUL);
}

tree::TerminalNode* ToyCParser::MulExprContext::MUL(size_t i) {
  return getToken(ToyCParser::MUL, i);
}

std::vector<tree::TerminalNode *> ToyCParser::MulExprContext::DIV() {
  return getTokens(ToyCParser::DIV);
}

tree::TerminalNode* ToyCParser::MulExprContext::DIV(size_t i) {
  return getToken(ToyCParser::DIV, i);
}

std::vector<tree::TerminalNode *> ToyCParser::MulExprContext::MOD() {
  return getTokens(ToyCParser::MOD);
}

tree::TerminalNode* ToyCParser::MulExprContext::MOD(size_t i) {
  return getToken(ToyCParser::MOD, i);
}


size_t ToyCParser::MulExprContext::getRuleIndex() const {
  return ToyCParser::RuleMulExpr;
}


std::any ToyCParser::MulExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ToyCVisitor*>(visitor))
    return parserVisitor->visitMulExpr(this);
  else
    return visitor->visitChildren(this);
}

ToyCParser::MulExprContext* ToyCParser::mulExpr() {
  MulExprContext *_localctx = _tracker.createInstance<MulExprContext>(_ctx, getState());
  enterRule(_localctx, 20, ToyCParser::RuleMulExpr);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(131);
    unaryExpr();
    setState(136);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 57344) != 0)) {
      setState(132);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 57344) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(133);
      unaryExpr();
      setState(138);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UnaryExprContext ------------------------------------------------------------------

ToyCParser::UnaryExprContext::UnaryExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ToyCParser::UnaryExprContext* ToyCParser::UnaryExprContext::unaryExpr() {
  return getRuleContext<ToyCParser::UnaryExprContext>(0);
}

tree::TerminalNode* ToyCParser::UnaryExprContext::PLUS() {
  return getToken(ToyCParser::PLUS, 0);
}

tree::TerminalNode* ToyCParser::UnaryExprContext::MINUS() {
  return getToken(ToyCParser::MINUS, 0);
}

tree::TerminalNode* ToyCParser::UnaryExprContext::NOT() {
  return getToken(ToyCParser::NOT, 0);
}

ToyCParser::PrimaryExprContext* ToyCParser::UnaryExprContext::primaryExpr() {
  return getRuleContext<ToyCParser::PrimaryExprContext>(0);
}


size_t ToyCParser::UnaryExprContext::getRuleIndex() const {
  return ToyCParser::RuleUnaryExpr;
}


std::any ToyCParser::UnaryExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ToyCVisitor*>(visitor))
    return parserVisitor->visitUnaryExpr(this);
  else
    return visitor->visitChildren(this);
}

ToyCParser::UnaryExprContext* ToyCParser::unaryExpr() {
  UnaryExprContext *_localctx = _tracker.createInstance<UnaryExprContext>(_ctx, getState());
  enterRule(_localctx, 22, ToyCParser::RuleUnaryExpr);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(142);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ToyCParser::PLUS:
      case ToyCParser::MINUS:
      case ToyCParser::NOT: {
        enterOuterAlt(_localctx, 1);
        setState(139);
        _la = _input->LA(1);
        if (!((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 71680) != 0))) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(140);
        unaryExpr();
        break;
      }

      case ToyCParser::ID:
      case ToyCParser::NUMBER:
      case ToyCParser::LPAREN: {
        enterOuterAlt(_localctx, 2);
        setState(141);
        primaryExpr();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PrimaryExprContext ------------------------------------------------------------------

ToyCParser::PrimaryExprContext::PrimaryExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t ToyCParser::PrimaryExprContext::getRuleIndex() const {
  return ToyCParser::RulePrimaryExpr;
}

void ToyCParser::PrimaryExprContext::copyFrom(PrimaryExprContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- CallExprContext ------------------------------------------------------------------

tree::TerminalNode* ToyCParser::CallExprContext::ID() {
  return getToken(ToyCParser::ID, 0);
}

tree::TerminalNode* ToyCParser::CallExprContext::LPAREN() {
  return getToken(ToyCParser::LPAREN, 0);
}

tree::TerminalNode* ToyCParser::CallExprContext::RPAREN() {
  return getToken(ToyCParser::RPAREN, 0);
}

std::vector<ToyCParser::ExprContext *> ToyCParser::CallExprContext::expr() {
  return getRuleContexts<ToyCParser::ExprContext>();
}

ToyCParser::ExprContext* ToyCParser::CallExprContext::expr(size_t i) {
  return getRuleContext<ToyCParser::ExprContext>(i);
}

std::vector<tree::TerminalNode *> ToyCParser::CallExprContext::COMMA() {
  return getTokens(ToyCParser::COMMA);
}

tree::TerminalNode* ToyCParser::CallExprContext::COMMA(size_t i) {
  return getToken(ToyCParser::COMMA, i);
}

ToyCParser::CallExprContext::CallExprContext(PrimaryExprContext *ctx) { copyFrom(ctx); }


std::any ToyCParser::CallExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ToyCVisitor*>(visitor))
    return parserVisitor->visitCallExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- NumExprContext ------------------------------------------------------------------

tree::TerminalNode* ToyCParser::NumExprContext::NUMBER() {
  return getToken(ToyCParser::NUMBER, 0);
}

ToyCParser::NumExprContext::NumExprContext(PrimaryExprContext *ctx) { copyFrom(ctx); }


std::any ToyCParser::NumExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ToyCVisitor*>(visitor))
    return parserVisitor->visitNumExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ParenExprContext ------------------------------------------------------------------

tree::TerminalNode* ToyCParser::ParenExprContext::LPAREN() {
  return getToken(ToyCParser::LPAREN, 0);
}

ToyCParser::ExprContext* ToyCParser::ParenExprContext::expr() {
  return getRuleContext<ToyCParser::ExprContext>(0);
}

tree::TerminalNode* ToyCParser::ParenExprContext::RPAREN() {
  return getToken(ToyCParser::RPAREN, 0);
}

ToyCParser::ParenExprContext::ParenExprContext(PrimaryExprContext *ctx) { copyFrom(ctx); }


std::any ToyCParser::ParenExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ToyCVisitor*>(visitor))
    return parserVisitor->visitParenExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IdExprContext ------------------------------------------------------------------

tree::TerminalNode* ToyCParser::IdExprContext::ID() {
  return getToken(ToyCParser::ID, 0);
}

ToyCParser::IdExprContext::IdExprContext(PrimaryExprContext *ctx) { copyFrom(ctx); }


std::any ToyCParser::IdExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ToyCVisitor*>(visitor))
    return parserVisitor->visitIdExpr(this);
  else
    return visitor->visitChildren(this);
}
ToyCParser::PrimaryExprContext* ToyCParser::primaryExpr() {
  PrimaryExprContext *_localctx = _tracker.createInstance<PrimaryExprContext>(_ctx, getState());
  enterRule(_localctx, 24, ToyCParser::RulePrimaryExpr);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(163);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<ToyCParser::IdExprContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(144);
      match(ToyCParser::ID);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<ToyCParser::NumExprContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(145);
      match(ToyCParser::NUMBER);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<ToyCParser::ParenExprContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(146);
      match(ToyCParser::LPAREN);
      setState(147);
      expr();
      setState(148);
      match(ToyCParser::RPAREN);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<ToyCParser::CallExprContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(150);
      match(ToyCParser::ID);
      setState(151);
      match(ToyCParser::LPAREN);
      setState(160);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 67182080) != 0)) {
        setState(152);
        expr();
        setState(157);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == ToyCParser::COMMA) {
          setState(153);
          match(ToyCParser::COMMA);
          setState(154);
          expr();
          setState(159);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
      }
      setState(162);
      match(ToyCParser::RPAREN);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

void ToyCParser::initialize() {
  ::antlr4::internal::call_once(toycParserOnceFlag, toycParserInitialize);
}
