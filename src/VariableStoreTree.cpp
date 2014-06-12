#include "VariableStoreTree.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// Destructor, recurses through tree and deletes all nodes
VariableStoreTree::~VariableStoreTree() {
	destroy(root);
}

// Insert new Variable node into tree
int VariableStoreTree::insert(Variable* &root, Variable* variable) {
	if(root == NULL) {
		variable->index = index;
		root = variable;
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

// Recursively delete each node
void VariableStoreTree::destroy(Variable* root) {
	if(root == NULL) return;
	
	destroy(root->left);
	destroy(root->right);
	
	free(root);
}