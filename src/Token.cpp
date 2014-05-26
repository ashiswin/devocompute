#include "Token.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

// Create a new Token object with provided data
Token::Token(TokenType type, char* data, SourcePosition* pos) {
	this->type = type;
	this->data = data;
	this->position = pos;
}

// Destructor; Delete all allocated memory
Token::~Token() {
	free(data);
	free(position);
}

// Generate string representation of Token
char* Token::toString() {
	char* str = (char*) malloc(1024);
	sprintf(str, "%d %s (%d, %d)", type, data, position->lineNo, position->columnNo);
	str = (char*) realloc(str, strlen(str));
	
	return str;
}