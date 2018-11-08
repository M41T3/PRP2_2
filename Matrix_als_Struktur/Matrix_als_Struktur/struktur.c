#include <stdio.h>

typedef struct {
	int** werte;
	unsigned short zeilen;
	unsigned short spalten;
} matrix_t;

matrix_t* matrix_erstellen(unsigned short zeilen, unsigned short spalten);
void matrix_eingeben(matrix_t *matrix);
void matrix_ausgeben(matrix_t *matrix);
void matrix_freigeben(matrix_t *matrix);

int main(void) {

	matrix_t* matrix;
	unsigned short zeilen, spalten;

	printf("Wieviele Zeilen soll die Matrix enthalten? ");
	scanf_s(" %hu", &zeilen);
	printf("Wieviele Spalten soll die Matrix enthalten? ");
	scanf_s(" %hu", &spalten);

	matrix = matrix_erstellen(zeilen, spalten);

	matrix_eingeben(matrix);
	matrix_ausgeben(matrix);
	matrix_freigeben(matrix);


	system("PAUSE");
	return 0;
}

matrix_t* matrix_erstellen(unsigned short zeilen, unsigned short spalten) {

	matrix_t* pmatrix;

	pmatrix = (matrix_t*)malloc(sizeof(matrix_t));	// Speicher für Struck in heap, damit er nach beendigung des blocks noch vorhanden ist

	pmatrix->zeilen = zeilen;
	pmatrix->spalten = spalten;

	pmatrix->werte = (int**)malloc(zeilen * sizeof(int*));	// Speicher für werte matrix
	if (pmatrix->werte == NULL) {
		free(pmatrix->werte);
		return 1;
	}

	for (int i = 0; i < zeilen; i++) {
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

void matrix_eingeben(matrix_t *matrix) {

	printf("Bitte die Matrixeintraege Zeile fuer Zeile eingeben:\n");

	for (int z = 0; z < matrix->zeilen; z++) {
		for (int s = 0; s < matrix->spalten; s++) {
			scanf_s(" %d", &(matrix->werte[s][z]));
		}
	}
}

void matrix_ausgeben(matrix_t *matrix) {

	printf("Inhalt dieser Matrix:\n");

	for (int z = 0; z < matrix->zeilen; z++){
		for (int s = 0; s < matrix->spalten; s++) {
			printf("%d\t", matrix->werte[z][s]);
		}
		printf("\n");
	}
}

void matrix_freigeben(matrix_t* matrix) {
	for (int j = 0; j < matrix->zeilen; j++) {
		free(matrix->werte[j]);
	}
	free(matrix->werte);
}