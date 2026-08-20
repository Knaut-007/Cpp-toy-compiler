# Notes4 — Bytecode Compiler & Stack-Based Virtual Machine (VM)

## What is a Bytecode Virtual Machine?

A **Bytecode Virtual Machine (VM)** is a software-based execution engine that emulates a physical CPU. Instead of translating the Abstract Syntax Tree (AST) directly into complex, platform-dependent native machine code (such as x86-64 or ARM assembly), the compiler translates the AST into a streamlined, platform-independent **Intermediate Representation (IR)** known as **Bytecode**. 

The Virtual Machine then executes these bytecode instructions sequentially using a software-managed runtime stack.

```text
Source Code (.toy)
       │
       ▼ (Lexer)
  Token Stream
       │
       ▼ (Parser)
Abstract Syntax Tree (AST)
       │
       ▼ (Bytecode Compiler - Post-Order Traversal)
Bytecode Instruction Array (IR)
       │
       ▼ (Virtual Machine - Fetch/Decode/Execute)
 Runtime Evaluation & State Output
 ```

 ---

## 1. Instruction Set Architecture (ISA)

The ISA defines the set of operations our Virtual Machine understands. Each instruction consists of an **Opcode** and an optional 32-bit integer **Operand**.

### Opcode Mapping & Stack Behavior

| Opcode | Mnemonic | Operand Used? | Stack Effect (Before -> After) | Description |
| :--- | :--- | :--- | :--- | :--- |
| `0` | `PUSH` | Yes (literal value) | `[...]` -> `[..., val]` | Pushes an immediate integer constant onto the operand stack. |
| `1` | `ADD` | No | `[..., a, b]` -> `[..., a + b]` | Pops two top values, adds them, and pushes the result. |
| `2` | `SUB` | No | `[..., a, b]` -> `[..., a - b]` | Pops `b`, pops `a`, computes `a - b`, and pushes the result. |
| `3` | `MUL` | No | `[..., a, b]` -> `[..., a * b]` | Pops two top values, multiplies them, and pushes the result. |
| `4` | `DIV` | No | `[..., a, b]` -> `[..., a / b]` | Pops `b`, pops `a`, computes `a / b`, and pushes result. Throws on b = 0. |
| `5` | `LOAD` | Yes (var ID) | `[...]` -> `[..., memory[varId]]` | Retrieves variable value from global memory by ID and pushes it. |
| `6` | `STORE` | Yes (var ID) | `[..., val]` -> `[...]` | Pops the top value and stores it into global memory at `varId`. |
| `7` | `HALT` | No | `[...]` -> `[...]` | Terminates the VM execution loop. |

### Memory-Efficient Representation (`src/vm.hpp`)
* **`enum class Opcode : uint8_t`**: Packed into an 8-bit unsigned integer to minimize memory footprint.
* **`struct Instruction`**: Pairs an `Opcode` with an `int32_t operand`.

---

## 2. The Bytecode Compiler (`src/compiler.cpp`)

The compiler acts as the bridge between the high-level tree structure (AST) and the low-level linear instruction array.

### Post-Order AST Traversal
A stack machine requires operands to be on the stack *before* an operator can execute. Therefore, arithmetic expressions are compiled using a **post-order traversal** (Left -> Right -> Root):

1. **`NumberNode`**: Emits `PUSH <value>`.
2. **`IdentifierNode`**: Resolves variable name to an integer ID via the Symbol Table and emits `LOAD <varId>`.
3. **`BinaryOpNode`**: Recursively compiles `left`, then `right`, and finally emits the arithmetic opcode (`ADD`, `SUB`, `MUL`, `DIV`).
4. **`AssignmentNode`**: Compiles the right-hand side expression first, then emits `STORE <varId>`.

### The Symbol Table
Instead of using expensive string lookups inside the high-frequency VM execution loop:
* The compiler maintains an `std::unordered_map<std::string, int32_t> symbol_table`.
* Variable names (`"x"`, `"y"`) are assigned sequential integer IDs (`0`, `1`, ...).
* The VM only interacts with fast integer addresses.

---

## 3. The Execution Engine (`src/vm.cpp`)

The VM operates on a classic **Fetch-Decode-Execute** cycle:

```cpp
while (pc < bytecode.size()) {
    Instruction instr = bytecode[pc++]; // 1. FETCH & advance PC
    switch (instr.op) {                 // 2. DECODE
        case Opcode::ADD: {             // 3. EXECUTE
            int32_t b = pop();
            int32_t a = pop();
            push(a + b);
            break;
        }
        // ... other opcodes
    }
}
```

### Components of the Virtual Machine
* **Operand Stack (`std::vector<int32_t> stack`)**: Fast LIFO container for intermediate arithmetic computations.
* **Program Counter (`size_t pc`)**: Index register pointing to the next instruction in bytecode memory.
* **Global Memory Store (`std::unordered_map<int32_t, int32_t> globals`)**: Persistent runtime state mapping variable IDs to their evaluated values.

---

## 4. Execution Trace: `assign_expr.toy`

### Input Source
```text
x = 1 + 2 * 3
y = x - 4
```

### Emitted Bytecode Stream

```text
Index   Instruction      Operand    Comment
─────────────────────────────────────────────────────────────
[0]     PUSH             1          Stack: [1]
[1]     PUSH             2          Stack: [1, 2]
[2]     PUSH             3          Stack: [1, 2, 3]
[3]     MUL                         Pop 3, Pop 2 -> Push 6.  Stack: [1, 6]
[4]     ADD                         Pop 6, Pop 1 -> Push 7.  Stack: [7]
[5]     STORE            0          Pop 7 -> globals[0] (x) = 7. Stack: []
[6]     LOAD             0          globals[0] -> Push 7.    Stack: [7]
[7]     PUSH             4          Stack: [7, 4]
[8]     SUB                         Pop 4, Pop 7 -> Push 3.  Stack: [3]
[9]     STORE            1          Pop 3 -> globals[1] (y) = 3. Stack: []
[10]    HALT                        Terminate execution.
```

---

## 5. Key C++ Systems Engineering Concepts Used

* **Polymorphic Downcasting (`dynamic_cast`)**: Enables safe AST node inspection and traversal in the compilation pass without polluting AST node structures with compiler logic.
* **Cache Locality (`std::vector`)**: Used for instruction memory and the operand stack to ensure contiguous memory allocation and minimal CPU cache misses.
* **RAII & Exception Safety**: 
  * Stack bounds checking guards against underflows during malformed bytecode runs.
  * Runtime divide-by-zero checks prevent hardware traps.
* **Memory Decoupling**: Lexer tokens, AST nodes (`std::unique_ptr`), and Bytecode instructions are decoupled into separate compilation pipeline stages.

---

## 6. How to Build and Run

### 1. Build the Complete Pipeline
```powershell
g++ src/main.cpp src/lexer.cpp src/parser.cpp src/compiler.cpp src/vm.cpp -o main.exe
```

### 2. Execute on Test File
```powershell
./main.exe tests/parser/assign_expr.toy
```

### 3. Expected Terminal Output
```text
Assignment(x)
  BinaryOp(+)
    Number(1)
    BinaryOp(*)
      Number(2)
      Number(3)
Assignment(y)
  BinaryOp(-)
    Identifier(x)
    Number(4)

--- VM Execution Starting ---
VM Memory State for x (ID 0): 7
VM Memory State for y (ID 1): 3
--- VM Execution Finished ---
```