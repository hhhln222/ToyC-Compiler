
// Generated from ToyC.g4 by ANTLR 4.12.0

#pragma once


#include "antlr4-runtime.h"




class  ToyCLexer : public antlr4::Lexer {
public:
  enum {
    INT = 1, VOID = 2, IF = 3, ELSE = 4, WHILE = 5, BREAK = 6, CONTINUE = 7, 
    RETURN = 8, ID = 9, NUMBER = 10, PLUS = 11, MINUS = 12, MUL = 13, DIV = 14, 
    MOD = 15, NOT = 16, ASSIGN = 17, LT = 18, GT = 19, LE = 20, GE = 21, 
    EQ = 22, NE = 23, AND = 24, OR = 25, LPAREN = 26, RPAREN = 27, LBRACE = 28, 
    RBRACE = 29, COMMA = 30, SEMI = 31, WS = 32
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

