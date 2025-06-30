#pragma once
#include "token.h"
#include "keywords.h"
#include <istream>
#include <vector>

class Lexer{
public:
    Lexer(std::istream& input);
    std::vector<Token> tokenize();

private:
    std::istream& in;
    int line = 1;
    int column = 0;
    char peek();
    char next();
    void skipWhitespace();
    void skipComment();
    Token readNumber();
    Token readIdentifierOrKeyword();
    Token readOperatorOrSeparator();
};