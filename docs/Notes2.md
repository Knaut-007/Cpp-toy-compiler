# Notes2 -> Lexical Analysis (Lexer)

Primary source - https://www.tutorialspoint.com/what-is-the-role-of-the-lexical-analyzer-in-compiler-design

- **What is a Lexer ?**
The first phase of a compiler. 
Reads the raw source code character by character, groups those characters into meaningful sequences called lexemes, converts them into a stream of tokens (identifiers, numbers, keywords, etc.). 
Removes whitespace and comments, making it easier for the next phase (parser) to work with a clean structured input.

- The lexer should report errors for invalid characters or malformed tokens, and track line numbers for precise error messages.

- The lexer converts the raw source code into tokens, which are then used by the parser to build a syntax tree.

- It also strips out comments and whitespace, and may interact with the symbol table to record identifiers.

- - Tokens are the basic building blocks (like words in a sentence) that the parser will use to understand the structure of the code.


## Why use .hpp and .cpp files
- .hpp (header) files declare the structures, enums, and function prototypes to share between multiple .cpp files. For organization and to avoid duplication.
- .cpp (source) files contain the actual implementation (function bodies, logic, etc.)

## What is #pragma once
- preprocessor directive placed at the top of a header file to ensure the file is included only once per compilation, preventing duplicate definitions and errors.  

## Understanding main.cpp (Arguments, File Streams, and Buffers)

Primary Source - https://stackoverflow.com

- argc: Number of command-line arguments (including program name).

- argv: Array of argument strings; argv[1] is usually the first real argument.

- argc < 2: Means no filename was given; print usage and exit.

- std::ifstream: Reads from files; in(argv[1]) opens the file named by the user.

- std::ostringstream: Builds a string from stream input; buf << in.rdbuf(); reads the whole file into a string.

- buf.str(): Gets the string to pass to the lexer.

## Test files 
- Created test files for each new feature added in the lexer to ensure correctness and make debugging easier.

# Lexer: Token Table, Test Coverage, and Logic

## TokenKind Enum Mapping

| Integer Value | TokenKind   | Example      |
|---------------|-------------|--------------|
| 0             | Identifier  | `foo`, `bar` |
| 1             | Number      | `42`, `7`    |
| 2             | Equal       | `=`          |
| 3             | Plus        | `+`          |
| 4             | Minus       | `-`          |
| 5             | Star        | `*`          |
| 6             | Slash       | `/`          |
| 7             | LParen      | `(`          |
| 8             | RParen      | `)`          |
| 9             | Unknown     | `$`, `@`, `#`|
| 10            | EndOfFile   |              |

*This table matches the order in the `TokenKind` enum and helps to quickly interpret the output of the lexer tests.*[1]


## Test File Coverage

- **identifiers.toy** — tests recognition of identifiers like `foo`, `bar`, `myVar123`.
- **numbers.toy** — tests recognition of numbers like `123`, `42`, `0`.
- **operators.toy** — tests recognition of operators: `=`, `+`, `-`, `*`, `/`.
- **parentheses.toy** — tests recognition of parentheses: `(`, `)`.
- **unknowns.toy** — tests handling of unknown/invalid characters like `$`, `@`, `#`.


*All these test files are in `tests/lexer/` and the lexer correctly tokenizes each case, as verified by running `./main.exe` on each file and checking the output matches the expected token kinds and text.*[1]

---

## Lexer Logic (How The Lexer Works)

- **Whitespace:**  
  Skips any whitespace characters using `std::isspace` before checking for tokens.

- **Identifiers:**  
  If the current character is a letter or underscore, starts an identifier token.  
  Continues while the character is alphanumeric or underscore, then emits a token of kind `Identifier` with the matched text.

- **Numbers:**  
  If the current character is a digit, starts a number token.  
  Continues while the character is a digit, then emits a token of kind `Number` with the matched text.

- **Single-Character Tokens:**  
  Checks for `=`, `+`, `-`, `*`, `/`, `(`, `)`.
  Emits the corresponding token kind and advances to the next character.

- **End of File:**  
  After processing all input, appends an `EndOfFile` token to signal the end of the token stream.

*This order ensures that whitespace is ignored, identifiers and numbers are grouped correctly, and all single-character tokens are recognized individually.*[1]

#### Handling Unknown Characters

- If the lexer encounters a character that does not match any known token type, it:
  - Prints a warning to `std::cerr` with the character and its position.
  - Emits a token of kind `Unknown` with the character as its text.
- This ensures that typos or unsupported symbols are not silently ignored and are visible both in the output and as warnings in the terminal[#].

**Reference:**  
https://www.tutorialspoint.com/what-is-the-role-of-the-lexical-analyzer-in-compiler-design
