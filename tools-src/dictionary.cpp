#include <stdio.h>
#include <stdlib.h>
#include "TokenTypes.h"

int main() {
	int* characters;
	characters = (int*) malloc(sizeof(int) * 256);
	
	for(int i = 0; i < 256; i++) {
		characters[i] = INVALID;
	}
	
	FILE* indic = fopen("dictionary.txt", "r");
	if(indic != NULL) {
		for(int i = 0; i < 256; i++) {
			fscanf(indic, "%d ", &characters[i]);
		}
		fclose(indic);
	}
	
	while(1) {
		for(int i = 0; i < 256; i++) {
			printf("%d %d\n", i, characters[i]);
		}
		
		int c, e;
		
		scanf("%d %d", &c, &e);
		
		if(c > 255 || c < 0) {
			break;
		}
		
		characters[c] = e;
	}
	
	FILE *dictionary = fopen("dictionary.txt", "w");
	
	for(int i = 0; i < 256; i++) {
		fprintf(dictionary, "%d\n", characters[i]);
	}
	
	fclose(dictionary);
	return 0;
}