#include "parser.hpp"
#include <iostream>

void NumberNode::print(int indent) const {
    std::cout << std::string(indent, ' ') << "Number(" << value << ")\n";
}
void IdentifierNode::print(int indent) const {
    std::cout << std::string(indent, ' ') << "Identifier(" << name << ")\n";
}
void BinaryOpNode::print(int indent) const {
    std::cout << std::string(indent, ' ') << "BinaryOp(" << op << ")\n";
    left->print(indent + 2);
    right->print(indent + 2);
}
void AssignmentNode::print(int indent) const {
    std::cout << std::string(indent, ' ') << "Assignment(" << name << ")\n";
    expr->print(indent + 2);
}

// Recursive Descent Parser Implementation
namespace {

    AST parse_expression();

    size_t pos;
    const std::vector<Token>* tokens;

    const Token& peek() { return (*tokens)[pos]; }
    const Token& advance() { return (*tokens)[pos++]; }
    bool match(TokenKind kind) {
        if (peek().kind == kind) { advance(); return true; }
        return false;
    }
    void expect(TokenKind kind, const std::string& msg) {
        if (!match(kind)) throw std::runtime_error("Parse error: " + msg);
    }

    AST parse_factor() {
        if (match(TokenKind::Number)) {
            return std::make_unique<NumberNode>(tokens->at(pos-1).text);
        }
        if (match(TokenKind::Identifier)) {
            return std::make_unique<IdentifierNode>(tokens->at(pos-1).text);
        }
        if (match(TokenKind::LParen)) {
            auto expr = parse_expression();
            expect(TokenKind::RParen, "Expected ')'");
            return expr;
        }
        throw std::runtime_error("Parse error: Expected number, identifier, or '('");
    }

    AST parse_term() {
        auto node = parse_factor();
        while (peek().kind == TokenKind::Star || peek().kind == TokenKind::Slash) {
            std::string op = peek().text;
            advance();
            node = std::make_unique<BinaryOpNode>(op, std::move(node), parse_factor());
        }
        return node;
    }

    AST parse_expression() {
        auto node = parse_term();
        while (peek().kind == TokenKind::Plus || peek().kind == TokenKind::Minus) {
            std::string op = peek().text;
            advance();
            node = std::make_unique<BinaryOpNode>(op, std::move(node), parse_term());
        }
        return node;
    }

    AST parse_statement() {
        if (peek().kind == TokenKind::Identifier && tokens->at(pos+1).kind == TokenKind::Equal) {
            std::string name = peek().text;
            advance(); // identifier
            advance(); // '='
            auto expr = parse_expression();
            return std::make_unique<AssignmentNode>(name, std::move(expr));
        }
        throw std::runtime_error("Parse error: Expected assignment statement");
    }

    std::vector<AST> parse_program() {
        std::vector<AST> stmts;
        while (peek().kind != TokenKind::EndOfFile) {
            stmts.push_back(parse_statement());
        }
        return stmts;
    }
}

std::vector<AST> parse(const std::vector<Token>& toks) {
    tokens = &toks;
    pos = 0;
    try {
        return parse_program();
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return {};
    }
}

