#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "TokenTypes.h"

struct Keyword {
	char text[10];
	TokenType type;
	Keyword *left, *right;
};

class BinarySearchTree {
	public:
		~BinarySearchTree();
		void insert(Keyword* &root, Keyword* keyword);
		Keyword* find(Keyword* root, char* text);
		void destroy(Keyword* root);
		
		Keyword* root;
};
#endif