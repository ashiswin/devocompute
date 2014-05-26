#include "Lexer.h"
#include "Token.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
	if(argc < 2) {
		printf("Usage: devocomp-dist <scriptfile>\n");
		return -1;
	}
	
	Lexer *lexer = new Lexer(argv[1], "dictionary.txt");
	while(1) {
		Token* token = lexer->getToken();
		
		if(token->type == FEOF) {
			delete token;
			break;
		}
		if(token->type == WHITE) {
			continue;
		}
		printf("%s\n", token->toString());
	}
	
	return 0;
}