/*
PRP2-2 Aufgabe 2.2
Name: Malte Müller, Fabian Liebold
Date: 09.11.2018
*/

#include <stdio.h>

#define N 3	// Number of temperature measurements per day

// Prototypes:
float **allocate_2d(int n_days);
float  *allocate_1d(int n_days);
void scan_data(float **temperature, float *air_pressure, int from, int to);
float mean_temperature(float **temperature, int n_days);
float mean_air_pressure(float *air_pressure, int n_days);
float **add_temperature(float **temperature, int new_size, int new_days);
float *add_air_pressure(float *air_pressure, int new_size);

int main(void) {

	int n_days;	// Number of days
	int new_days = 0;	// Number of new days
	int from = 0;

	printf("F%cr wieviele Tage sollen die Messdaten erfasst werden? ", 129);
	scanf_s(" %d", &n_days);

	float **temperature = NULL;	// Declare temperature- and air-pressure-pointers
	float *air_pressure = NULL;

	temperature = allocate_2d(n_days);	// Allocate memory to temperature pointer
	if (temperature == NULL) {
		printf("Allocation failed!\n");	// Print error message to console, if allocation failed and exit programm
		return 1;
	}
	
	air_pressure = allocate_1d(n_days);	// Allocate memory to air-pressure pointer
	if (air_pressure == NULL) {
		printf("Allocation failed!\n");	// Print error message to console, if allocation failed and exit programm
		return 1;
	}
	
	char rep_flag = 'j';
	int input = 0;

	do {	// Loops, when measurement-data gets enhanced

		scan_data(temperature, air_pressure, from, n_days);	// Read in measurement-data

		// Calculate mean-values:
		printf("\n--> Durchschnittswert der Temperaturen: %.2f\n", mean_temperature(temperature, n_days));
		printf("\n--> Durchschnittswert der Luftdruckwerte: %.2f\n", mean_air_pressure(air_pressure, n_days));
		
		do {

			printf("Sollen weitere Messwerte eingegeben werden [j/n]? ");	// Ask to add measurement-data
			scanf_s(" %c", &rep_flag);						

			fseek(stdin, 0, SEEK_END);	// clear buffer

			if (rep_flag != 'j' && rep_flag != 'J'&& rep_flag != 'n'&& rep_flag != 'N'){	// If the user typed in the wrong character 
				printf("Bitte nur 'J' oder 'N' eingeben!\n");
			}

		} while (rep_flag != 'j' && rep_flag != 'J' && rep_flag != 'n' && rep_flag != 'N');

		if (rep_flag == 'j' || rep_flag == 'J') {	// If user typed in 'j'
			// realloc
			printf("Wieviele neue Tage? \n");
			scanf_s(" %d", &new_days);	// Ask for number of days, which the user wants to add 

			from = n_days;
			n_days = n_days + new_days;	// Total days

			air_pressure = add_air_pressure(air_pressure, n_days);	// Reallocate memory
			if (air_pressure == NULL) {
				printf("Allocation failed: air_pressure == NULL!\n");	// Send message and exit programm if realloc fails

				return 1;
			}
			
			temperature = add_temperature(temperature, n_days, new_days); // Reallocate memory
			if (temperature == NULL) {
				printf("Allocation failed: temperature == NULL!\n");	// Send message and exit programm if realloc fails
			
				return 1;
			}
			
		}

	} while (rep_flag == 'j' || rep_flag == 'J');	// Repeat prozedure until user don't want to add any data

	// Release storage at the end:
	for (int i = 0; i < n_days; i++) {	// Free storage (Y-Values)
		free(temperature[i]);
	}

	free(temperature);	// Free storage (X-Values)
	free(air_pressure);

	system("PAUSE");
	return 0;
}

/**************************************************************************************************
Function allocates memory to a pointer.
Parameters:
	int days - size of second dimension. 
Returns:
	float matrix - pointer of matrix.
*/
float **allocate_2d(int n_days) {
	
	float **matrix = NULL;
	
	matrix = (float**)malloc(n_days * sizeof(float*));	// Allocate memory (x-values: number of days) for pointer

	if (matrix == NULL) {	// Exit programm if allocation failed.

		return NULL;
	}

	for (int i = 0; i < n_days; i++) {
		matrix[i] = (float*)malloc(N * sizeof(float));	// Allocate memory for every day (y-values: N) for float-values

		if (matrix[i] == NULL) {

			for (int j = i - 1; j >= 0; j--) {	// Free storage (Y-Values)
				free(matrix[j]);
			}
			free(matrix);	// Free storage (X-Values)
			return NULL;
		}
	}

	return matrix;
}

/**************************************************************************************************
Function allocates memory to a pointer.
Parameters:
	int days - size of dimension.
Returns:
	float matrix - pointer of array.
*/
float *allocate_1d(int n_days) {
	
	float *array = NULL;

	array = (float*)malloc(n_days * sizeof(float)); // Allocate memory (x-values: number of days) for float-values

	if (array == NULL) {	// Exit programm if allocation failed 
		return NULL;
	}

	return array;
}

/**************************************************************************************************
Reads in measurement data from console.
Parameters:
	float **temperature
	float *air_pressure
	int n_days
Returns:
	void.
*/
void scan_data(float **temperature, float *air_pressure, int from, int to) {

	printf("* Einlesen der Messwerte f%cr die einzelchen Tage *\n", 129);

	for (int i = from; i < to; i++) {	// Read in temperature-values: [i] = day, [j] = measurement per day
		printf("Tag %d:\n", i+1);
		for (int j = 0; j < N; j++) {
			printf("\tTemperatur %d: ", j+1);
			scanf_s(" %f", &temperature[i][j]);
		}
		printf("\tLuftdruck: ");
		scanf_s(" %f", &air_pressure[i]);	// Read in air-pressure-values
	}
}

/**************************************************************************************************
Calculates the mean of the temperature values.
Parameters:
	float **temperature
	int n_days
Returns:
	float - mean temperature value.
*/
float mean_temperature(float **temperature, int n_days) {
	float i = 0;
	for (int k = 0; k < n_days; k++) {
		for (int n = 0; n < N; n++) {
			i += temperature[k][n];	// Add up every temperature-value and devide by number of temperature-values
		}
	}
	return i / (N * n_days);
}

/**************************************************************************************************
Calculates the mean of the air pressure values.
Parameters:
	float *air_pressure
	int n_days
Returns:
	float - mean air pressure value.
*/
float mean_air_pressure(float *air_pressure, int n_days) {
	float i = 0;
	for (int k = 0; k < n_days; k++) {
		i += air_pressure[k];	// Add up every air-pressure-value and devide by number of air-pressure-values
	}
	return i / n_days;
}

/**************************************************************************************************
Reallocate memory of temperature-values.
Parameters:
	float **temperature
	int new_size - number of total days.
	int new_days - number of new days.
*/
float **add_temperature(float **temperature, int new_size, int new_days) {
	
	float **new_temp = (float**)realloc(temperature, new_size * sizeof(float*));	// Reallocate memory
	
	if (new_temp == NULL) {	// Exit programm if allocation failed 
		return NULL;
	}

	for (int i = new_size-new_days; i < new_size; i++) {	// Allocate memory to new days
		new_temp[i] = (float*)malloc(N * sizeof(float));
		
		if (new_temp[i] == NULL) {
			for (int j = i - 1; j >= 0; j--) {	// Free storage (Y-Values)
				free(new_temp[j]);
			}
			free(new_temp);	// Free storage (X-Values)
			return NULL;
		}
	}
	return new_temp;
}

/**************************************************************************************************
Reallocate memory of air-pressure-values.
Parameters:
float *air_pressure
int new_size - number of total days.
*/

float *add_air_pressure(float *air_pressure, int new_size) {
	
	float *new_air_pr = (float*)realloc(air_pressure, new_size * sizeof(float));	// Reallocate memory

	if (new_air_pr == NULL) {	// Exit programm if allocation failed 
		return NULL;
	}
	return new_air_pr;
}