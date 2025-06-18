#pragma once 
#include <string>
#include <vector>

enum class TokenKind { Identifier, Number, EndOfFile };

struct Token {
    TokenKind kind;
    std:: string text;
};

std::vector<Token> lex(const std:: string& source);
