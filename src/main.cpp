#include <iostream>
#include <fstream>
#include <sstream>
#include "lexer.hpp"
#include "parser.hpp"
#include "compiler.hpp"
#include "vm.hpp"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>\n";
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "Failed to open file.\n";
        return 1;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string sourceCode = buffer.str();

    // Phase 1: Lexical Analysis
    // Updated to use your exact lex() function
    std::vector<Token> tokens = lex(sourceCode);

    // Phase 2: Syntax Analysis (AST Generation)
    std::vector<AST> program = parse(tokens);

    // Phase 3: Intermediate Code Generation
    BytecodeCompiler compiler;
    for (const auto& stmt : program) {
        stmt->print(); 
        compiler.compile(stmt.get());
    }
    
    // Halt instruction at the end of the program
    std::vector<Instruction> bytecode = compiler.get_bytecode();
    bytecode.emplace_back(Opcode::HALT);

    // Phase 4: Virtual Machine Execution
    std::cout << "\n--- VM Execution Starting ---\n";
    VirtualMachine vm(bytecode);
    vm.execute();
    
    // Testing the result for your `assign_expr.toy`
    // x = 1 + 2 * 3 (should be 7)
    // y = x - 4 (should be 3)
    std::cout << "VM Memory State for x (ID 0): " << vm.getVariableValue(0) << "\n";
    std::cout << "VM Memory State for y (ID 1): " << vm.getVariableValue(1) << "\n";
    std::cout << "--- VM Execution Finished ---\n";

    return 0;
}