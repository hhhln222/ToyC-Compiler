
// Generated from ToyC.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"




class  ToyCLexer : public antlr4::Lexer {
public:
  enum {
    INT = 1, VOID = 2, IF = 3, ELSE = 4, WHILE = 5, BREAK = 6, CONTINUE = 7, 
    RETURN = 8, OR = 9, AND = 10, LT = 11, GT = 12, LE = 13, GE = 14, EQ = 15, 
    NE = 16, ADD = 17, SUB = 18, MUL = 19, DIV = 20, MOD = 21, NOT = 22, 
    ASSIGN = 23, SEMI = 24, COMMA = 25, LPAREN = 26, RPAREN = 27, LBRACE = 28, 
    RBRACE = 29, ID = 30, NUMBER = 31, LINE_COMMENT = 32, COMMENT = 33, 
    WS = 34
  };

  explicit ToyCLexer(antlr4::CharStream *input);

  ~ToyCLexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

