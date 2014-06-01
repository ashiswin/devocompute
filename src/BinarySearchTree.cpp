#include "BinarySearchTree.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

BinarySearchTree::~BinarySearchTree() {
	destroy(root);
}

void BinarySearchTree::insert(Keyword* &root, Keyword* keyword) {
	if(root == NULL) {
		root = keyword;
		return;
	}
	
	if(strcmp(root->text, keyword->text) < 0) {
		return insert(root->left, keyword);
	}
	else {
		return insert(root->right, keyword);
	}
}

Keyword* BinarySearchTree::find(Keyword* root, char* text) {
	if(root == NULL) {
		return NULL;
	}
	
	int compare = strcmp(root->text, text);
	
	if(compare == 0) {
		return root;
	}
	else if(compare < 0) {
		return find(root->left, text);
	}
	else {
		return find(root->right, text);
	}
}

void BinarySearchTree::destroy(Keyword* root) {
	if(root == NULL) return;
	
	destroy(root->left);
	destroy(root->right);
	
	free(root);
}