#include <stdio.h>
#include <stdlib.h>

#include "../errors/errors.h"
#include "matrix.h"

MatrixOutcome createMatrix(const uint64_t rows, const uint64_t columns) {
	MatrixOutcome resultMatrix;

	resultMatrix.errorCode = NONE_ERROR;

	resultMatrix.matrix = malloc(sizeof(Matrix));

	if (resultMatrix.matrix == NULL) {
		resultMatrix.errorCode = MATRIX_ALLOCATION_ERROR;
	} else {
		resultMatrix.matrix->rows = rows;
		resultMatrix.matrix->cols = columns;
		resultMatrix.matrix->data = malloc(sizeof(MATRIX_TYPE *) * rows);

		if (resultMatrix.matrix->data == NULL) {
			resultMatrix.errorCode = DATA_ALLOCATION_ERROR;
		}

		for (size_t rowsIter = 0;
			 rowsIter < rows && resultMatrix.errorCode == NONE_ERROR;
			 rowsIter++) {
			resultMatrix.matrix->data[rowsIter] =
				malloc(sizeof(MATRIX_TYPE) * columns);
			if (resultMatrix.matrix->data[rowsIter] == NULL) {
				resultMatrix.errorCode = DATA_ALLOCATION_ERROR;
			}
		}
	}

	if (resultMatrix.errorCode != NONE_ERROR) {
		freeMatrixOutcome(&resultMatrix);
	}

	return resultMatrix;
}

void destroyMatrix(Matrix **matrix) {
	if (*matrix != NULL) {
		for (size_t rowsIter = 0; rowsIter < (*matrix)->rows; rowsIter++) {
			free((*matrix)->data[rowsIter]);
		}

		(*matrix)->cols = 0;
		(*matrix)->rows = 0;
		free((*matrix)->data);
		(*matrix)->data = NULL;
		matrix = NULL;
	}
}

void freeMatrixOutcome(MatrixOutcome *resultMatrix) {
	destroyMatrix(&resultMatrix->matrix);
	resultMatrix->errorCode = NONE_ERROR;
}