#include <stdio.h>

#include "../include/config.h"
#include "matrix/matrix.h"
#include "output/output.h"

int main() {
	MatrixErrorCode errorCode = NONE_ERROR;

	MatrixOutcome A = loadMatrixFromFile(INPUT_FILE_DIR "matrix_a.txt");
	MatrixOutcome B = loadMatrixFromFile(INPUT_FILE_DIR "matrix_b.txt");
	MatrixOutcome C = loadMatrixFromFile(INPUT_FILE_DIR "matrix_c.txt");
	MatrixOutcome D = loadMatrixFromFile(INPUT_FILE_DIR "matrix_d.txt");

	MatrixOutcome transposedA = transposeMatrix(A);
	MatrixOutcome result = multiplyMatrices(B, C);
	result = getSumOrDiffMatrices(transposedA, result, false);
	result = getSumOrDiffMatrices(result, D, true);

	if (result.errorCode == NONE_ERROR) {
		printMatrix(result, outputToFile, OUTPUT_FILE_DIR "result.txt");
	} else {
		printf("%s\n", getErrorMessage(result.errorCode));
		errorCode = result.errorCode;
	}

	freeMatrixOutcome(&A);
	freeMatrixOutcome(&B);
	freeMatrixOutcome(&C);
	freeMatrixOutcome(&D);
	freeMatrixOutcome(&transposedA);
	freeMatrixOutcome(&result);

	return errorCode;
}