/*
PRP2-2 Aufgabe 2.1
Name: Malte Müller
Date: 23.10.2018
*/

#include <stdio.h>
#include <math.h>

// Range of system:
#define X_0 -2.1
#define X_1 0.6
#define Y_0 -1.2
#define Y_1 1.2
// Step size:
#define X_STEP 0.02
#define Y_STEP 0.02
// Interations:
#define ITER 1000

int main(void) {
	
	int n_x = (int)((X_1 - X_0) / X_STEP) +1;
	int n_y = (int)((Y_1 - Y_0) / Y_STEP) +1;
	
	float x0, y0, x1, y1, abs;	// Start values


	float** coordinates;	// Initialize 2d array 
	coordinates = (float**) malloc(n_x * sizeof(float*));	// Allocate dynamic storage (X-Value), type = int* (address)
	
	
	if (coordinates == NULL) {	// Exit programm if allocation failed 
		printf("Allocation failed.\n");

		return 1;
	}
	

	for (int i = 0; i < n_x; i++) {
		coordinates[i] = (float*) malloc(n_y * sizeof(float));	// Allocate dynamic storage (Y-Value) [ERROR] ?
		
	
		if (coordinates[i] == NULL) {
			printf("Allocation failed.\n");

			for (int j = i - 1; j >= 0; j--) {	// Free storage (Y-Values)
				free(coordinates[j]);	
			}
			free(coordinates);	// Free storage (X-Values)
			return 1;
		}
		
	}

	
	for (int i = 0; i < n_x; i++) {
		for (int j = 0; j < n_y; j++) {
			x0 = 0;
			y0 = 0;
			for (int k = 0; k < ITER; k++) {
				//printf("temp: %f\n", X_0 + i * X_STEP);	//[DEBUG]
				x1 = pow(x0,2) - pow(y0,2) + X_0 + i * X_STEP;
				y1 =  2 * x0 * y0 + Y_0 + j * Y_STEP;
				x0 = x1;
				y0 = y1;
				abs = sqrt(pow(x0, 2) + pow(y0, 2));
				if (abs > 2) break;
			}
			coordinates[i][j] = abs;	// Calculate abs value
		}
	}
	
	for (int i = 0; i < n_y; i++) {		//[TODO] swoap x and y coordinates
		for (int j = 0; j < n_x; j++) {
			if (coordinates[j][i] < 2) printf("9 ");	// If ads divergates
			else if(coordinates[j][i] < 2.5) printf("8 ");
			else if (coordinates[j][i] < 3) printf("7 ");
			else if (coordinates[j][i] < 3.5) printf("6 ");
			else if (coordinates[j][i] < 4) printf("5 ");
			else if (coordinates[j][i] < 4.5) printf("4 ");
			else if (coordinates[j][i] < 5) printf("3 ");
			else if (coordinates[j][i] < 5.5) printf("2 ");
			else if (coordinates[j][i] < 6) printf("1 ");
			else printf("0 ");
		}
		printf("\n");
	}

	// Release storage at the end:
	for (int i = 0; i < n_x; i++) {	// Free storage (Y-Values)
		free(coordinates[i]);
	}
	free(coordinates);	// Free storage (X-Values)

	system("PAUSE");

	return 0;
}
