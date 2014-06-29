#include "VariableStoreTree.h"
#include "VariableTypes.h"
#include "Queue.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

VariableStoreTree::VariableStoreTree() {
	types = new Queue<char>(INT_MAX);
	index = 0;
}

// Destructor, recurses through tree and deletes all nodes
VariableStoreTree::~VariableStoreTree() {
	delete types;
	destroy(root);
}

// Insert new Variable node into tree
int VariableStoreTree::insert(Variable* &root, Variable* variable) {
	if(root == NULL) {
		variable->index = index;
		root = variable;
		
		switch(variable->type) {
			case INT: {
				types->push('i');
				break;
			}
			case FLOAT: {
				types->push('f');
				break;
			}
			case DOUBLE: {
				types->push('d');
				break;
			}
			case SHORT: {
				types->push('s');
				break;
			}
			case BYTE: {
				types->push('b');
				break;
			}
			case VEC2: {
				types->push('v');
				break;
			}
			case VEC4: {
				types->push('w');
				break;
			}
			case VEC8: {
				types->push('x');
				break;
			}
			case VEC16: {
				types->push('y');
				break;
			}
		}
			
		index++;
		return (index - 1);
	}
	
	if(strcmp(root->name, variable->name) < 0) {
		return insert(root->left, variable);
	}
	else {
		return insert(root->right, variable);
	}
}

// Search recursively for a Variable node based on the text
Variable* VariableStoreTree::find(Variable* root, char* name, int* function) {
	if(root == NULL) {
		return NULL;
	}
	
	int compare = strcmp(root->name, name);
	
	if(compare == 0 && root->function == *function) {
		return root;
	}
	else if(compare < 0) {
		return find(root->left, name, function);
	}
	else {
		return find(root->right, name, function);
	}
}

// Get the types of all the variables stored
Queue<char>* VariableStoreTree::getTypes() {
	return types;
}

// Recursively delete each node
void VariableStoreTree::destroy(Variable* root) {
	if(root == NULL) return;
	
	destroy(root->left);
	destroy(root->right);
	
	free(root);
}