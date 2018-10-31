/*
PRP2-2 Aufgabe 2.1
Name: Malte Müller
Date: 31.10.2018
*/

#include <stdio.h>
#include <math.h>

// Range of system:
#define X_0 -2.1
#define X_1 0.6
#define Y_0 -1.2
#define Y_1 1.2
// Step size:
#define X_STEP 0.05
#define Y_STEP 0.05
// Interations:
#define ITER 300
// Characters:
#define DEV 32
#define CONV 254 
// N dimensions:
#define N_X  ((int)((X_1 - X_0) / X_STEP))
#define N_Y  ((int)((Y_1 - Y_0) / Y_STEP))

// Typdefs:
typedef struct {
	double x_value;
	double y_value;
	double abs;
	int div_num;
}coordinate_t;
 
//Prototypes:
void print_mandelbrot(coordinate_t **coordinates);
void print_list(coordinate_t **coordinates);

int main(void) {

	float x0, y0, x1, y1, abs;	// Start values
	char output; 

	coordinate_t **coordinates; // Initialize 2d struct array 
	coordinates = (coordinate_t**) malloc(N_X * sizeof(coordinate_t*));	// Allocate dynamic storage (X-Value), type = int* (address)
	
	if (coordinates == NULL) {	// Exit programm if allocation failed 
		printf("Allocation failed.\n");

		return 1;
	}
	
	for (int i = 0; i < (int)N_X; i++) {
		coordinates[i] = (coordinate_t*) malloc(N_Y * sizeof(coordinate_t));	// Allocate dynamic storage (Y-Value) 
		
	
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
	for (int i = 0; i < N_X; i++) {
		for (int j = 0; j < N_Y; j++) {
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

	printf("Ausgabe? [0] Liste , [1] Mandelbrot - ");
	scanf_s(" %c", &output);
	if(output == '0') print_list(coordinates);
	else if (output == '1') print_mandelbrot(coordinates);
	

	// Release storage at the end:
	for (int i = 0; i < N_X; i++) {	// Free storage (Y-Values)
		free(coordinates[i]);
	}
	free(coordinates);	// Free storage (X-Values)

	system("PAUSE");
	return 0;
}

void print_mandelbrot(coordinate_t **coordinates) {
	for (int i = 0; i < N_Y; i++) {		//[TODO] swoap x and y coordinates
		for (int j = 0; j < N_X; j++) {
			if (coordinates[j][i].abs >= 2) printf("%c ", DEV);	// If ads divergates
			else printf("%c ", CONV);
		}
		printf("\n");
	}
}

void print_list(coordinate_t **coordinates) {
	printf("Untersuchung einer Folge ausgehend vom Punkt:\n");
	float x;
	float y;
	for (int i = 0; i < N_Y; i++) {		//[TODO] swoap x and y coordinates
		y = Y_0 + i * Y_STEP;
		for (int j = 0; j < N_X; j++) {
			x = X_0 + j * X_STEP;

			if(coordinates[j][i].div_num == -1)
				printf("(%.2f, %.2f):\tDie Folge ist konvergent!\n",x,y);
			else printf("(%.2f, %.2f):\tDie Folge ist divergent ab Iteration %d\n", x, y, coordinates[j][i].div_num);
		}
		printf("\n");
	}
}