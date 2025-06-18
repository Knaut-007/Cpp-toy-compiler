# Day-2 Notes -> Lexical Analysis (Lexer)

Primary source - https://www.tutorialspoint.com/what-is-the-role-of-the-lexical-analyzer-in-compiler-design

- **What is a Lexer ?**
The first phase of a compiler. 
Reads the raw source code character by character, groups those characters into meaningful sequences called lexemes, converts them into a stream of tokens (identifiers, numbers, keywords, etc.). 
Removes whitespace and comments, making it easier for the next phase (parser) to work with a clean structured input.

- The lexer should report errors for invalid characters or malformed tokens, and track line numbers for precise error messages.

- The lexer converts the raw source code into tokens, which are then used by the parser to build a syntax tree.

- It also strips out comments and whitespace, and may interact with the symbol table to record identifiers.

Tokens are the basic building blocks (like words in a sentence) that the parser will use to understand the structure of the code.


- **Why use .hpp and .cpp files**
- .hpp (header) files declare the structures, enums, and function prototypes to share between multiple .cpp files. For organization and to avoid duplication.
- .cpp (source) files contain the actual implementation (function bodies, logic, etc.)

- **What is #pragma once** 
preprocessor directive placed at the top of a header file to ensure the file is included only once per compilation, preventing duplicate definitions and errors.  

## Understanding main.cpp (Arguments, File Streams, and Buffers)

Primary Source - https://stackoverflow.com

- argc: Number of command-line arguments (including program name).

- argv: Array of argument strings; argv[1] is usually the first real argument.

- argc < 2: Means no filename was given; print usage and exit.

- std::ifstream: Reads from files; in(argv[1]) opens the file named by the user.

- std::ostringstream: Builds a string from stream input; buf << in.rdbuf(); reads the whole file into a string.

- buf.str(): Gets the string to pass to the lexer.

- **Test files** - Created test files for each new feature added in the lexer to ensure correctness and make debugging easier.