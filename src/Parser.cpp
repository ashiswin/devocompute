#include "BinarySearchTree.h"
#include "Block.h"
#include "FunctionStoreTree.h"
#include "Lexer.h"
#include "Parser.h"
#include "Queue.h"
#include "Token.h"
#include "TokenBuffer.h"
#include "VariableStoreTree.h"
#include <stdlib.h>
#include <string.h>
#include <limits.h>

Parser::Parser(Lexer* lexer, const char* outfile, const char* variabletypesfile) {
	bytecode = fopen(outfile, "w");
	if(bytecode == NULL) {
		printf("[Parser Error] Unable to open bytecode file for writing!\n");
		return;
	}
	
	FILE *vartypes = fopen(variabletypesfile, "r");
	if(vartypes == NULL) {
		printf("[Parser Error] Unable to open variable types file!\n");
		return;
	}
	
	variabletypes = new BinarySearchTree();
	int i = 0;
	
	while(!feof(vartypes)) {
		if(feof(vartypes)) break;

		Keyword* keyword = (Keyword*) malloc(sizeof(Keyword));
		
		fscanf(vartypes, "%s", keyword->text);
		keyword->type = TokenType(i);
		variabletypes->insert(variabletypes->root, keyword);
		i++;
	}
	
	fclose(vartypes);
	
	buffer = new TokenBuffer(lexer, 3);
	variables = new VariableStoreTree();
	in = new Queue<int>(INT_MAX);
	out = new Queue<int>(INT_MAX);
	uniform = new Queue<int>(INT_MAX);
	blockList = new Queue<Block*>(INT_MAX);
	functions = new FunctionStoreTree();
	
	currentFunction = 0;
}

Parser::~Parser() {
	fclose(bytecode);
	delete variabletypes;
	delete buffer;
	delete variables;
	delete in;
	delete out;
	delete uniform;
}

Token* Parser::match(TokenType type) {
	Token* token = buffer->read();
	if(type == token->type) {
		return token;
	}
	else {
		printf("[Parser Error] Expected %d but found %d at line %d, column %d\n", type, token->type, token->position->lineNo, token->position->columnNo);
		return NULL;
	}
}

void Parser::start() {
	while(buffer->getSize()) {
		Token* token = buffer->peek(0);
		
		switch(token->type) {
			case IN: {
				match(IN);
				Token* tokType = match(TYPE);
				Token* tokName = match(VARIABLE);
				match(END);
				
				Variable* variable = variables->find(variables->root, tokName->data, &currentFunction);
				if(variable == NULL) {
					Variable *variable = (Variable*) malloc(sizeof(Variable));
					variable->name = (char*)malloc(sizeof(tokName->data));
					strncpy(variable->name, tokName->data, strlen(tokName->data));
					variable->type = VariableType(variabletypes->find(variabletypes->root, tokType->data)->type);
					variable->function = currentFunction;
					in->push(variables->insert(variables->root, variable));
				}
				else {
					printf("[Parser Error] Redefinition of variable %s\n", variable->name);
					free(variable);
				}
				
				break;
			}
			case OUT: {
				match(OUT);
				Token* tokType = match(TYPE);
				Token* tokName = match(VARIABLE);
				match(END);
				
				Variable* variable = variables->find(variables->root, tokName->data, &currentFunction);
				if(variable == NULL) {
					Variable *variable = (Variable*) malloc(sizeof(Variable));
					variable->name = (char*)malloc(sizeof(tokName->data));
					strncpy(variable->name, tokName->data, strlen(tokName->data));
					variable->type = VariableType(variabletypes->find(variabletypes->root, tokType->data)->type);
					variable->function = currentFunction;
					out->push(variables->insert(variables->root, variable));
				}
				else {
					printf("[Parser Error] Redefinition of variable %s\n", variable->name);
					free(variable);
				}
				
				break;
			}
			case UNIFORM: {
				match(UNIFORM);
				Token* tokType = match(TYPE);
				Token* tokName = match(VARIABLE);
				match(END);
				
				Variable* variable = variables->find(variables->root, tokName->data, &currentFunction);
				if(variable == NULL) {
					Variable *variable = (Variable*) malloc(sizeof(Variable));
					variable->name = (char*)malloc(sizeof(tokName->data));
					strncpy(variable->name, tokName->data, strlen(tokName->data));
					variable->type = VariableType(variabletypes->find(variabletypes->root, tokType->data)->type);
					variable->function = currentFunction;
					uniform->push(variables->insert(variables->root, variable));
				}
				else {
					printf("[Parser Error] Redefinition of variable %s\n", variable->name);
					free(variable);
				}
				
				break;
			}
			case TYPE: {
				Token* tokType = match(TYPE);
				Token* tokName = match(VARIABLE);
				
				if(buffer->peek(0)->type == LPAR) {
					match(LPAR);
					
					Function* function = functions->findFunction(functions->root, tokName->data);
					if(function != NULL) {
						printf("[Parser Error] Redefinition of function %s\n", function->name);
						free(function);
						break;
					}
					
					Block* block = new Block();
					blockList->push(block);
					int blockId = blockList->getSize();
					
					Function* function = (Function*) malloc(sizeof(Function));
					strncpy(function->name, tokName->data, strlen(tokName->data));
					function->ret = VariableType(variabletypes->find(variabletypes->root, tokType->data)->type);
					function->arguments = getArguments();
					function->block = blockId;
					currentFunction = functions->addFunction(functions->root, function);
					
					processBlock(block);
					
					currentFunction = 0;
					
					break;
				}
				
				Variable* variable = variables->find(variables->root, tokName->data, &currentFunction);
				if(variable == NULL) {
					Variable *variable = (Variable*) malloc(sizeof(Variable));
					variable->name = (char*)malloc(sizeof(tokName->data));
					strncpy(variable->name, tokName->data, strlen(tokName->data));
					variable->type = VariableType(variabletypes->find(variabletypes->root, tokType->data)->type);
					variable->function = currentFunction;
					variables->insert(variables->root, variable);
				}
				else {
					printf("[Parser Error] Redefinition of variable %s\n", variable->name);
					free(variable);
				}
				
				break;
			}
			default: {
				printf("[Parser Error] Invalid token %s(%d) detected!\n", token->data, token->type);
				return;
			}
		}
	}
}

Queue<int>* Parser::getArguments() {
	
}

void Parser::processBlock(Block* block) {
}

void Parser::write() {
	// Write the bytecode version
	fprintf(bytecode, "0.1\n");
	
	// Write variable types
	Queue<char> *types = variables->getTypes();
	int variableCount = types->getSize();
	fprintf(bytecode, "%d ", variableCount);
	for(int i = 0; i < variableCount; i++) {
		fprintf(bytecode, "%c", types->pop());
	}
	fprintf(bytecode, "\n");
	
	// Write all IN variables
	int size = in->getSize();
	fprintf(bytecode, "%d", size);
	for(int i = 0; i < size; i++) {
		fprintf(bytecode, " %d", in->pop());
	}
	fprintf(bytecode, "\n");
	
	// Write all OUT variables
	int outCount = out->getSize();
	fprintf(bytecode, "%d", outCount);
	for(int i = 0; i < outCount; i++) {
		fprintf(bytecode, " %d", out->pop());
	}
	fprintf(bytecode, "\n");
	
	// Write all UNIFORM variables
	int uniformCount = uniform->getSize();
	fprintf(bytecode, "%d", uniformCount);
	for(int i = 0; i < uniformCount; i++) {
		fprintf(bytecode, " %d", uniform->pop());
	}
	fprintf(bytecode, "\n");
}