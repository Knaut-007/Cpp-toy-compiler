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
std::vector<AST> parse(const std::vector<Token>& tokens) {
    
    return {};
}
