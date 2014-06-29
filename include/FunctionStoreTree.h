#ifndef FUNCTIONSTORETREE_H
#define FUNCTIONSTORETREE_H
#include "VariableTypes.h"

template <class T> class Queue;

struct Function {
	char* name;
	VariableType ret;
	int index;
	Function *left, *right;
	Queue<int> *arguments;
	int block;
};

class FunctionStoreTree {
	public:
		FunctionStoreTree();
		~FunctionStoreTree();
		int addFunction(Function* &root, Function* function);
		Function* findFunction(Function* root, char* name);
		void destroy(Function* function);
		Function* root;
	private:
		int index;
};

#endif