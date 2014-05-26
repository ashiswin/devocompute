#include "PeekReader.h"
#include "Queue.h"

// Construct a PeekReader
PeekReader::PeekReader(FILE* script, int size) {
	// Get pointer to script file
	this->script = script;
	// Prepare new Queue object
	this->buffer = new Queue<char>(size);
	// Clear script file stream for reading
	fflush(script);
	
	// Fill queue with characters from file
	fillBuffer();
}

// Destructor; Delete all relevant objects and close script file
PeekReader::~PeekReader() {
	fclose(script);
	delete buffer;
}

// Look ahead in the queue by i
int PeekReader::peek(int i) {
	return buffer->at(i);
}

// Fill the buffer to its max size
void PeekReader::fillBuffer() {
	int size = buffer->getSize();
	for(int i = 0; i < buffer->getMaxSize() - size; i++) {
		if(feof(script)) break; // If end of file, break from the loop
		int c = fgetc(script);
		
		if(!buffer->push((char) c)) {
			printf("Unable to push new char\n");
		}
	}
}

// Read top character off the queue and remove it from the queue
int PeekReader::read() {
	if(buffer->getSize() == 0) {
		return -1;
	}
	
	int c = buffer->pop();
	fillBuffer();
	
	return c;
}