#include "vm.hpp"
#include <stdexcept>
#include <iostream>

VirtualMachine::VirtualMachine(const std::vector<Instruction>& code) 
    : bytecode(code), pc(0) {}

void VirtualMachine::push(int32_t value) {
    stack.push_back(value);
}

int32_t VirtualMachine::pop() {
    if (stack.empty()) {
        throw std::runtime_error("Stack underflow: Invalid instruction sequence.");
    }
    int32_t val = stack.back();
    stack.pop_back();
    return val;
}

void VirtualMachine::execute() {
    while (pc < bytecode.size()) {
        Instruction instr = bytecode[pc++];
        
        switch (instr.op) {
            case Opcode::PUSH:
                push(instr.operand);
                break;
            case Opcode::ADD: {
                int32_t b = pop();
                int32_t a = pop();
                push(a + b);
                break;
            }
            case Opcode::SUB: {
                int32_t b = pop();
                int32_t a = pop();
                push(a - b);
                break;
            }
            case Opcode::MUL: {
                int32_t b = pop();
                int32_t a = pop();
                push(a * b);
                break;
            }
            case Opcode::DIV: {
                int32_t b = pop();
                int32_t a = pop();
                if (b == 0) throw std::runtime_error("Division by zero!");
                push(a / b);
                break;
            }
            case Opcode::LOAD:
                push(globals[instr.operand]);
                break;
            case Opcode::STORE:
                globals[instr.operand] = pop();
                break;
            case Opcode::HALT:
                return;
        }
    }
}

int32_t VirtualMachine::getVariableValue(int32_t varId) const {
    auto it = globals.find(varId);
    if (it != globals.end()) return it->second;
    throw std::runtime_error("Variable not found in VM memory.");
}