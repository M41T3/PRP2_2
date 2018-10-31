/*
PRP2-2 Aufgabe 2.2
Name: Malte Müller
Date: 31.10.2018
*/

#include <stdio.h>

#define N 3

int allocate_2d(float **temperature, int n_days);
int allocate_1d(float *humidity, int n_days);

int main(void) {

	int n_days;

	printf("F%cr wieviele Tage sollen die Messdaten erfasst werden? ", 129);
	scanf_s(" %d", &n_days);

	float **temperature = NULL;
	float *humidity = NULL;

	allocate_2d(temperature, n_days);
	allocate_1d(humidity, n_days);

	// Release storage at the end:
	for (int i = 0; i < N; i++) {	// Free storage (Y-Values)
		free(temperature[i]);
	}
	free(temperature);	// Free storage (X-Values)

	system("PAUSE");
	return 0;
}

int allocate_2d(float **temperature, int n_days) {
	temperature = (float**)malloc(n_days * sizeof(float*));

	if (temperature == NULL) {	// Exit programm if allocation failed 
		printf("Allocation failed.\n");

		return 1;
	}

	for (int i = 0; i < n_days; i++) {
		temperature[i] = (float*)malloc(N * sizeof(float));

		if (temperature[i] == NULL) {
			printf("Allocation failed.\n");

			for (int j = i - 1; j >= 0; j--) {	// Free storage (Y-Values)
				free(temperature[j]);
			}
			free(temperature);	// Free storage (X-Values)
			return 1;
		}
	}
}

int allocate_1d(float *humidity, int n_days) {
	humidity = (float*)malloc(n_days * sizeof(float));

	if (humidity == NULL) {	// Exit programm if allocation failed 
		printf("Allocation failed.\n");

		return 1;
	}
}