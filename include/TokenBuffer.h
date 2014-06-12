/* Copyright (C) 2014 Isaac Ashwin Ravindran
 *
 * TokenBuffer.cpp
 * Provides a means to peek ahead as well as store a few tokens produced by the lexer
 * for access by the parser. This allows the parser to know ahead what the next token
 * emitted will be.
 */

#ifndef TOKENBUFFER_H
#define TOKENBUFFER_H

template <class T> class Queue;
class Token;
class Lexer;

class TokenBuffer {
	private:
		Queue<Token*> *buffer;
		Lexer *lexer;
	public:
		TokenBuffer(Lexer* lexer, int size);
		~TokenBuffer();
		Token* peek(int i);
		void fillBuffer();
		Token* read();
		int getSize();
};

#endif