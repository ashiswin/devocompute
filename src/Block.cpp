#include "Block.h"
#include "Node.h"
#include "Queue.h"
#include <limits.h>

Block::Block() {
	nodeList = new Queue<Node*>(INT_MAX);
}

Block::~Block() {
	delete nodeList;
}

void Block::addNode(Node* node) {
	nodeList->push(node);
}

Node* Block::popNode() {
	return nodeList->pop();
}