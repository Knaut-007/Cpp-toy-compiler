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
