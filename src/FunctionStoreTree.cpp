#include "FunctionStoreTree.h"
#include "Queue.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

FunctionStoreTree::FunctionStoreTree() {
	index = 0;
}

// Destructor, recurses through tree and deletes all nodes
FunctionStoreTree::~FunctionStoreTree() {
	destroy(root);
}

int FunctionStoreTree::addFunction(Function* &root, Function* function) {
	if(root == NULL) {
		function->index = index;
		root = function;
			
		index++;
		return (index - 1);
	}
	
	if(strcmp(root->name, function->name) < 0) {
		return addFunction(root->left, function);
	}
	else {
		return addFunction(root->right, function);
	}
}

Function* FunctionStoreTree::findFunction(Function* root, char* name) {
	if(root == NULL) {
		return NULL;
	}
	
	int compare = strcmp(root->name, name);
	
	if(compare == 0) {
		return root;
	}
	else if(compare < 0) {
		return findFunction(root->left, name);
	}
	else {
		return findFunction(root->right, name);
	}
}

void FunctionStoreTree::destroy(Function* root) {
	if(root == NULL) return;
	
	destroy(root->left);
	destroy(root->right);
	
	free(root);
}