/* Copyright (C) 2014 Isaac Ashwin Ravindran
 *
 * dictionary.cpp
 * Generates a dictionary file for the lexer and saves it to dictionary.txt in the same directory.
 * Usage:
 * 	./dictionary.cpp
 *	To edit an entry, type <asciicode> <enumvalue>
 *	To save file type 256 0
 */

#include <stdio.h>
#include <stdlib.h>
#include "TokenTypes.h"

int main() {
	// Prepare array of characters, one for each ascii character
	int* characters;
	characters = (int*) malloc(sizeof(int) * 256);
	
	// Set all characters to mean invalid token
	for(int i = 0; i < 256; i++) {
		characters[i] = INVALID;
	}
	
	// Read in from dictionary to get currently saved settings
	FILE* indic = fopen("dictionary.txt", "r");
	if(indic != NULL) {
		for(int i = 0; i < 256; i++) {
			fscanf(indic, "%d ", &characters[i]);
		}
		fclose(indic);
	}
	
	while(1) {
		// Print table
		for(int i = 0; i < 256; i++) {
			printf("%d %d\n", i, characters[i]);
		}
		
		// Scan input in format specified above
		int c, e;
		
		scanf("%d %d", &c, &e);
		
		// Check for save command
		if(c > 255 || c < 0) {
			break;
		}
		
		// Else, write enum value to character slot
		characters[c] = e;
	}
	
	// Write dictionary to file
	FILE *dictionary = fopen("dictionary.txt", "w");
	
	for(int i = 0; i < 256; i++) {
		fprintf(dictionary, "%d\n", characters[i]);
	}
	
	fclose(dictionary);
	return 0;
}