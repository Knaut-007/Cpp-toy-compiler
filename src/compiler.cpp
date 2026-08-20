#include "compiler.hpp"
#include <stdexcept>

int32_t BytecodeCompiler::get_or_create_var_id(const std::string& name) {
    if (symbol_table.find(name) == symbol_table.end()) {
        symbol_table[name] = next_var_id++;
    }
    return symbol_table[name];
}

void BytecodeCompiler::compile(ASTNode* node) {
    if (!node) return;

    if (auto* num = dynamic_cast<NumberNode*>(node)) {
        bytecode.emplace_back(Opcode::PUSH, std::stoi(num->value));
    }
    else if (auto* id = dynamic_cast<IdentifierNode*>(node)) {
        int32_t varId = get_or_create_var_id(id->name);
        bytecode.emplace_back(Opcode::LOAD, varId);
    }
    else if (auto* binop = dynamic_cast<BinaryOpNode*>(node)) {
        // Post-order traversal: Left, Right, Root (Operator)
        compile(binop->left.get());
        compile(binop->right.get());
        
        if (binop->op == "+") bytecode.emplace_back(Opcode::ADD);
        else if (binop->op == "-") bytecode.emplace_back(Opcode::SUB);
        else if (binop->op == "*") bytecode.emplace_back(Opcode::MUL);
        else if (binop->op == "/") bytecode.emplace_back(Opcode::DIV);
        else throw std::runtime_error("Unknown operator: " + binop->op);
    }
    else if (auto* assign = dynamic_cast<AssignmentNode*>(node)) {
        // Evaluate the right side first
        compile(assign->expr.get());
        
        // Store it in the variable's memory slot
        int32_t varId = get_or_create_var_id(assign->name);
        bytecode.emplace_back(Opcode::STORE, varId);
    }
    else {
        throw std::runtime_error("Unknown AST Node type");
    }
}

std::vector<Instruction> BytecodeCompiler::get_bytecode() const {
    return bytecode;
}