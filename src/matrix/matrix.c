#include "matrix.h"

#include <stdio.h>
#include <stdlib.h>

#include "../errors/errors.h"

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

void freeMatrixOutcome(MatrixOutcome *matrixOutcome) {
	if (matrixOutcome != NULL) {
		destroyMatrix(&matrixOutcome->matrix);
		matrixOutcome->errorCode = NONE_ERROR;
	}
}

bool isMatricesSizesEqual(const MatrixOutcome A, const MatrixOutcome B) {
	return A.matrix->rows == B.matrix->rows &&
		   A.matrix->cols == B.matrix->cols;
}

MatrixOutcome getSumOrDiffMatrices(const MatrixOutcome A,
								   const MatrixOutcome B, const bool isDiff) {
	MatrixOutcome result = {.matrix = NULL, .errorCode = NONE_ERROR};

	if (A.matrix == NULL || B.matrix == NULL)
		result.errorCode = NULL_POINTER_ERROR;
	else if (!isMatricesSizesEqual(A, B))
		result.errorCode = SIZE_MISMATCH_ERROR;
	else {
		result = createMatrix(A.matrix->rows, A.matrix->cols);
		if (result.errorCode == NONE_ERROR) {
			for (size_t rowsIter = 0; rowsIter < A.matrix->rows; rowsIter++) {
				for (size_t colsIter = 0; colsIter < A.matrix->cols;
					 colsIter++) {
					result.matrix->data[rowsIter][colsIter] =
						A.matrix->data[rowsIter][colsIter] +
						B.matrix->data[rowsIter][colsIter] *
							(1 - 2 * (int8_t)isDiff);
				}
			}
		}
	}

	if (result.errorCode != NONE_ERROR && result.matrix != NULL)
		destroyMatrix(&result.matrix);

	return result;
}

MatrixOutcome getMatrixCopy(const MatrixOutcome source) {
	MatrixOutcome result = {.matrix = NULL, .errorCode = NONE_ERROR};

	if (source.matrix == NULL)
		result.errorCode = NULL_POINTER_ERROR;
	else {
		result = createMatrix(source.matrix->rows, source.matrix->cols);
		if (result.errorCode == NONE_ERROR)
			for (size_t rowsIter = 0; rowsIter < source.matrix->rows;
				 rowsIter++)
				for (size_t colsIter = 0; colsIter < source.matrix->cols;
					 colsIter++)
					result.matrix->data[rowsIter][colsIter] =
						source.matrix->data[rowsIter][colsIter];
	}

	if (result.errorCode != NONE_ERROR && result.matrix != NULL)
		destroyMatrix(&result.matrix);

	return result;
}

MatrixOutcome transposeMatrix(const MatrixOutcome A) {
	MatrixOutcome result = {.matrix = NULL, .errorCode = NONE_ERROR};

	if (A.matrix == NULL) {
		result.errorCode = NULL_POINTER_ERROR;
	} else {
		result = createMatrix(A.matrix->cols, A.matrix->rows);
		if (result.errorCode == NONE_ERROR)
			for (size_t rowsIter = 0; rowsIter < A.matrix->rows; rowsIter++)
				for (size_t colsIter = 0; colsIter < A.matrix->cols;
					 colsIter++)
					result.matrix->data[colsIter][rowsIter] =
						A.matrix->data[rowsIter][colsIter];
	}

	if (result.errorCode != NONE_ERROR && result.matrix != NULL)
		destroyMatrix(&result.matrix);

	return result;
}