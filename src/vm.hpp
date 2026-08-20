#ifndef VM_HPP
#define VM_HPP

#include <vector>
#include <unordered_map>
#include <cstdint>

enum class Opcode : uint8_t {
    PUSH,
    ADD,
    SUB,
    MUL,
    DIV,
    LOAD,
    STORE,
    HALT
};

struct Instruction {
    Opcode op;
    int32_t operand;
    Instruction(Opcode o, int32_t arg = 0) : op(o), operand(arg) {}
};

class VirtualMachine {
private:
    std::vector<Instruction> bytecode;
    std::vector<int32_t> stack;
    std::unordered_map<int32_t, int32_t> globals;
    size_t pc;

    void push(int32_t value);
    int32_t pop();

public:
    VirtualMachine(const std::vector<Instruction>& code);
    void execute();
    int32_t getVariableValue(int32_t varId) const;
};

#endif // VM_HPP