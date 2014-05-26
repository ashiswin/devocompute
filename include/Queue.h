/* Copyright (C) 2014 Isaac Ashwin Ravindran
 * 
 * Queue.h
 * Implentation of a templated Queue based on a linked-list.
 * Basic functions of a queue are implemented
 */

#ifndef QUEUE_H
#define QUEUE_H
#include <stdio.h>
#include <stdlib.h>

template <class T> class Queue {
	private:
		struct QueueObject {
			T item;
			QueueObject* next;
		};

		QueueObject *first;
		QueueObject *last;
		int size;
		int maxSize;
		
	public:
		Queue(int size);
		bool push(T item);
		T pop();
		T at(int index);
		int getSize();
		int getMaxSize();
};

// Construct new queue object
template <class T> Queue<T>::Queue(int size) {
	this->maxSize = size;
	this->size = 0;
	this->first = NULL;
	this->last = this->first;
}

// Push object of type T to back of queue
template <class T> bool Queue<T>::push(T item) {
	if(size == maxSize) {
		return false;
	}
	
	QueueObject* newItem = (QueueObject*) malloc(sizeof(QueueObject));
	newItem->item = item;
	newItem->next = NULL;
	
	if(first == NULL) {
		first = newItem;
		last = newItem;
	}
	else {
		last->next = newItem;
		last = newItem;
	}
	
	size++;
	
	return true;
}

// Pop object of type T off front of queue
template <class T> T Queue<T>::pop() {
	QueueObject* oldFirst = first;
	T firstItem = first->item;
	first = first->next;
	
	free(oldFirst);
	
	size--;
	
	return firstItem;
}

// Iterate through and return object at index provided
template <class T> T Queue<T>::at(int index) {
	if(index >= size) {
		printf("Queue limit exceeded, requested %d when size was %d!\n", index, size);
	}
	
	QueueObject* currentObject = first;
	
	for(int i = 0; i < index; i++) {
		currentObject = currentObject->next;
	}
	
	return currentObject->item;
}

// Get current size of queue
template <class T> int Queue<T>::getSize() {
	return size;
}

// Get maximum size of queue
template <class T> int Queue<T>::getMaxSize() {
	return maxSize;
}

#endif