#include <iostream>
#include <fstream>
#include <sstream>
#include "lexer.hpp"

int main(int argc, char* argv[]){
    if (argc < 2){
        std::cerr << "usage: compiler <file>\n";
        return 1;
    }
    std::ifstream the_file (argv[1]);
    if(!the_file.is_open()){
        std::cerr << "Could not open file: " << argv[1] << '\n';
        return 1;
    }
    std::ostringstream buf;
    buf << the_file.rdbuf();
    for(auto& tok : lex(buf.str())){
        std::cout << static_cast<int>(tok.kind) << " " << tok.text << '\n';
    }
    return 0;
} 