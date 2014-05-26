#include "Lexer.h"
#include "PeekReader.h"
#include "Token.h"
#include <sstream>
#include <string.h>

// Constructor for the lexer
Lexer::Lexer(char* filename, const char* dictionary) {
	// Dictionary file contains relevant TokenType for each character. Refer to tools-src/dictionary.cpp for more details
	FILE* dictionaryFile = fopen(dictionary, "r");
	if(dictionaryFile == NULL) {
		printf("[Lexer Error] Unable to load lexer dictionary\n");
		return;
	}
	
	// Allocate memory for storing the TokenTypes
	this->dictionary = (int*) malloc(sizeof(int) * 256);
	
	// Read in the file
	for(int i = 0; i < 256; i++) {
		fscanf(dictionaryFile, "%d ", &this->dictionary[i]);
	}
	
	// Close dictionary file
	fclose(dictionaryFile);
	
	// Open script
	FILE* scriptFile = fopen(filename, "r");
	if(scriptFile == NULL) {
		printf("[Lexer Error] Unable to load script file\n");
		return;
	}
	
	// Build PeekReader from file pointer
	reader = new PeekReader(scriptFile, 2);
	
	// Initialize SourcePosition struct with beginning of file
	position = (SourcePosition*) malloc(sizeof(SourcePosition));
	position->columnNo = position->lineNo = 0;
}

// Destructor; Deletes all allocated memory blocks
Lexer::~Lexer() {
	free(dictionary);
	free(position);
	delete reader;
}

// Gets a token from the file by lexing it and matching it against the dictionary
Token* Lexer::getToken() {
	// Peek for the next character rather than reading it
	int c = reader->peek(0);
	// Increment SourcePosition by 1
	position->columnNo++;
	
	// Test next character
	switch(c) {
		case -1:
			// End of file detected
			return new Token(FEOF, NULL, position);
		case '/':
			// Test for a block comment
			if(reader->peek(1) == '*') {
				reader->read();
				reader->read();
				return readBlockComment();
			}
			// Test for a line comment
			else if(reader->peek(1) == '/') {
				reader->read();
				reader->read();
				return readLineComment();
			}
			// Only possibility left is divide operation
			else {
				reader->read();
				return new Token(DIVIDE, "/", position);
			}
		case '"':
			// String literal detected
			reader->read();
			return readString();
		case '_':
			// Identifier such as variable, type or function detected
			return readIdentifier();
		case '<':
			if(reader->peek(1) == '=') {
				reader->read();
				reader->read();
				return new Token(LESSEQUAL, "<=", position);
			}
			else {
				reader->read();
				return new Token(LESS, "<", position);
			}
		case '>':
			if(reader->peek(1) == '=') {
				reader->read();
				reader->read();
				return new Token(GREATEREQUAL, ">=", position);
			}
			else {
				reader->read();
				return new Token(GREATER, ">", position);
			}
		case '=':
			if(reader->peek(1) == '=') {
				reader->read();
				reader->read();
				return new Token(EQUAL, "==", position);
			}
			else {
				reader->read();
				return new Token(EQUALS, "=", position);
			}
		default:
			// If it is a character, read identifier
			if((c > 64 && c < 91) || (c > 96 && c < 123)) return readIdentifier();
			// Set SourcePosition to next line if new line detected
			if(c == '\n') {
				position->lineNo++;
				position->columnNo = 0;
			}
			// Number detected
			if(c >= '0' && c <= '9') return readNumber();
			
			// If unmatched, return the TokenType from the dictionary and return relevant Token
			char data[2];
			data[0] = c;
			data[1] = '\0';
			reader->read();
			return new Token(TokenType(dictionary[c]), data, position);
	}
}

// Read block comment
Token* Lexer::readBlockComment() {
	// Initialize stringstream object
	std::stringstream ss;
	
	// Create new SourcePosition object with beginning of comment
	SourcePosition* pos = (SourcePosition*) malloc(sizeof(SourcePosition));
	pos->lineNo = position->lineNo;
	pos->columnNo = position->columnNo;
	
	while(1) {
		// Read next character
		int c = reader->read();
		// Check for end of block comment
		if((c == '*' && reader->peek(0) == '/') || reader->peek(0) == -1) {
			// Read away final /
			reader->read();
			
			// Return Token with comment
			char* str = (char*) malloc(ss.str().length());
			strncpy(str, ss.str().c_str(), ss.str().length());
			return new Token(BCOMMENT, str, pos);
		}
		
		// Add character to string
		ss << (char) c;

		// Set SourcePosition to correct new positions
		position->columnNo++;
		if(c == '\n') {
			position->lineNo++;
			position->columnNo = 0;
		}
	}
}

// Read line comment
Token* Lexer::readLineComment() {
	// Initialize stringstream object
	std::stringstream ss;
	
	// Create new SourcePosition with beginning of comment
	SourcePosition* pos = (SourcePosition*) malloc(sizeof(SourcePosition));
	pos->lineNo = position->lineNo;
	pos->columnNo = position->columnNo;
	
	while(1) {
		// Add current character to stringstream
		ss << (char) reader->read();
		
		// Check if next character is newline or end of file
		if(reader->peek(0) == '\n' || reader->peek(0) == -1) {
			// Return Token with comment
			char* str = (char*) malloc(ss.str().length());
			strncpy(str, ss.str().c_str(), ss.str().length());
			return new Token(LCOMMENT, str, pos);
		}
		// Update SourcePosition
		position->columnNo++;
	}
}

// Read string literal
Token* Lexer::readString() {
	// Initialize stringstream object
	std::stringstream ss;
	
	// Create new SourcePosition with beginning of string
	SourcePosition* pos = (SourcePosition*) malloc(sizeof(SourcePosition));
	pos->lineNo = position->lineNo;
	pos->columnNo = position->columnNo;
	
	while(1) {
		// Read next character and add it to string
		int c = reader->read();
		ss << (char)c;
		
		// Check if next character is end of string literal or end of file
		if(reader->peek(0) == '"' || reader->peek(0) == -1) {
			// Read away the "
			reader->read();
			
			// Return Token with string data
			char* str = (char*) malloc(ss.str().length());
			strncpy(str, ss.str().c_str(), ss.str().length());
			return new Token(STRING, str, pos);
		}
		
		// Update SourcePosition
		if(c == '\n') {
			position->lineNo++;
			position->columnNo = 0;
		}
		position->columnNo++;
	}
}

// Read identifier
Token* Lexer::readIdentifier() {
	// Initialize stringstream object
	std::stringstream ss;
	
	// Create new SourcePosition with beginning of identifier
	SourcePosition* pos = (SourcePosition*) malloc(sizeof(SourcePosition));
	pos->lineNo = position->lineNo;
	pos->columnNo = position->columnNo;
	char* str;
	
	while(1) {
		// Get current character and next character
		int c = reader->read();
		int p = reader->peek(0);
		
		// Add current character to string
		ss << (char)c;
		
		// If next character is not a valid character in an identifier, break
		if(!((p >= 'a' && p <= 'z') || (p >= 'A' && p <= 'Z') || (p >= '0' && p <= '9') || p == '_')) {
			// Get contents of stringstream as a character array
			str = (char*) malloc(ss.str().length());
			strncpy(str, ss.str().c_str(), ss.str().length());
			break;
		}
		
		// Update SourcePosition
		position->columnNo++;
	}
	// Check for matches with reserved words
	// TODO: Create a binary search tree with data from dictionary to match against larger set of reserved words quickly
	if(strcmp("for", str) == 0) {
		return new Token(FOR, str, pos);
	}
	else if(strcmp("while", str) == 0) {
		return new Token(WHILE, str, pos);
	}
	
	// If unmatched, return as a VARIABLE Token
	return new Token(VARIABLE, str, pos);
}

// Read number
Token* Lexer::readNumber() {
	// Initialize stringstream object
	std::stringstream ss;
	
	// Create new SourcePosition with beginning of number
	SourcePosition* pos = (SourcePosition*) malloc(sizeof(SourcePosition));
	pos->lineNo = position->lineNo;
	pos->columnNo = position->columnNo;
	
	while(1) {
		// Read current and next character
		int c = reader->read();
		int p = reader->peek(0);
		
		// Add current character to string
		ss << (char)c;
		
		// If non-numeric character detected, break
		if(!(p >= '0' && p <= '9')) {
			// Return Token with number as a character array for later processing
			char* str = (char*) malloc(ss.str().length());
			strncpy(str, ss.str().c_str(), ss.str().length());
			return new Token(NUMBER, (char*) str, pos);
		}
		
		// Update SourcePosition
		position->columnNo++;
	}
}