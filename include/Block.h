#ifndef BLOCK_H
#define BLOCK_H

template <class T> class Queue;
class Node;

class Block {
	public:
		Block();
		~Block();
		void addNode(Node* node);
		Node* popNode();
	private:
		Queue<Node*> *nodeList;
};

#endif