#ifndef LEXER_H
#define LEXER_H
#include "SourcePosition.h"
#include "TokenTypes.h"

class Token;
class PeekReader;
class BinarySearchTree;

class Lexer {
	private:
		PeekReader *reader;
		SourcePosition* position;
		int* dictionary;
		BinarySearchTree* identifiers;
	public:
		Lexer(char* filename, const char* dictionary, const char* identifiers);
		~Lexer();
		Token* getToken();
		Token* readBlockComment();
		Token* readLineComment();
		Token* readString();
		Token* readIdentifier();
		Token* readNumber();
};

#endif