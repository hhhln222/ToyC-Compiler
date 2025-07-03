
// Generated from ToyC.g4 by ANTLR 4.13.1


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
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
ToyCParserStaticData *toycParserStaticData = nullptr;

void toycParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (toycParserStaticData != nullptr) {
    return;
  }
#else
  assert(toycParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<ToyCParserStaticData>(
    std::vector<std::string>{
      "compUnit", "funcDef", "param", "stmt", "block", "expr", "lOrExpr", 
      "lAndExpr", "relExpr", "addExpr", "mulExpr", "unaryExpr", "primaryExpr"
    },
    std::vector<std::string>{
      "", "'int'", "'void'", "'if'", "'else'", "'while'", "'break'", "'continue'", 
      "'return'", "'||'", "'&&'", "'<'", "'>'", "'<='", "'>='", "'=='", 
      "'!='", "'+'", "'-'", "'*'", "'/'", "'%'", "'!'", "'='", "';'", "','", 
      "'('", "')'", "'{'", "'}'"
    },
    std::vector<std::string>{
      "", "INT", "VOID", "IF", "ELSE", "WHILE", "BREAK", "CONTINUE", "RETURN", 
      "OR", "AND", "LT", "GT", "LE", "GE", "EQ", "NE", "ADD", "SUB", "MUL", 
      "DIV", "MOD", "NOT", "ASSIGN", "SEMI", "COMMA", "LPAREN", "RPAREN", 
      "LBRACE", "RBRACE", "ID", "NUMBER", "LINE_COMMENT", "COMMENT", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,34,184,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,1,0,4,0,28,8,0,11,
  	0,12,0,29,1,1,1,1,1,1,1,1,1,1,1,1,5,1,38,8,1,10,1,12,1,41,9,1,3,1,43,
  	8,1,1,1,1,1,1,1,1,2,1,2,1,2,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,
  	3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,3,3,74,8,3,1,3,1,3,
  	1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,3,3,90,8,3,1,4,1,4,5,
  	4,94,8,4,10,4,12,4,97,9,4,1,4,1,4,1,5,1,5,1,6,1,6,1,6,1,6,1,6,1,6,5,6,
  	109,8,6,10,6,12,6,112,9,6,1,7,1,7,1,7,1,7,1,7,1,7,5,7,120,8,7,10,7,12,
  	7,123,9,7,1,8,1,8,1,8,1,8,1,8,1,8,5,8,131,8,8,10,8,12,8,134,9,8,1,9,1,
  	9,1,9,1,9,1,9,1,9,5,9,142,8,9,10,9,12,9,145,9,9,1,10,1,10,1,10,1,10,1,
  	10,1,10,5,10,153,8,10,10,10,12,10,156,9,10,1,11,1,11,1,11,3,11,161,8,
  	11,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,5,12,174,8,
  	12,10,12,12,12,177,9,12,3,12,179,8,12,1,12,3,12,182,8,12,1,12,0,5,12,
  	14,16,18,20,13,0,2,4,6,8,10,12,14,16,18,20,22,24,0,5,1,0,1,2,1,0,11,16,
  	1,0,17,18,1,0,19,21,2,0,17,18,22,22,195,0,27,1,0,0,0,2,31,1,0,0,0,4,47,
  	1,0,0,0,6,89,1,0,0,0,8,91,1,0,0,0,10,100,1,0,0,0,12,102,1,0,0,0,14,113,
  	1,0,0,0,16,124,1,0,0,0,18,135,1,0,0,0,20,146,1,0,0,0,22,160,1,0,0,0,24,
  	181,1,0,0,0,26,28,3,2,1,0,27,26,1,0,0,0,28,29,1,0,0,0,29,27,1,0,0,0,29,
  	30,1,0,0,0,30,1,1,0,0,0,31,32,7,0,0,0,32,33,5,30,0,0,33,42,5,26,0,0,34,
  	39,3,4,2,0,35,36,5,25,0,0,36,38,3,4,2,0,37,35,1,0,0,0,38,41,1,0,0,0,39,
  	37,1,0,0,0,39,40,1,0,0,0,40,43,1,0,0,0,41,39,1,0,0,0,42,34,1,0,0,0,42,
  	43,1,0,0,0,43,44,1,0,0,0,44,45,5,27,0,0,45,46,3,8,4,0,46,3,1,0,0,0,47,
  	48,5,1,0,0,48,49,5,30,0,0,49,5,1,0,0,0,50,90,3,8,4,0,51,90,5,24,0,0,52,
  	53,3,10,5,0,53,54,5,24,0,0,54,90,1,0,0,0,55,56,5,30,0,0,56,57,5,23,0,
  	0,57,58,3,10,5,0,58,59,5,24,0,0,59,90,1,0,0,0,60,61,5,1,0,0,61,62,5,30,
  	0,0,62,63,5,23,0,0,63,64,3,10,5,0,64,65,5,24,0,0,65,90,1,0,0,0,66,67,
  	5,3,0,0,67,68,5,26,0,0,68,69,3,10,5,0,69,70,5,27,0,0,70,73,3,6,3,0,71,
  	72,5,4,0,0,72,74,3,6,3,0,73,71,1,0,0,0,73,74,1,0,0,0,74,90,1,0,0,0,75,
  	76,5,5,0,0,76,77,5,26,0,0,77,78,3,10,5,0,78,79,5,27,0,0,79,80,3,6,3,0,
  	80,90,1,0,0,0,81,82,5,6,0,0,82,90,5,24,0,0,83,84,5,7,0,0,84,90,5,24,0,
  	0,85,86,5,8,0,0,86,87,3,10,5,0,87,88,5,24,0,0,88,90,1,0,0,0,89,50,1,0,
  	0,0,89,51,1,0,0,0,89,52,1,0,0,0,89,55,1,0,0,0,89,60,1,0,0,0,89,66,1,0,
  	0,0,89,75,1,0,0,0,89,81,1,0,0,0,89,83,1,0,0,0,89,85,1,0,0,0,90,7,1,0,
  	0,0,91,95,5,28,0,0,92,94,3,6,3,0,93,92,1,0,0,0,94,97,1,0,0,0,95,93,1,
  	0,0,0,95,96,1,0,0,0,96,98,1,0,0,0,97,95,1,0,0,0,98,99,5,29,0,0,99,9,1,
  	0,0,0,100,101,3,12,6,0,101,11,1,0,0,0,102,103,6,6,-1,0,103,104,3,14,7,
  	0,104,110,1,0,0,0,105,106,10,1,0,0,106,107,5,9,0,0,107,109,3,14,7,0,108,
  	105,1,0,0,0,109,112,1,0,0,0,110,108,1,0,0,0,110,111,1,0,0,0,111,13,1,
  	0,0,0,112,110,1,0,0,0,113,114,6,7,-1,0,114,115,3,16,8,0,115,121,1,0,0,
  	0,116,117,10,1,0,0,117,118,5,10,0,0,118,120,3,16,8,0,119,116,1,0,0,0,
  	120,123,1,0,0,0,121,119,1,0,0,0,121,122,1,0,0,0,122,15,1,0,0,0,123,121,
  	1,0,0,0,124,125,6,8,-1,0,125,126,3,18,9,0,126,132,1,0,0,0,127,128,10,
  	1,0,0,128,129,7,1,0,0,129,131,3,18,9,0,130,127,1,0,0,0,131,134,1,0,0,
  	0,132,130,1,0,0,0,132,133,1,0,0,0,133,17,1,0,0,0,134,132,1,0,0,0,135,
  	136,6,9,-1,0,136,137,3,20,10,0,137,143,1,0,0,0,138,139,10,1,0,0,139,140,
  	7,2,0,0,140,142,3,20,10,0,141,138,1,0,0,0,142,145,1,0,0,0,143,141,1,0,
  	0,0,143,144,1,0,0,0,144,19,1,0,0,0,145,143,1,0,0,0,146,147,6,10,-1,0,
  	147,148,3,22,11,0,148,154,1,0,0,0,149,150,10,1,0,0,150,151,7,3,0,0,151,
  	153,3,22,11,0,152,149,1,0,0,0,153,156,1,0,0,0,154,152,1,0,0,0,154,155,
  	1,0,0,0,155,21,1,0,0,0,156,154,1,0,0,0,157,161,3,24,12,0,158,159,7,4,
  	0,0,159,161,3,22,11,0,160,157,1,0,0,0,160,158,1,0,0,0,161,23,1,0,0,0,
  	162,182,5,30,0,0,163,182,5,31,0,0,164,165,5,26,0,0,165,166,3,10,5,0,166,
  	167,5,27,0,0,167,182,1,0,0,0,168,169,5,30,0,0,169,178,5,26,0,0,170,175,
  	3,10,5,0,171,172,5,25,0,0,172,174,3,10,5,0,173,171,1,0,0,0,174,177,1,
  	0,0,0,175,173,1,0,0,0,175,176,1,0,0,0,176,179,1,0,0,0,177,175,1,0,0,0,
  	178,170,1,0,0,0,178,179,1,0,0,0,179,180,1,0,0,0,180,182,5,27,0,0,181,
  	162,1,0,0,0,181,163,1,0,0,0,181,164,1,0,0,0,181,168,1,0,0,0,182,25,1,
  	0,0,0,15,29,39,42,73,89,95,110,121,132,143,154,160,175,178,181
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
ToyCParser::StmtContext* ToyCParser::stmt() {
  StmtContext *_localctx = _tracker.createInstance<StmtContext>(_ctx, getState());
  enterRule(_localctx, 6, ToyCParser::RuleStmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(89);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<ToyCParser::BlockStmtContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(50);
      block();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<ToyCParser::EmptyStmtContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(51);
      match(ToyCParser::SEMI);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<ToyCParser::ExprStmtContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(52);
      expr();
      setState(53);
      match(ToyCParser::SEMI);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<ToyCParser::AssignStmtContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(55);
      match(ToyCParser::ID);
      setState(56);
      match(ToyCParser::ASSIGN);
      setState(57);
      expr();
      setState(58);
      match(ToyCParser::SEMI);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<ToyCParser::DeclStmtContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(60);
      match(ToyCParser::INT);
      setState(61);
      match(ToyCParser::ID);
      setState(62);
      match(ToyCParser::ASSIGN);
      setState(63);
      expr();
      setState(64);
      match(ToyCParser::SEMI);
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<ToyCParser::IfStmtContext>(_localctx);
      enterOuterAlt(_localctx, 6);
      setState(66);
      match(ToyCParser::IF);
      setState(67);
      match(ToyCParser::LPAREN);
      setState(68);
      expr();
      setState(69);
      match(ToyCParser::RPAREN);
      setState(70);
      stmt();
      setState(73);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx)) {
      case 1: {
        setState(71);
        match(ToyCParser::ELSE);
        setState(72);
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
      setState(75);
      match(ToyCParser::WHILE);
      setState(76);
      match(ToyCParser::LPAREN);
      setState(77);
      expr();
      setState(78);
      match(ToyCParser::RPAREN);
      setState(79);
      stmt();
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<ToyCParser::BreakStmtContext>(_localctx);
      enterOuterAlt(_localctx, 8);
      setState(81);
      match(ToyCParser::BREAK);
      setState(82);
      match(ToyCParser::SEMI);
      break;
    }

    case 9: {
      _localctx = _tracker.createInstance<ToyCParser::ContinueStmtContext>(_localctx);
      enterOuterAlt(_localctx, 9);
      setState(83);
      match(ToyCParser::CONTINUE);
      setState(84);
      match(ToyCParser::SEMI);
      break;
    }

    case 10: {
      _localctx = _tracker.createInstance<ToyCParser::ReturnStmtContext>(_localctx);
      enterOuterAlt(_localctx, 10);
      setState(85);
      match(ToyCParser::RETURN);
      setState(86);
      expr();
      setState(87);
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
  enterRule(_localctx, 8, ToyCParser::RuleBlock);
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
    setState(91);
    match(ToyCParser::LBRACE);
    setState(95);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 3578135018) != 0)) {
      setState(92);
      stmt();
      setState(97);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(98);
    match(ToyCParser::RBRACE);
   
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
    lOrExpr(0);
   
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


size_t ToyCParser::LOrExprContext::getRuleIndex() const {
  return ToyCParser::RuleLOrExpr;
}

void ToyCParser::LOrExprContext::copyFrom(LOrExprContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- MulLOrExprContext ------------------------------------------------------------------

ToyCParser::LOrExprContext* ToyCParser::MulLOrExprContext::lOrExpr() {
  return getRuleContext<ToyCParser::LOrExprContext>(0);
}

tree::TerminalNode* ToyCParser::MulLOrExprContext::OR() {
  return getToken(ToyCParser::OR, 0);
}

ToyCParser::LAndExprContext* ToyCParser::MulLOrExprContext::lAndExpr() {
  return getRuleContext<ToyCParser::LAndExprContext>(0);
}

ToyCParser::MulLOrExprContext::MulLOrExprContext(LOrExprContext *ctx) { copyFrom(ctx); }


std::any ToyCParser::MulLOrExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ToyCVisitor*>(visitor))
    return parserVisitor->visitMulLOrExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- SingleLOrContext ------------------------------------------------------------------

ToyCParser::LAndExprContext* ToyCParser::SingleLOrContext::lAndExpr() {
  return getRuleContext<ToyCParser::LAndExprContext>(0);
}

ToyCParser::SingleLOrContext::SingleLOrContext(LOrExprContext *ctx) { copyFrom(ctx); }


std::any ToyCParser::SingleLOrContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ToyCVisitor*>(visitor))
    return parserVisitor->visitSingleLOr(this);
  else
    return visitor->visitChildren(this);
}

ToyCParser::LOrExprContext* ToyCParser::lOrExpr() {
   return lOrExpr(0);
}

ToyCParser::LOrExprContext* ToyCParser::lOrExpr(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  ToyCParser::LOrExprContext *_localctx = _tracker.createInstance<LOrExprContext>(_ctx, parentState);
  ToyCParser::LOrExprContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 12;
  enterRecursionRule(_localctx, 12, ToyCParser::RuleLOrExpr, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    _localctx = _tracker.createInstance<SingleLOrContext>(_localctx);
    _ctx = _localctx;
    previousContext = _localctx;

    setState(103);
    lAndExpr(0);
    _ctx->stop = _input->LT(-1);
    setState(110);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        auto newContext = _tracker.createInstance<MulLOrExprContext>(_tracker.createInstance<LOrExprContext>(parentContext, parentState));
        _localctx = newContext;
        pushNewRecursionContext(newContext, startState, RuleLOrExpr);
        setState(105);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(106);
        match(ToyCParser::OR);
        setState(107);
        lAndExpr(0); 
      }
      setState(112);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx);
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


size_t ToyCParser::LAndExprContext::getRuleIndex() const {
  return ToyCParser::RuleLAndExpr;
}

void ToyCParser::LAndExprContext::copyFrom(LAndExprContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- SingleLAndContext ------------------------------------------------------------------

ToyCParser::RelExprContext* ToyCParser::SingleLAndContext::relExpr() {
  return getRuleContext<ToyCParser::RelExprContext>(0);
}

ToyCParser::SingleLAndContext::SingleLAndContext(LAndExprContext *ctx) { copyFrom(ctx); }


std::any ToyCParser::SingleLAndContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ToyCVisitor*>(visitor))
    return parserVisitor->visitSingleLAnd(this);
  else
    return visitor->visitChildren(this);
}
//----------------- MulLAndExprContext ------------------------------------------------------------------

ToyCParser::LAndExprContext* ToyCParser::MulLAndExprContext::lAndExpr() {
  return getRuleContext<ToyCParser::LAndExprContext>(0);
}

tree::TerminalNode* ToyCParser::MulLAndExprContext::AND() {
  return getToken(ToyCParser::AND, 0);
}

ToyCParser::RelExprContext* ToyCParser::MulLAndExprContext::relExpr() {
  return getRuleContext<ToyCParser::RelExprContext>(0);
}

ToyCParser::MulLAndExprContext::MulLAndExprContext(LAndExprContext *ctx) { copyFrom(ctx); }


std::any ToyCParser::MulLAndExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ToyCVisitor*>(visitor))
    return parserVisitor->visitMulLAndExpr(this);
  else
    return visitor->visitChildren(this);
}

ToyCParser::LAndExprContext* ToyCParser::lAndExpr() {
   return lAndExpr(0);
}

ToyCParser::LAndExprContext* ToyCParser::lAndExpr(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  ToyCParser::LAndExprContext *_localctx = _tracker.createInstance<LAndExprContext>(_ctx, parentState);
  ToyCParser::LAndExprContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 14;
  enterRecursionRule(_localctx, 14, ToyCParser::RuleLAndExpr, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    _localctx = _tracker.createInstance<SingleLAndContext>(_localctx);
    _ctx = _localctx;
    previousContext = _localctx;

    setState(114);
    relExpr(0);
    _ctx->stop = _input->LT(-1);
    setState(121);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        auto newContext = _tracker.createInstance<MulLAndExprContext>(_tracker.createInstance<LAndExprContext>(parentContext, parentState));
        _localctx = newContext;
        pushNewRecursionContext(newContext, startState, RuleLAndExpr);
        setState(116);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(117);
        match(ToyCParser::AND);
        setState(118);
        relExpr(0); 
      }
      setState(123);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx);
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


size_t ToyCParser::RelExprContext::getRuleIndex() const {
  return ToyCParser::RuleRelExpr;
}

void ToyCParser::RelExprContext::copyFrom(RelExprContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- SingleRelContext ------------------------------------------------------------------

ToyCParser::AddExprContext* ToyCParser::SingleRelContext::addExpr() {
  return getRuleContext<ToyCParser::AddExprContext>(0);
}

ToyCParser::SingleRelContext::SingleRelContext(RelExprContext *ctx) { copyFrom(ctx); }


std::any ToyCParser::SingleRelContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ToyCVisitor*>(visitor))
    return parserVisitor->visitSingleRel(this);
  else
    return visitor->visitChildren(this);
}
//----------------- MulRelExprContext ------------------------------------------------------------------

ToyCParser::RelExprContext* ToyCParser::MulRelExprContext::relExpr() {
  return getRuleContext<ToyCParser::RelExprContext>(0);
}

ToyCParser::AddExprContext* ToyCParser::MulRelExprContext::addExpr() {
  return getRuleContext<ToyCParser::AddExprContext>(0);
}

tree::TerminalNode* ToyCParser::MulRelExprContext::LT() {
  return getToken(ToyCParser::LT, 0);
}

tree::TerminalNode* ToyCParser::MulRelExprContext::GT() {
  return getToken(ToyCParser::GT, 0);
}

tree::TerminalNode* ToyCParser::MulRelExprContext::LE() {
  return getToken(ToyCParser::LE, 0);
}

tree::TerminalNode* ToyCParser::MulRelExprContext::GE() {
  return getToken(ToyCParser::GE, 0);
}

tree::TerminalNode* ToyCParser::MulRelExprContext::EQ() {
  return getToken(ToyCParser::EQ, 0);
}

tree::TerminalNode* ToyCParser::MulRelExprContext::NE() {
  return getToken(ToyCParser::NE, 0);
}

ToyCParser::MulRelExprContext::MulRelExprContext(RelExprContext *ctx) { copyFrom(ctx); }


std::any ToyCParser::MulRelExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ToyCVisitor*>(visitor))
    return parserVisitor->visitMulRelExpr(this);
  else
    return visitor->visitChildren(this);
}

ToyCParser::RelExprContext* ToyCParser::relExpr() {
   return relExpr(0);
}

ToyCParser::RelExprContext* ToyCParser::relExpr(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  ToyCParser::RelExprContext *_localctx = _tracker.createInstance<RelExprContext>(_ctx, parentState);
  ToyCParser::RelExprContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 16;
  enterRecursionRule(_localctx, 16, ToyCParser::RuleRelExpr, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    _localctx = _tracker.createInstance<SingleRelContext>(_localctx);
    _ctx = _localctx;
    previousContext = _localctx;

    setState(125);
    addExpr(0);
    _ctx->stop = _input->LT(-1);
    setState(132);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        auto newContext = _tracker.createInstance<MulRelExprContext>(_tracker.createInstance<RelExprContext>(parentContext, parentState));
        _localctx = newContext;
        pushNewRecursionContext(newContext, startState, RuleRelExpr);
        setState(127);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(128);
        _la = _input->LA(1);
        if (!((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 129024) != 0))) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(129);
        addExpr(0); 
      }
      setState(134);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx);
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


size_t ToyCParser::AddExprContext::getRuleIndex() const {
  return ToyCParser::RuleAddExpr;
}

void ToyCParser::AddExprContext::copyFrom(AddExprContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- MulAddExprContext ------------------------------------------------------------------

ToyCParser::AddExprContext* ToyCParser::MulAddExprContext::addExpr() {
  return getRuleContext<ToyCParser::AddExprContext>(0);
}

ToyCParser::MulExprContext* ToyCParser::MulAddExprContext::mulExpr() {
  return getRuleContext<ToyCParser::MulExprContext>(0);
}

tree::TerminalNode* ToyCParser::MulAddExprContext::ADD() {
  return getToken(ToyCParser::ADD, 0);
}

tree::TerminalNode* ToyCParser::MulAddExprContext::SUB() {
  return getToken(ToyCParser::SUB, 0);
}

ToyCParser::MulAddExprContext::MulAddExprContext(AddExprContext *ctx) { copyFrom(ctx); }


std::any ToyCParser::MulAddExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ToyCVisitor*>(visitor))
    return parserVisitor->visitMulAddExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- SingleAddContext ------------------------------------------------------------------

ToyCParser::MulExprContext* ToyCParser::SingleAddContext::mulExpr() {
  return getRuleContext<ToyCParser::MulExprContext>(0);
}

ToyCParser::SingleAddContext::SingleAddContext(AddExprContext *ctx) { copyFrom(ctx); }


std::any ToyCParser::SingleAddContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ToyCVisitor*>(visitor))
    return parserVisitor->visitSingleAdd(this);
  else
    return visitor->visitChildren(this);
}

ToyCParser::AddExprContext* ToyCParser::addExpr() {
   return addExpr(0);
}

ToyCParser::AddExprContext* ToyCParser::addExpr(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  ToyCParser::AddExprContext *_localctx = _tracker.createInstance<AddExprContext>(_ctx, parentState);
  ToyCParser::AddExprContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 18;
  enterRecursionRule(_localctx, 18, ToyCParser::RuleAddExpr, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    _localctx = _tracker.createInstance<SingleAddContext>(_localctx);
    _ctx = _localctx;
    previousContext = _localctx;

    setState(136);
    mulExpr(0);
    _ctx->stop = _input->LT(-1);
    setState(143);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        auto newContext = _tracker.createInstance<MulAddExprContext>(_tracker.createInstance<AddExprContext>(parentContext, parentState));
        _localctx = newContext;
        pushNewRecursionContext(newContext, startState, RuleAddExpr);
        setState(138);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(139);
        _la = _input->LA(1);
        if (!(_la == ToyCParser::ADD

        || _la == ToyCParser::SUB)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(140);
        mulExpr(0); 
      }
      setState(145);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx);
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


size_t ToyCParser::MulExprContext::getRuleIndex() const {
  return ToyCParser::RuleMulExpr;
}

void ToyCParser::MulExprContext::copyFrom(MulExprContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- SingleMulContext ------------------------------------------------------------------

ToyCParser::UnaryExprContext* ToyCParser::SingleMulContext::unaryExpr() {
  return getRuleContext<ToyCParser::UnaryExprContext>(0);
}

ToyCParser::SingleMulContext::SingleMulContext(MulExprContext *ctx) { copyFrom(ctx); }


std::any ToyCParser::SingleMulContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ToyCVisitor*>(visitor))
    return parserVisitor->visitSingleMul(this);
  else
    return visitor->visitChildren(this);
}
//----------------- MulMulExprContext ------------------------------------------------------------------

ToyCParser::MulExprContext* ToyCParser::MulMulExprContext::mulExpr() {
  return getRuleContext<ToyCParser::MulExprContext>(0);
}

ToyCParser::UnaryExprContext* ToyCParser::MulMulExprContext::unaryExpr() {
  return getRuleContext<ToyCParser::UnaryExprContext>(0);
}

tree::TerminalNode* ToyCParser::MulMulExprContext::MUL() {
  return getToken(ToyCParser::MUL, 0);
}

tree::TerminalNode* ToyCParser::MulMulExprContext::DIV() {
  return getToken(ToyCParser::DIV, 0);
}

tree::TerminalNode* ToyCParser::MulMulExprContext::MOD() {
  return getToken(ToyCParser::MOD, 0);
}

ToyCParser::MulMulExprContext::MulMulExprContext(MulExprContext *ctx) { copyFrom(ctx); }


std::any ToyCParser::MulMulExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ToyCVisitor*>(visitor))
    return parserVisitor->visitMulMulExpr(this);
  else
    return visitor->visitChildren(this);
}

ToyCParser::MulExprContext* ToyCParser::mulExpr() {
   return mulExpr(0);
}

ToyCParser::MulExprContext* ToyCParser::mulExpr(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  ToyCParser::MulExprContext *_localctx = _tracker.createInstance<MulExprContext>(_ctx, parentState);
  ToyCParser::MulExprContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 20;
  enterRecursionRule(_localctx, 20, ToyCParser::RuleMulExpr, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    _localctx = _tracker.createInstance<SingleMulContext>(_localctx);
    _ctx = _localctx;
    previousContext = _localctx;

    setState(147);
    unaryExpr();
    _ctx->stop = _input->LT(-1);
    setState(154);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        auto newContext = _tracker.createInstance<MulMulExprContext>(_tracker.createInstance<MulExprContext>(parentContext, parentState));
        _localctx = newContext;
        pushNewRecursionContext(newContext, startState, RuleMulExpr);
        setState(149);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(150);
        _la = _input->LA(1);
        if (!((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 3670016) != 0))) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(151);
        unaryExpr(); 
      }
      setState(156);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx);
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


size_t ToyCParser::UnaryExprContext::getRuleIndex() const {
  return ToyCParser::RuleUnaryExpr;
}

void ToyCParser::UnaryExprContext::copyFrom(UnaryExprContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- MulUnaryOpContext ------------------------------------------------------------------

ToyCParser::UnaryExprContext* ToyCParser::MulUnaryOpContext::unaryExpr() {
  return getRuleContext<ToyCParser::UnaryExprContext>(0);
}

tree::TerminalNode* ToyCParser::MulUnaryOpContext::ADD() {
  return getToken(ToyCParser::ADD, 0);
}

tree::TerminalNode* ToyCParser::MulUnaryOpContext::SUB() {
  return getToken(ToyCParser::SUB, 0);
}

tree::TerminalNode* ToyCParser::MulUnaryOpContext::NOT() {
  return getToken(ToyCParser::NOT, 0);
}

ToyCParser::MulUnaryOpContext::MulUnaryOpContext(UnaryExprContext *ctx) { copyFrom(ctx); }


std::any ToyCParser::MulUnaryOpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ToyCVisitor*>(visitor))
    return parserVisitor->visitMulUnaryOp(this);
  else
    return visitor->visitChildren(this);
}
//----------------- SingleUnaryContext ------------------------------------------------------------------

ToyCParser::PrimaryExprContext* ToyCParser::SingleUnaryContext::primaryExpr() {
  return getRuleContext<ToyCParser::PrimaryExprContext>(0);
}

ToyCParser::SingleUnaryContext::SingleUnaryContext(UnaryExprContext *ctx) { copyFrom(ctx); }


std::any ToyCParser::SingleUnaryContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ToyCVisitor*>(visitor))
    return parserVisitor->visitSingleUnary(this);
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
    setState(160);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ToyCParser::LPAREN:
      case ToyCParser::ID:
      case ToyCParser::NUMBER: {
        _localctx = _tracker.createInstance<ToyCParser::SingleUnaryContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(157);
        primaryExpr();
        break;
      }

      case ToyCParser::ADD:
      case ToyCParser::SUB:
      case ToyCParser::NOT: {
        _localctx = _tracker.createInstance<ToyCParser::MulUnaryOpContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(158);
        _la = _input->LA(1);
        if (!((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 4587520) != 0))) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(159);
        unaryExpr();
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

//----------------- IdentifierContext ------------------------------------------------------------------

tree::TerminalNode* ToyCParser::IdentifierContext::ID() {
  return getToken(ToyCParser::ID, 0);
}

ToyCParser::IdentifierContext::IdentifierContext(PrimaryExprContext *ctx) { copyFrom(ctx); }


std::any ToyCParser::IdentifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ToyCVisitor*>(visitor))
    return parserVisitor->visitIdentifier(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ParenthesizedExprContext ------------------------------------------------------------------

tree::TerminalNode* ToyCParser::ParenthesizedExprContext::LPAREN() {
  return getToken(ToyCParser::LPAREN, 0);
}

ToyCParser::ExprContext* ToyCParser::ParenthesizedExprContext::expr() {
  return getRuleContext<ToyCParser::ExprContext>(0);
}

tree::TerminalNode* ToyCParser::ParenthesizedExprContext::RPAREN() {
  return getToken(ToyCParser::RPAREN, 0);
}

ToyCParser::ParenthesizedExprContext::ParenthesizedExprContext(PrimaryExprContext *ctx) { copyFrom(ctx); }


std::any ToyCParser::ParenthesizedExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ToyCVisitor*>(visitor))
    return parserVisitor->visitParenthesizedExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FunctionCallContext ------------------------------------------------------------------

tree::TerminalNode* ToyCParser::FunctionCallContext::ID() {
  return getToken(ToyCParser::ID, 0);
}

tree::TerminalNode* ToyCParser::FunctionCallContext::LPAREN() {
  return getToken(ToyCParser::LPAREN, 0);
}

tree::TerminalNode* ToyCParser::FunctionCallContext::RPAREN() {
  return getToken(ToyCParser::RPAREN, 0);
}

std::vector<ToyCParser::ExprContext *> ToyCParser::FunctionCallContext::expr() {
  return getRuleContexts<ToyCParser::ExprContext>();
}

ToyCParser::ExprContext* ToyCParser::FunctionCallContext::expr(size_t i) {
  return getRuleContext<ToyCParser::ExprContext>(i);
}

std::vector<tree::TerminalNode *> ToyCParser::FunctionCallContext::COMMA() {
  return getTokens(ToyCParser::COMMA);
}

tree::TerminalNode* ToyCParser::FunctionCallContext::COMMA(size_t i) {
  return getToken(ToyCParser::COMMA, i);
}

ToyCParser::FunctionCallContext::FunctionCallContext(PrimaryExprContext *ctx) { copyFrom(ctx); }


std::any ToyCParser::FunctionCallContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ToyCVisitor*>(visitor))
    return parserVisitor->visitFunctionCall(this);
  else
    return visitor->visitChildren(this);
}
//----------------- NumberLiteralContext ------------------------------------------------------------------

tree::TerminalNode* ToyCParser::NumberLiteralContext::NUMBER() {
  return getToken(ToyCParser::NUMBER, 0);
}

ToyCParser::NumberLiteralContext::NumberLiteralContext(PrimaryExprContext *ctx) { copyFrom(ctx); }


std::any ToyCParser::NumberLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ToyCVisitor*>(visitor))
    return parserVisitor->visitNumberLiteral(this);
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
    setState(181);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<ToyCParser::IdentifierContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(162);
      match(ToyCParser::ID);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<ToyCParser::NumberLiteralContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(163);
      match(ToyCParser::NUMBER);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<ToyCParser::ParenthesizedExprContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(164);
      match(ToyCParser::LPAREN);
      setState(165);
      expr();
      setState(166);
      match(ToyCParser::RPAREN);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<ToyCParser::FunctionCallContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(168);
      match(ToyCParser::ID);
      setState(169);
      match(ToyCParser::LPAREN);
      setState(178);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 3292921856) != 0)) {
        setState(170);
        expr();
        setState(175);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == ToyCParser::COMMA) {
          setState(171);
          match(ToyCParser::COMMA);
          setState(172);
          expr();
          setState(177);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
      }
      setState(180);
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

bool ToyCParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 6: return lOrExprSempred(antlrcpp::downCast<LOrExprContext *>(context), predicateIndex);
    case 7: return lAndExprSempred(antlrcpp::downCast<LAndExprContext *>(context), predicateIndex);
    case 8: return relExprSempred(antlrcpp::downCast<RelExprContext *>(context), predicateIndex);
    case 9: return addExprSempred(antlrcpp::downCast<AddExprContext *>(context), predicateIndex);
    case 10: return mulExprSempred(antlrcpp::downCast<MulExprContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool ToyCParser::lOrExprSempred(LOrExprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool ToyCParser::lAndExprSempred(LAndExprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 1: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool ToyCParser::relExprSempred(RelExprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 2: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool ToyCParser::addExprSempred(AddExprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 3: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool ToyCParser::mulExprSempred(MulExprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 4: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

void ToyCParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  toycParserInitialize();
#else
  ::antlr4::internal::call_once(toycParserOnceFlag, toycParserInitialize);
#endif
}
