/*
PRP2-2 Aufgabe 2.1
Name: Malte Müller
Date: 26.10.2018
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
#define ITER 300
// Characters:
#define DEV 32
#define CONV 254 

struct coordinate {
	double x_value;
	double y_value;
	double abs;
	int div_num;
};


int main(void) {
	
	int n_x = (int)((X_1 - X_0) / X_STEP) +1;
	int n_y = (int)((Y_1 - Y_0) / Y_STEP) +1;
	
	float x0, y0, x1, y1, abs;	// Start values


	struct coordinate **coordinates; // Initialize 2d struct array 
	coordinates = (struct coordinate**) malloc(n_x * sizeof(struct coordinate*));	// Allocate dynamic storage (X-Value), type = int* (address)
	
	
	if (coordinates == NULL) {	// Exit programm if allocation failed 
		printf("Allocation failed.\n");

		return 1;
	}
	

	for (int i = 0; i < n_x; i++) {
		coordinates[i] = (struct coordinate*) malloc(n_y * sizeof(struct coordinate));	// Allocate dynamic storage (Y-Value) [ERROR] ?
		
	
		if (coordinates[i] == NULL) {
			printf("Allocation failed.\n");

			for (int j = i - 1; j >= 0; j--) {	// Free storage (Y-Values)
				free(coordinates[j]);	
			}
			free(coordinates);	// Free storage (X-Values)
			return 1;
		}
		
	}

	// Calculate every single value.
	for (int i = 0; i < n_x; i++) {
		for (int j = 0; j < n_y; j++) {
			x0 = 0;
			y0 = 0;
			for (int k = 0; k < ITER; k++) {
				x1 = pow(x0,2) - pow(y0,2) + X_0 + i * X_STEP;
				y1 =  2 * x0 * y0 + Y_0 + j * Y_STEP;
				x0 = x1;
				y0 = y1;
				abs = sqrt(pow(x0, 2) + pow(y0, 2));
				if (abs > 2) { 
					coordinates[i][j].div_num = k;
					break; 
				}
				coordinates[i][j].div_num = -1;	// divergence
			}
			coordinates[i][j].x_value = x0;
			coordinates[i][j].y_value = y0;
			coordinates[i][j].abs = abs;
			coordinates[i][j].abs = abs;	// Calculate abs value
		}
	}
	
	for (int i = 0; i < n_y; i++) {		//[TODO] swoap x and y coordinates
		for (int j = 0; j < n_x; j++) {
			if (coordinates[j][i].abs >= 2) printf("%c ", DEV);	// If ads divergates
			else printf("%c ", CONV);
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
