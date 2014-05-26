#ifndef LEXER_H
#define LEXER_H
#include "SourcePosition.h"
#include "TokenTypes.h"

class Token;
class PeekReader;
class Lexer {
	private:
		PeekReader *reader;
		SourcePosition* position;
		int* dictionary;
	public:
		Lexer(char* filename, const char* dictionary);
		~Lexer();
		Token* getToken();
		Token* readBlockComment();
		Token* readLineComment();
		Token* readString();
		Token* readIdentifier();
		Token* readNumber();
};

#endif