#include "lexer.h"
#include <cctype>
Lexer::Lexer(std::istream& input) : in(input) {}

char Lexer::peek() {
    return in.peek();
}

char Lexer::next() {
    char ch = in.get();
    if (ch == '\n') { ++line; column = 0; }
    else { ++column; }
    return ch;
}

void Lexer::skipWhitespace() {
    while (std::isspace(peek())) next();
}

void Lexer::skipComment() {
    if (peek() == '/') {
        next();
        if (peek() == '/') {
            while (peek() != '\n' && !in.eof()) next();
        }
        else if (peek() == '*') {
            next();
            while (true) {
                if (in.eof()) break;
                char ch = next();
                if (ch == '*' && peek() == '/') {
                    next(); break;
                }
            }
        }
        else {
            in.unget(); --column;
        }
    }
}

Token Lexer::readNumber() {
    int startCol = column;
    std::string num;
    if (peek() == '-') num += next();
    while (std::isdigit(peek())) num += next();
    return Token(TokenType::Number, num, line, startCol);
}

Token Lexer::readIdentifierOrKeyword() {
    int startCol = column;
    std::string id;
    while (std::isalnum(peek()) || peek() == '_') id += next();
    if (keywords.count(id))
        return Token(TokenType::Keyword, id, line, startCol);
    return Token(TokenType::Identifier, id, line, startCol);
}

Token Lexer::readOperatorOrSeparator() {
    int startCol = column;
    std::string op;
    op += next();
    if (singleCharOperators.count(peek())) {
        std::string two = op + peek();
        if (operators.count(two)) {
            op += next();
            return Token(TokenType::Operator, two, line, startCol);
        }
    }
    if (operators.count(op)) return Token(TokenType::Operator, op, line, startCol);
    if (op == "(" || op == ")" || op == "{" || op == "}" || op == ";" || op == ",")
        return Token(TokenType::Separator, op, line, startCol);
    return Token(TokenType::Unknown, op, line, startCol);
}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    while (!in.eof()) {
        skipWhitespace();
        skipComment();
        skipWhitespace();
        char ch = peek();
        if (in.eof()) break;
        if (std::isdigit(ch) || ch == '-') tokens.push_back(readNumber());
        else if (std::isalpha(ch) || ch == '_') tokens.push_back(readIdentifierOrKeyword());
        else if (singleCharOperators.count(ch)) tokens.push_back(readOperatorOrSeparator());
        else {
            tokens.push_back(Token(TokenType::Unknown, std::string(1, next()), line, column));
        }
    }
    tokens.emplace_back(TokenType::EndOfFile, "EOF", line, column);
    return tokens;
}
