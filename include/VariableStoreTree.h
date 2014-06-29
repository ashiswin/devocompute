#ifndef VARIABLE_STORE_TREE_H
#define VARIABLE_STORE_TREE_H

#include "VariableTypes.h"

template <class T> class Queue;

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
		VariableStoreTree();
		~VariableStoreTree();
		int insert(Variable* &root, Variable* variable);
		Variable* find(Variable* root, char* name, int* function);
		Queue<char>* getTypes();
		void destroy(Variable* root);
		
		Variable* root;
		int index;
	private:
		Queue<char>* types;
};
#endif