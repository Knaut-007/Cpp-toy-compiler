#ifndef COMPILER_HPP
#define COMPILER_HPP

#include "vm.hpp"
#include "parser.hpp" // Assuming your AST nodes are defined here or in ast.hpp
#include <vector>
#include <unordered_map>
#include <string>

class BytecodeCompiler {
private:
    std::vector<Instruction> bytecode;
    std::unordered_map<std::string, int32_t> symbol_table;
    int32_t next_var_id = 0;

    int32_t get_or_create_var_id(const std::string& name);

public:
    // We will pass the root of your AST here
    void compile(ASTNode* node); 
    std::vector<Instruction> get_bytecode() const;
};

#endif // COMPILER_HPP