# Day 3 -> Syntax Analysis (Parser)

Primary source - https://www.tutorialspoint.com/compiler_design/compiler_design_syntax_analysis.htm

## What is Parsing?
Parsing is the process of analyzing a sequence of tokens (from the lexer) to determine its grammatical structure according to the language’s grammar. The parser builds a parse tree or an Abstract Syntax Tree (AST) representing the program.

## What is a Recursive Descent Parser?
A recursive descent parser is a top-down parser built from a set of mutually-recursive functions, where each function implements one of the grammar rules. It is simple to implement and works well for arithmetic expressions and assignment statements.

## Why Build a Parse Tree/AST?
The parse tree (or AST) is a structured, tree-like representation of the source code. It makes it easier for later compiler phases (like semantic analysis or code generation) to process the program.

## Parser Grammar

- program: sequence of assignment statements.
- statement: identifier '=' expression
- expression: term (+/- term)*
- term: factor (* or / factor)*
- factor: number | identifier | (expression)

## AST Nodes

- NumberNode: represents a number literal.
- IdentifierNode: represents a variable name.
- BinaryOpNode: represents binary operations (+, -, *, /).
- AssignmentNode: represents assignments (x = ...).

## Test File

- `assign_expr.toy` tests assignment and arithmetic parsing.

## Recursive Descent Parser Implementation

- Each grammar rule is implemented as a function: `parse_expression`, `parse_term`, etc.
- The parser uses a global position variable to track the current token.
- For each assignment statement (`x = 1 + 2 * 3`), the parser builds an AST using the node classes.
- If the input is invalid, the parser throws and prints a clear error.

## Example: Input, Tokens, and AST Output

### Input (`assign_expr.toy`)

x = 1 + 2 * 3
y = x - 4


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

**Sample Output:**
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



- The `Assignment(x)` node represents `x = ...`
- The `BinaryOp(+)` node represents `1 + (2 * 3)`
- The tree structure shows how the parser groups operations according to precedence.

---

### What This Demonstrates

- The lexer correctly splits the input into tokens.
- The parser builds a tree structure that reflects the grammar and operator precedence.
- This output can be used for further compiler phases, such as semantic analysis or code generation.
