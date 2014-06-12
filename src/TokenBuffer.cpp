#include "Lexer.h"
#include "Token.h"
#include "TokenBuffer.h"
#include "TokenTypes.h"
#include "Queue.h"
#include <stdio.h>

TokenBuffer::TokenBuffer(Lexer* lexer, int size) {
	this->lexer = lexer;
	
	this->buffer = new Queue<Token*>(size);
	
	fillBuffer();
}

TokenBuffer::~TokenBuffer() {
	delete buffer;
	if(lexer != NULL) {
		delete lexer;
	}
}

Token* TokenBuffer::peek(int i) {
	return buffer->at(i);
}

void TokenBuffer::fillBuffer() {
	int size = buffer->getSize();
	
	for(int i = 0 ; i < buffer->getMaxSize() - size; i++) {
		if(lexer == NULL) {
			break;
		}
		Token* token = lexer->getToken();
		if(token->type == FEOF) {
			delete lexer;
			break;
		}
		if(token->type == WHITE) {
			continue;
		}
		if(!buffer->push(token)) {
			printf("Unable to push new Token\n");
		}
	}
}

Token* TokenBuffer::read() {
	if(buffer->getSize() == 0) {
		return NULL;
	}
	
	Token* token = buffer->pop();
	fillBuffer();
	
	return token;
}

int TokenBuffer::getSize() {
	return buffer->getSize();
}