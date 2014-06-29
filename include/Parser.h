#ifndef PARSER_H
#define PARSER_H
#include "TokenTypes.h"
#include <stdio.h>

class BinarySearchTree;
class Block;
class FunctionStoreTree;
class Lexer;
class Token;
class TokenBuffer;
class VariableStoreTree;
template <class T> class Queue;

class Parser {
	private:
		BinarySearchTree* variabletypes;
		TokenBuffer* buffer;
		VariableStoreTree* variables;
		Queue<int> *in, *out, *uniform;
		Queue<Block*> *blockList;
		FunctionStoreTree *functions;
		Node *astRoot;
		FILE *bytecode;
		int currentFunction;
	public:
		Parser(Lexer* lexer, const char* bytefile, const char* variabletypesfile);
		~Parser();
		void start();
		Token* match(TokenType type);
		Queue<int>* getArguments();
		void processBlock(Block* block);
		void write();
};

#endif