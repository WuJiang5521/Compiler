#include <iostream>

#include "tree.h"
#include "translator.h"
#include "cst.h"
#include "parser.hpp"
#include "codegen.h"

using namespace std;

extern int doyyparse();
extern ast::Program* ast_root;

std::string red(const std::string& str) {
	string red_b = "\033[1;31m";
	string red_e = "\033[0m";
	return red_b + str + red_e;
}
std::string green(const std::string& str) {
	string red_b = "\033[1;32m";
	string red_e = "\033[0m";
	return red_b + str + red_e;
}

int main(int argc, char** argv) {
	doyyparse();
	std::cout << "after yyparse()" << std::endl;
	//cout << ast_root << endl;
	//ast_root->print_node("", true, true);
	InitializeNativeTargetAsmPrinter();
	InitializeNativeTargetAsmParser();
	InitializeNativeTarget();
	CodeGenContext context;
	//createCoreFunctions(context);
	context.generateCode(*ast_root);
	//context.runCode();
	return 0;
}
