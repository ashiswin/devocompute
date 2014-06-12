#ifndef VARIABLE_STORE_TREE_H
#define VARIABLE_STORE_TREE_H

#include "VariableTypes.h"

struct Variable {
	char* name;
	VariableType type;
	int index;
	/* Function that this variable belongs to:
	 * 0 - Global
	 * 1 onwards - user defined functions including main
	 */
	int function;
	Variable *left, *right;
};

class VariableStoreTree {
	public:
		~VariableStoreTree();
		int insert(Variable* &root, Variable* variable);
		Variable* find(Variable* root, char* name, int* function);
		void destroy(Variable* root);
		
		Variable* root;
		int index = 0;
};
#endif