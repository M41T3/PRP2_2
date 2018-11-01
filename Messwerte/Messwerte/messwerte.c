/*
PRP2-2 Aufgabe 2.2
Name: Malte Müller
Date: 31.10.2018
*/

#include <stdio.h>

#define N 3

float **allocate_2d(int n_days);
float  *allocate_1d(int n_days);
void scan_data(float **temperature, float *air_pressure, int from, int to);
float mean_temperature(float **temperature, int n_days);
float mean_air_pressure(float *air_pressure, int n_days);
float **add_temperature(float **temperature, int new_size);
float *add_air_pressure(float *air_pressure, int new_size);

int main(void) {

	int n_days;
	int new_days = 0;
	int from = 0;

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

		scan_data(temperature, air_pressure, from, n_days);

		//[DEBUG]vvvvvvvv
		printf("\n[DEBUG] Print out Temperature-2dArray:\n\n");
		for (int i = 0; i < n_days; i++) {
			for (int j = 0; j < N; j++) {
				printf("%f ", temperature[i][j]);
			}
			printf("\n");
		}

		printf("\n[DEBUG] Print out Pressure-1dArray:\n\n");
		for (int i = 0; i < n_days; i++) {
			printf("%f ", air_pressure[i]);
		}
		printf("\n");
		//^^^^^^^^

		// Calc mean:
		printf("\n--> Durchschnittswert der Temperaturen: %.2f\n", mean_temperature(temperature, n_days));
		printf("\n--> Durchschnittswert der Luftdruckwerte: %.2f\n", mean_air_pressure(air_pressure, n_days));

		printf("Sollen weitere Messwerte eingegeben werden [j/n]? ");
		scanf_s(" %c", &rep_flag);

		if (rep_flag == 'j') {
			// realloc:
			printf("Wieviele neue Tage? \n");
			scanf_s(" %d", &new_days);

			from = n_days;
			n_days = n_days + new_days;

			air_pressure = add_air_pressure(air_pressure, n_days);
			if (air_pressure == NULL) {
				printf("Allocation failed: air_pressure == NULL!\n");

				return 1;
			}
			
			temperature = add_temperature(temperature, n_days);
			if (temperature == NULL) {
				printf("Allocation failed: temperature == NULL!\n");
			
				return 1;
			}
			
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
void scan_data(float **temperature, float *air_pressure, int from, int to) {

	printf("* Einlesen der Messwerte f%cr die einzelchen Tage *\n", 129);

	for (int i = from; i < to; i++) {
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

/**************************************************************************************************
temp Realloc-fnc.
*/
float **add_temperature(float **temperature, int new_size) {
	
	float **new_temp = (float**)realloc(temperature, new_size * sizeof(float*));
	
	if (new_temp == NULL) {	// Exit programm if allocation failed 
		return NULL;
	}

	for (int i = 0; i < new_size; i++) {
		new_temp[i] = (float*)malloc(N * sizeof(float));
		
		printf("%d\n", i); // [DEBUG]

		if (new_temp[i] == NULL) {
			printf("fail at %d\n", i); // [DEBUG]
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
air Realloc-fnc.
*/

float *add_air_pressure(float *air_pressure, int new_size) {
	float *new_air_pr = (float*)realloc(air_pressure, new_size);

	if (new_air_pr == NULL) {	// Exit programm if allocation failed 
		return NULL;
	}

	return new_air_pr;
}