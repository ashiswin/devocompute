#ifndef NODE_H
#define NODE_H
#include <stdio.h>

class Node {
	public:
		virtual void printNode(FILE* file) = 0;
		Node* getNext();
		void setNext(Node* next);
	private:
		Node* next;
};

#endif