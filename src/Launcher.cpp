#include "Lexer.h"
#include "Parser.h"
#include "Token.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
	if(argc < 2) {
		printf("Usage: devocomp-dist <scriptfile>\n");
		return -1;
	}
	
	Lexer *lexer = new Lexer(argv[1], "dictionary.txt", "identifiers.txt");
	Parser *parser = new Parser(lexer, "bytecode.dev", "variabletypes.txt");
	
	parser->start();
	parser->write();
	
	return 0;
}