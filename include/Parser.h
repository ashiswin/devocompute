#ifndef PARSER_H
#define PARSER_H

class Lexer;
class TokenBuffer;

class Parser {
	private:
		TokenBuffer* buffer;
	public:
		Parser(Lexer* lexer);
		~Parser();
};

#endif