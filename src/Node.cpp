#include "Node.h"

Node* Node::getNext() {
	return next;
}

void Node::setNext(Node* next) {
	this->next = next;
}