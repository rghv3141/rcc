#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "token.hpp"
#include "parser.hpp"
#include "codegen.hpp"
#include "llvm/Support/raw_ostream.h"

int main(int argc, char** argv) {
	if (argc != 2) {
		std::cerr << "Incorrect Usage" << std::endl;
		std::cerr << "rcc <input.c>" << std::endl;
		return EXIT_FAILURE;
	}
	
	
	std::string contents;
	{
		std::stringstream contents_stream;
		std::fstream input(argv[1], std::ios::in);
		contents_stream << input.rdbuf();
		contents = contents_stream.str();
	}

	Parser parser(contents);
	InitializeModule();
	auto FnAST = parseFunction();
	auto *FnIR = FnAST->codegen();
	TheModule->print(errs(), nullptr);
	return EXIT_SUCCESS;
} 

