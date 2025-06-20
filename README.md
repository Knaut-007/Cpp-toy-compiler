# C++ Toy Compiler

This is my attempt at building a tiny compiler for a super simple C++-like language, just to really understand how compilers work and to show I get the basics of Theory of Computation (Learned in 4th Sem MNC) and C++. This project is all about learning by doing, so I kept everything as clear and beginner-friendly as possible.

---

## What This Project Does

- **Reads a text file written in a toy language (looks a bit like C++).**
- **Breaks the code into tokens** (like words: variable names, numbers, operators, etc.).
- **Parses those tokens** into a tree structure (the AST) that shows how the code is built up (like, what gets added or multiplied first).
- **Prints out the token stream and the AST** so you can see exactly what the compiler is doing.

---

## Why I Made This

- To actually *see* how a compiler takes raw code and turns it into something a computer can work with.
- To practice C++, file handling, and recursive functions.
- To have a real project on my GitHub that shows I understand compiler basics and can write clean, tested code.

---

## How It Works (In Plain English)

1. **Lexical Analysis (Lexer):**
   - Reads your source code character by character.
   - Groups characters into tokens: identifiers (like `x`), numbers (`123`), operators (`+`, `-`, `*`, `/`, `=`), parentheses, and even unknown characters (like `$`).
   - Skips over any whitespace.
   - If it finds something weird (like `@`), it prints a warning and still makes a token for it.

2. **Syntax Analysis (Parser):**
   - Takes the list of tokens and checks if they make sense together.
   - Builds a tree (AST) that shows the structure of each statement (like `x = 1 + 2 * 3`).
   - Handles operator precedence, so multiplication happens before addition, just like in real math.
   - Prints the AST in a way that’s easy to read and follow.

3. **Testing:**
   - Every feature (identifiers, numbers, operators, errors) has its own test file in the `tests/` folder.
   - You can run the compiler on any of these files and see exactly what happens at each step.

---

## What You Can Run

### Example Input (`tests/parser/assign_expr.toy`):
x = 1 + 2 * 3
y = x - 4


### Example Output:
0 x
2 =
1 1
3 +
1 2
5 *
1 3
0 y
2 =
0 x
4 -
1 4
10
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

### Token Output

Each line shows the token kind (as an integer) and the token text.

| Kind | TokenKind   | Example |
|------|-------------|---------|
| 0    | Identifier  | x, y    |
| 1    | Number      | 1, 2, 3, 4 |
| 2    | Equal       | =       |
| 3    | Plus        | +       |
| 4    | Minus       | -       |
| 5    | Star        | *       |
| 10   | EndOfFile   |         |

### AST (Parse Tree) Output

Each assignment is shown as a tree, with indentation for child nodes:

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


3. **What you’ll see:**
- The token stream (optional, can comment out in `main.cpp`).
- The AST for each assignment, showing how the code is structured.

---

## Project Structure

- `src/` — All the C++ source files (main, lexer, parser, AST nodes)
- `tests/lexer/` — Test files for the lexer (identifiers, numbers, operators, unknowns)
- `tests/parser/` — Test files for parser (assignments, expressions)
- `docs/` — My detailed notes on every phase, with theory, code, and test explanations
- `README.md` — This file

---

## What I Learned

- How a compiler takes code from raw text to a structured tree.
- The difference between lexical analysis (finding words) and parsing (finding structure).
- How to write and test recursive functions in C++.
- The value of documenting each step and testing every feature.

---

## What to see

If you want to see what my compiler can do:
- Check out the test files in `tests/`.
- Run the compiler on them and look at the printed AST.
- Read the notes in `docs/` for a step-by-step explanation of every phase.

---

## References & Resources

- [Tutorialspoint: Compiler Design](https://www.tutorialspoint.com/compiler_design/index.htm)
- [Let's Create a Compiler (YouTube)](https://www.youtube.com/watch?v=vcSijrRsrY0)

---
