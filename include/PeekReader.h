/* Copyright (C) 2014 Isaac Ashwin Ravindran
 * 
 * PeekReader.cpp
 * The purpose of this is to provide a method to peek into the next characters of a file
 * easily as well as being able to read it off traditionally.
 * Peeking essentially is where the character i spaces from the current character is
 * returned, allowing for easier detection of symbols
 */

#ifndef PEEKREADER_H
#define PEEKREADER_H
#include <stdio.h>
#include <stdlib.h>

template <class T> class Queue;

class PeekReader {
	private:
		Queue<char> *buffer;
		FILE* script;
	public:
		PeekReader(FILE* script, int size);
		~PeekReader();
		int peek(int i);
		void fillBuffer();
		int read();
};
#endif