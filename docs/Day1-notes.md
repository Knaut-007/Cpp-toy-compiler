# Day-1 Notes — Compiler Pipeline

Source - https://www.tutorialspoint.com/compiler_design/index.htm

## Language Processing System

- **Preprocessor** - produces input for compilers. Deals with macro-processing, augmentation, file inclusion, language extenion etc.
expands `#include`, macros and conditionals, leaving plain C/C++ the compiler can read.

- **Compiler** - A compiler reads the whole source code at once, creates tokens, checks semantics, generates intermediate code, executes the whole program and may involve many passes.
runs the internal phases below and emits assembly (`.s`)

- **Interpreter** - reads a statement from the input, converts it to an intermediate code, executes it, then takes the next statement in sequence. If an error occurs, an interpreter stops execution and reports it.
(alt-path) reads one statement, turns it into intermediate code, executes at once, stops on the first run-time error

- **Assembler** - An assembler translates assembly language programs into machine code.The output of an assembler is called an object file, which contains a combination of machine instructions as well as the data required to place these instructions in memory.
converts assembly mnemonics to raw op-codes inside an object file (`.o`)

- **Linker** - links and merges various object files together in order to make an executable file. All these files might have been compiled by separate assemblers. The major task of a linker is to search and locate referenced module/routines in a program and to determine the memory location where these codes will be loaded, making the program instruction to have absolute references.
stitches object files & libs together, fixes external symbols, writes the final executable

- **Loader** - Loader is a part of operating system and is responsible for loading executable files into memory and execute them. It calculates the size of a program (instructions and data) and creates memory space for it. It initializes various registers to initiate execution.
part of the OS; loads the exe into RAM, patches addresses, jumps to `main()`

## Phases of a Compiler 

## 1. Lexical Analysis  
The first phase of scanner works as a text scanner. This phase scans the source code as a stream of characters and converts it into meaningful lexemes. Lexical analyzer represents these lexemes in the form of tokens as: <token-name, attribute-value>
- Consumes characters → produces tokens `<token-name, attr>`.  
- Uses regex-based DFAs; tools: **Lex / flex**. 

## 2. Syntax Analysis  
The next phase is called the syntax analysis or PARSING. It takes the token produced by lexical analysis as input and generates a parse tree (or syntax tree). In this phase, token arrangements are checked against the source code grammar, i.e. the parser checks if the expression made by the tokens is syntactically correct.
- Consumes tokens → builds a parse/AST tree according to grammar rules.  
- Algorithms: LL (recursive-descent) or LR table parsers.

## 3. Semantic Analysis  
Semantic analysis checks whether the parse tree constructed follows the rules of language. For example, assignment of values is between compatible data types, and adding string to an integer. Also, the semantic analyzer keeps track of identifiers, their types and expressions; whether identifiers are declared before use or not etc. The semantic analyzer produces an annotated syntax tree as an output.
- Walks the tree, checks type rules & declarations, outputs an annotated tree. 

## 4. Intermediate Code Generation  
After semantic analysis the compiler generates an intermediate code of the source code for the target machine. It represents a program for some abstract machine. It is in between the high-level language and the machine language. This intermediate code should be generated in such a way that it makes it easier to be translated into the target machine code.
- Converts the annotated tree to a machine-neutral IR (e.g., three-address code)

## 5. Code Optimisation & Final Code Generation  
Optimization can be assumed as something that removes unnecessary code lines, and arranges the sequence of statements in order to speed up the program execution without wasting resources (CPU, memory).
code generator takes the optimized representation of the intermediate code and maps it to the target machine language. The code generator translates the intermediate code into a sequence of (generally) re-locatable machine code. Sequence of instructions of machine code performs the task as the intermediate code would do.
- Optimiser trims IR (dead-code, constant-fold).  
- Code-gen maps the cleaned IR to relocatable machine code

## 6. Symbol Table
A data-structure maintained throughout all the phases of a compiler. All the identifier's names along with their types are stored here. The symbol table makes it easier for the compiler to quickly search the identifier record and retrieve it. The symbol table is also used for scope management.
- Shared structure holding *identifier → type/scope* for every phase
