/* Copyright (C) 2014 Isaac Ashwin Ravindran
 *
 * TokenTypes.h
 * Provides an enumeration of all valid tokens in the language
 */
#ifndef TOKENTYPES_H
#define TOKENTYPES_H

enum TokenType {
	ADD, MINUS, MULTIPLY, DIVIDE, MOD, POWER, EQUALS,
	OR, AND, NOT,
	NUMBER, STRING, VARIABLE, IDENTIFIER,
	LBRACE, RBRACE, LBRACKET, RBRACKET, LPAR, RPAR,
	LCOMMENT, BCOMMENT, 
	NUL, END, INVALID, WHITE, FEOF, COMMA,
	FOR, WHILE, TYPE,
	LESS, LESSEQUAL, GREATER, GREATEREQUAL, EQUAL
};

#endif