#pragma once
#include <string>
#include <vector>
#include <memory>
#include "lexer.hpp"

// AST Node Types
struct ASTNode {
    virtual ~ASTNode() = default;
    virtual void print(int indent = 0) const = 0;
};

using AST = std::unique_ptr<ASTNode>;

struct NumberNode : ASTNode {
    std::string value;
    NumberNode(std::string v) : value(std::move(v)) {}
    void print(int indent = 0) const override;
};

struct IdentifierNode : ASTNode {
    std::string name;
    IdentifierNode(std::string n) : name(std::move(n)) {}
    void print(int indent = 0) const override;
};

struct BinaryOpNode : ASTNode {
    std::string op;
    AST left, right;
    BinaryOpNode(std::string o, AST l, AST r)
        : op(std::move(o)), left(std::move(l)), right(std::move(r)) {}
    void print(int indent = 0) const override;
};

struct AssignmentNode : ASTNode {
    std::string name;
    AST expr;
    AssignmentNode(std::string n, AST e)
        : name(std::move(n)), expr(std::move(e)) {}
    void print(int indent = 0) const override;
};

std::vector<AST> parse(const std::vector<Token>& tokens);
