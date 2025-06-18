#include "lexer.hpp"
#include <cctype>
#include <iostream>

std::vector<Token> lex(const std:: string& src){
    std::vector<Token> tokens;
    size_t i = 0;
    while(i < src.size()){
        if(std::isspace(src[i])){ //skips whitespaces
            i++;
            continue;
        }
        if(std::isalpha(src[i])||src[i]=='_'){ // Identifiers: start with letter or underscore, followed by letters/digits/underscores
            size_t start = i;
            while(i<src.size() && (std::isalnum(src[i])) || src[i] == '_'){
                i++;
            }
            tokens.push_back({TokenKind::Identifier, src.substr(start, i - start)});
            continue;
        }
        if(std::isdigit(src[i])){ // Numbers - sequence of digits
            size_t start = i;
            while(i<src.size() && std::isdigit(src[i])){
                i++;
            }
            tokens.push_back({TokenKind::Number, src.substr(start, i - start)});
            continue;
        }
        if (src[i] == '=') { 
            tokens.push_back({TokenKind::Equal, "="}); 
            i++; 
            continue; 
        }
        if (src[i] == '+') { 
            tokens.push_back({TokenKind::Plus, "+"}); 
            i++; 
            continue; 
        }
        if (src[i] == '-') { 
            tokens.push_back({TokenKind::Minus, "-"}); 
            i++; 
            continue; 
        }
        if (src[i] == '*') { 
            tokens.push_back({TokenKind::Star, "*"}); 
            i++; 
            continue; 
        }
        if (src[i] == '/') { 
            tokens.push_back({TokenKind::Slash, "/"}); 
            i++; 
            continue; 
        }
        if (src[i] == '(') { 
            tokens.push_back({TokenKind::LParen, "("}); 
            i++; 
            continue; 
        }
        if (src[i] == ')') { 
            tokens.push_back({TokenKind::RParen, ")"}); 
            i++; 
            continue; 
        }

        //Error case for unknown character
        std::cerr << "Warning: Unknown Character '" << src[i] << "' at position " << i << '\n';
        tokens.push_back({TokenKind::Unknown, std::string(1, src[i])}); 
        i++;
    }
    tokens.push_back({TokenKind::EndOfFile, ""});
    return tokens;   
}