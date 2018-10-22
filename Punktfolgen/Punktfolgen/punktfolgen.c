/*
PRP2-2 Aufgabe 2.1
Name: Malte Müller
Date: 22.10.2018
*/

#include <stdio.h>

// Range of system:
#define X_0 -2.1
#define X_1 0.6
#define Y_0 -1.2
#define Y_1 1.2
// Step size:
#define X_STEP 0.1
#define Y_STEP 0.1
// Interations:
#define ITER 100

int main(void) {
	
	int** coordinates;	// Initialize 2d array 
	coordinates = (int**) malloc((X_1-X_0)/X_STEP * sizeof(int*));	// Allocate dynamic storage (X-Value), type = int* (address)
	
	
	if (coordinates == NULL) {	// Exit programm if allocation failed 
		printf("Allocation failed.\n");

		return 1;
	}
	

	for (int i = 0; i < ((X_1 - X_0) / X_STEP); i++) {
		coordinates[i] = (int*) malloc(((Y_1 - Y_0) / Y_STEP) * sizeof(int*));	// Allocate dynamic storage (Y-Value) [ERROR] ?
		
	
		if (coordinates[i] == NULL) {
			printf("Allocation failed.\n");

			for (int j = i - 1; j >= 0; j--) {	// Free storage (Y-Values)
				free(coordinates[j]);	
			}
			free(coordinates);	// Free storage (X-Values)
			return 1;
		}
		
	}

	// [DEBUG] Simple test:
	for (int i = 0; i < ((X_1 - X_0) / X_STEP); i++) {
		for (int j = 0; j < ((Y_1 - Y_0) / Y_STEP); j++) {
			coordinates[i][j] = i + j;
		}
	}
	for (int i = 0; i < ((X_1 - X_0) / X_STEP); i++) {
		for (int j = 0; j < ((Y_1 - Y_0) / Y_STEP); j++) {
			printf("%d ", coordinates[i][j]);
		}
		printf("\n");
	}



	// Release storage at the end:
	for (int i = 0; i < ((X_1 - X_0) / X_STEP); i++) {	// Free storage (Y-Values)
		free(coordinates[i]);
	}
	free(coordinates);	// Free storage (X-Values)

	return 0;
}
