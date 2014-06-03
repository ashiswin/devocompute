#ifndef VARIABLE_STORE_TREE_H
#define VARIABLE_STORE_TREE_H

#include "VariableTypes.h"

struct Variable {
	char* name;
	VariableType type;
	Variable *left, *right;
};

class VariableStoreTree {
	public:
		~VariableStoreTree();
		void insert(Variable* &root, Variable* variable);
		Variable* find(Variable* root, char* name);
		void destroy(Variable* root);
		
		Variable* root;
};
#endif