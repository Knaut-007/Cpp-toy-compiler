#include "lexer.hpp"
#include <cctype>

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
        i++;
    }
    tokens.push_back({TokenKind::EndOfFile, ""});
    return tokens;   
}