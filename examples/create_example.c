#include <stdio.h>
#include "../src/matrix/matrix.h"

int main() {
	MatrixOutcome matrix = createMatrix(4, 4);
	MATRIX_TYPE matrixData[] = {
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10, 11, 12,
		13, 14, 15, 16
	};
	fillMatrix(&matrix, matrixData);
}