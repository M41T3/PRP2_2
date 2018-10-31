/*
PRP2-2 Aufgabe 2.2
Name: Malte Müller
Date: 31.10.2018
*/

#include <stdio.h>

#define N 3

float **allocate_2d(int n_days);
float  *allocate_1d(int n_days);
void scan_data(float **temperature, float *air_pressure, int n_days);
float mean_temperature(float **temperature, int n_days);
float mean_air_pressure(float *air_pressure, int n_days);

int main(void) {

	int n_days;

	printf("F%cr wieviele Tage sollen die Messdaten erfasst werden? ", 129);
	scanf_s(" %d", &n_days);

	float **temperature = NULL;
	float *air_pressure = NULL;

	temperature = allocate_2d(n_days);
	if (temperature == NULL) {
		printf("Allocation failed!\n");
		return 1;
	}
	
	air_pressure = allocate_1d(n_days);
	if (air_pressure == NULL) {
		printf("Allocation failed!\n");
		return 1;
	}
	
	char rep_flag = 'j';

	do {

		scan_data(temperature, air_pressure, n_days);

		// Calc mean:
		printf("\n--> Durchschnittswert der Temperaturen: %.2f\n", mean_temperature(temperature, n_days));
		printf("\n--> Durchschnittswert der Luftdruckwerte: %.2f\n", mean_air_pressure(air_pressure, n_days));

		printf("Sollen weitere Messwerte eingegeben werden [j/n]? ");
		scanf_s(" %c", &rep_flag);

		if (rep_flag == 'j') {
			// realloc
			// ask for new data
		}

	} while (rep_flag == 'j');

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
	
	matrix = (float**)malloc(n_days * sizeof(float*));

	if (matrix == NULL) {	// Exit programm if allocation failed.

		return NULL;
	}

	for (int i = 0; i < n_days; i++) {
		matrix[i] = (float*)malloc(N * sizeof(float));

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

	array = (float*)malloc(n_days * sizeof(float));

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
void scan_data(float **temperature, float *air_pressure, int n_days) {

	printf("* Einlesen der Messwerte f%cr die einzelchen Tage *\n", 129);

	for (int i = 0; i < n_days; i++) {
		printf("Tag %d:\n", i+1);
		for (int j = 0; j < N; j++) {
			printf("\tTemperatur %d: ", j+1);
			scanf_s(" %f", &temperature[i][j]);
		}
		printf("\tLuftdruck: ");
		scanf_s(" %f", &air_pressure[i]);
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
			i += temperature[k][n];
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
		i += air_pressure[k];
	}
	return i / n_days;
}