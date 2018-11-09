/*
PRP2-2 Aufgabe 2.3
Name: Malte Müller, Fabian Liebold
Date: 09.11.2018
*/

#include <stdio.h>

typedef struct {
	int** werte;
	unsigned short zeilen;
	unsigned short spalten;
} matrix_t;

// Prototypes:
matrix_t* matrix_erstellen(unsigned short zeilen, unsigned short spalten);
void matrix_eingeben(matrix_t *matrix);
void matrix_ausgeben(matrix_t *matrix);
void matrix_freigeben(matrix_t *matrix);

int main(void) {

	matrix_t* matrix;
	unsigned short zeilen, spalten;

	printf("Wieviele Zeilen soll die Matrix enthalten? ");	// Read in amount of rows
	scanf_s(" %hu", &zeilen);
	printf("Wieviele Spalten soll die Matrix enthalten? ");	// Read in amount of columns
	scanf_s(" %hu", &spalten);

	matrix = matrix_erstellen(zeilen, spalten);	// Create matrix

	matrix_eingeben(matrix);	// Read in data to 'werte-matrix'
	matrix_ausgeben(matrix);	// Print matrix to console
	matrix_freigeben(matrix);	// Free allocated memory


	system("PAUSE");
	return 0;
}

/**************************************************************************************************
Function allocates memory for struct and matrix
Parameters:
	unsigned short zeilen - Rows of matrix
	unsigned short spalten - - Columns of matrix
Returns:
	matrix_t* pmatrix - pointer of allocated memory
*/
matrix_t* matrix_erstellen(unsigned short zeilen, unsigned short spalten) {

	matrix_t* pmatrix;

	pmatrix = (matrix_t*)malloc(sizeof(matrix_t));	// Allocate memory for struct in heap

	pmatrix->zeilen = zeilen;	// Save amount of rows and colums in struct
	pmatrix->spalten = spalten;

	pmatrix->werte = (int**)malloc(zeilen * sizeof(int*));	// Allocate memory for matrix (columns) in struct
	if (pmatrix->werte == NULL) {
		free(pmatrix->werte);
		return 1;
	}

	for (int i = 0; i < zeilen; i++) {	// Allocate memory for matrix (rows) in struct
	pmatrix->werte[i] = (int*)malloc(spalten * sizeof(int));

		if (pmatrix->werte[i] == NULL) {
			for (int j = 0; j < i; j++) {
				free(pmatrix->werte[i]);
			}
			free(pmatrix->werte);
			return 1;
		}
	}

	return pmatrix;
}

/**************************************************************************************************
Read in values for matrix.
Parameters:
	matrix_t *matrix - pointer of struct
Returns:
	void.
*/
void matrix_eingeben(matrix_t *matrix) {

	printf("Bitte die Matrixeintraege Zeile fuer Zeile eingeben:\n");

	for (int z = 0; z < matrix->zeilen; z++) {		// Read in values
		for (int s = 0; s < matrix->spalten; s++) {
			scanf_s(" %d", &(matrix->werte[z][s]));
		}
	}
}

/**************************************************************************************************
Print out values for matrix.
Parameters:
	matrix_t *matrix - pointer of struct
Returns:
	void.
*/
void matrix_ausgeben(matrix_t *matrix) {

	printf("Inhalt dieser Matrix:\n");

	for (int z = 0; z < matrix->zeilen; z++){		// Print out values
		for (int s = 0; s < matrix->spalten; s++) {
			printf("%d\t", matrix->werte[z][s]);
		}
		printf("\n");
	}
}

/**************************************************************************************************
Free memory.
Parameters:
	matrix_t *matrix - pointer of struct
Returns:
	void.
*/
void matrix_freigeben(matrix_t* matrix) {
	for (int j = 0; j < matrix->zeilen; j++) {	// Free rows of matrix
		free(matrix->werte[j]);
	}
	free(matrix->werte);	// Free column of matrix
	free(matrix);			// Free struct
}