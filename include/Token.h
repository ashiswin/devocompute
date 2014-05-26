/* Copyright (C) 2014 Isaac Ashwin Ravindran
 * 
 * Token.cpp
 * Implementation of a structure to hold basic information of a token.
 * Contains an enum of the type of token, the source string that generated this token and
 * the position in the file where this token was found
 */
#ifndef TOKEN_H
#define TOKEN_H
#include "TokenTypes.h"
#include "SourcePosition.h"

class Token {
	public:
		Token(TokenType type, char* data, SourcePosition* pos);
		~Token();
		char* toString();
		
		TokenType type;
		char* data;
		SourcePosition* position;
};

#endif