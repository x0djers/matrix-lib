#include "matrix.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

MatrixOutcome createMatrix(const size_t rows, const size_t columns) {
	MatrixOutcome resultMatrix;

	resultMatrix.errorCode = NONE_ERROR;

	if (rows == 0 || columns == 0) {
		resultMatrix.errorCode = INVALID_SIZE_ERROR;
	} else {
		resultMatrix.matrix = malloc(sizeof(Matrix));

		if (resultMatrix.matrix == NULL) {
			resultMatrix.errorCode = MATRIX_ALLOCATION_ERROR;
		} else {
			resultMatrix.matrix->rows = rows;
			resultMatrix.matrix->cols = columns;
			resultMatrix.matrix->data = malloc(sizeof(MATRIX_TYPE*) * rows);

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
	}
	return resultMatrix;
}

void destroyMatrix(Matrix** matrix) {
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

void freeMatrixOutcome(MatrixOutcome* matrixOutcome) {
	if (matrixOutcome != NULL) {
		destroyMatrix(&matrixOutcome->matrix);
		matrixOutcome->errorCode = NONE_ERROR;
	}
}

MatrixErrorCode getMatrixElement(const MatrixOutcome* A,
							 const size_t row,
							 const size_t column,
							 MATRIX_TYPE* element) {
	MatrixErrorCode errorCode = NONE_ERROR;

	if (!A || A->matrix == NULL || A->matrix->data == NULL) {
		errorCode = NULL_POINTER_ERROR;
	}
	else if (row >= A->matrix->rows || column >= A->matrix->cols) {
		errorCode = INVALID_ELEMENT_ERROR;
	} else if (element == NULL) {
		errorCode = NULL_POINTER_ERROR;
	} else {
		*element = A->matrix->data[row][column];
	}

	return errorCode;
}

MatrixErrorCode setMatrixElement(const MatrixOutcome* A,
								 const size_t row,
								 const size_t column,
								 const MATRIX_TYPE value) {
	MatrixErrorCode errorCode = NONE_ERROR;

	if (!A || A->matrix == NULL || A->matrix->data == NULL) {
		errorCode = NULL_POINTER_ERROR;
	} else if (row >= A->matrix->rows || column >= A->matrix->cols) {
		errorCode = INVALID_ELEMENT_ERROR;
	} else {
		A->matrix->data[row][column] = value;
	}

	return errorCode;
}

void fillMatrix(MatrixOutcome* A, const MATRIX_TYPE* data) {
	if (A->matrix == NULL || A->matrix->data == NULL) {
		A->errorCode = NULL_POINTER_ERROR;
	} else {
		for (size_t row = 0; row < A->matrix->rows; row++) {
			for (size_t col = 0; col < A->matrix->cols; col++) {
				A->matrix->data[row][col] = data[row * A->matrix->cols + col];
			}
		}
	}
}

bool isMatricesSizesEqual(const MatrixOutcome A, const MatrixOutcome B) {
	return A.matrix->rows == B.matrix->rows &&
		   A.matrix->cols == B.matrix->cols;
}

bool isSquareMatrix(const MatrixOutcome A) {
	return A.matrix->rows == A.matrix->cols;
}

bool canMultiplyMatrices(const MatrixOutcome A, const MatrixOutcome B) {
	return A.matrix->cols == B.matrix->rows;
}

MatrixErrorCode canExclude(const size_t count, const size_t currentIndex) {
	return count > currentIndex ? NONE_ERROR : EXCLUSION_ERROR;
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

MatrixOutcome multiplyMatrices(const MatrixOutcome A, const MatrixOutcome B) {
	MatrixOutcome result = {.matrix = NULL, .errorCode = NONE_ERROR};

	if (A.matrix == NULL || B.matrix == NULL)
		result.errorCode = NULL_POINTER_ERROR;
	else if (!canMultiplyMatrices(A, B))
		result.errorCode = SIZE_MISMATCH_ERROR;
	else {
		result = createMatrix(A.matrix->rows, B.matrix->cols);
		if (result.errorCode == NONE_ERROR) {
			for (size_t rowIndex = 0; rowIndex < A.matrix->rows; rowIndex++)
				for (size_t colIndex = 0; colIndex < B.matrix->cols;
					 colIndex++)
					for (size_t resIndex = 0; resIndex < A.matrix->cols;
						 resIndex++)
						result.matrix->data[rowIndex][colIndex] +=
							A.matrix->data[rowIndex][resIndex] *
							B.matrix->data[resIndex][colIndex];
		}
	}

	return result;
}

MatrixOutcome getMinor(const MatrixOutcome A, const size_t excludeRowIndex,
					   const size_t excludeColIndex) {
	MatrixOutcome result = {.matrix = NULL, .errorCode = NONE_ERROR};

	if (A.matrix == NULL)
		result.errorCode = NULL_POINTER_ERROR;
	else {
		result.errorCode = canExclude(A.matrix->rows, excludeRowIndex);
		if (result.errorCode == NONE_ERROR)
			result.errorCode = canExclude(A.matrix->cols, excludeColIndex);
	}

	if (result.errorCode == NONE_ERROR) {
		result = createMatrix(A.matrix->rows - 1, A.matrix->cols - 1);

		if (result.errorCode == NONE_ERROR) {
			MATRIX_TYPE* newMatrixData =
				calloc(result.matrix->cols * result.matrix->rows,
					   sizeof(MATRIX_TYPE));
			size_t insertionIndex = 0;

			for (size_t row = 0; row < A.matrix->rows; row++) {
				for (size_t col = 0; col < A.matrix->cols; col++) {
					if (!(row == excludeRowIndex || col == excludeColIndex)) {
						newMatrixData[insertionIndex++] =
							A.matrix->data[row][col];
					}
				}
			}

			fillMatrix(&result, newMatrixData);
			free(newMatrixData);
		}
	}

	if (result.errorCode != NONE_ERROR && result.matrix != NULL)
		destroyMatrix(&result.matrix);

	return result;
}

MatrixDeterminant calculateDeterminant(const MatrixOutcome A) {
	MatrixDeterminant result = {.determinant = (DETERMINANT_TYPE)0,
								.errorCode = NONE_ERROR};

	if (A.errorCode != NONE_ERROR)
		result.errorCode = A.errorCode;
	else if (A.matrix == NULL || A.matrix->data == NULL)
		result.errorCode = NULL_POINTER_ERROR;
	else if (!isSquareMatrix(A))
		result.errorCode = NOT_SQUARE_MATRIX_ERROR;
	else {
		MATRIX_TYPE** M = A.matrix->data;
		switch (A.matrix->rows) {
			case 1:
				result.determinant = A.matrix->data[0][0];
				break;
			case 2:
				result.determinant = M[0][0] * M[1][1] - M[0][1] * M[1][0];
				break;
			case 3:
				result.determinant =
					M[0][0] * M[1][1] * M[2][2] + M[0][1] * M[1][2] * M[2][0] +
					M[0][2] * M[1][0] * M[2][1] - M[0][2] * M[1][1] * M[2][0] -
					M[0][0] * M[1][2] * M[2][1] - M[0][1] * M[1][0] * M[2][2];
				break;
			default:
				for (size_t colsIter = 0; colsIter < A.matrix->cols &&
										  result.errorCode == NONE_ERROR;
					 colsIter++) {
					MatrixOutcome minorMatrix = getMinor(A, 0, colsIter);
					const int8_t sign = colsIter & 1 ? -1 : 1;
					const MatrixDeterminant minorDet =
						calculateDeterminant(minorMatrix);
					if (minorDet.errorCode != NONE_ERROR)
						result.errorCode = minorDet.errorCode;
					else
						result.determinant += sign * minorDet.determinant;
					freeMatrixOutcome(&minorMatrix);
				}
		}
	}

	return result;
}

char* prepareMatrixBuffer(const MatrixOutcome A) {
	size_t maxBufferSize = BUFFER_SIZE;
	size_t currentBufferSize = 0;

	char* buffer = malloc(maxBufferSize);

	for (size_t rowsIter = 0; rowsIter < A.matrix->rows && buffer;
		 rowsIter++) {
		for (size_t colsIter = 0; colsIter < A.matrix->cols && buffer;
			 colsIter++) {
			const MATRIX_TYPE number = A.matrix->data[rowsIter][colsIter];
			const size_t requiredSize =
				snprintf(NULL, 0, MATRIX_ELEMENT_SPEC, number);
			while (currentBufferSize + requiredSize > maxBufferSize &&
				   buffer) {
				maxBufferSize *= 2;
				buffer = (char*)realloc(buffer, maxBufferSize);
			}
			if (buffer)
				currentBufferSize +=
					snprintf(buffer + currentBufferSize,
							 maxBufferSize - currentBufferSize,
							 MATRIX_ELEMENT_SPEC " ", number);
		}
		if (buffer)
			currentBufferSize +=
				snprintf(buffer + currentBufferSize,
						 maxBufferSize - currentBufferSize, "\n");
	}

	return buffer;
}

MatrixErrorCode printMatrix(const MatrixOutcome A, const outputFunc output,
							void* context) {
	MatrixErrorCode errorCode = NONE_ERROR;

	if (A.errorCode != NONE_ERROR) {
		errorCode = A.errorCode;
	} else if (A.matrix == NULL || A.matrix->data == NULL) {
		errorCode = NULL_POINTER_ERROR;
	}

	if (errorCode == NONE_ERROR) {
		char* buffer = prepareMatrixBuffer(A);
		if (buffer == NULL) {
			errorCode = PREPARE_BUFFER_ERROR;
		} else {
			output(buffer, context);
			free(buffer);
		}
	}

	return errorCode;
}

MatrixOutcome loadMatrixFromFile(const char* fileName) {
	MatrixOutcome result = {.matrix = NULL, .errorCode = NONE_ERROR};

	FILE* file = fopen(fileName, "r");
	if (file == NULL) {
		result.errorCode = FILE_OPEN_ERROR;
	}

	size_t rows = 0, cols = 0;
	char line[BUFFER_SIZE];

	if (result.errorCode == NONE_ERROR) {
		while (fgets(line, sizeof(line), file)) {
			rows++;
			if (rows == 1) {
				const char* token = strtok(line, ELEMENT_DELIMITER);
				while (token != NULL) {
					cols++;
					token = strtok(NULL, ELEMENT_DELIMITER);
				}
			}
		}

		if (rows == 0 || cols == 0) {
			result.errorCode = FILE_READ_ERROR;
		}
	}

	if (result.errorCode == NONE_ERROR) {
		result = createMatrix(rows, cols);
		if (result.errorCode != NONE_ERROR) {
			fclose(file);
		}
	}

	if (result.errorCode == NONE_ERROR) {
		rewind(file);

		size_t rowsIter = 0;
		while (fgets(line, sizeof(line), file) && rowsIter < rows &&
			   result.errorCode == NONE_ERROR) {
			size_t colsIter = 0;
			const char* token = strtok(line, ELEMENT_DELIMITER);

			while (token != NULL && colsIter < cols &&
				   result.errorCode == NONE_ERROR) {
				MATRIX_TYPE value;

				if (sscanf(token, MATRIX_ELEMENT_SPEC, &value) != 1) {
					result.errorCode = FILE_READ_ERROR;
				} else {
					result.matrix->data[rowsIter][colsIter] = value;
					colsIter++;
				}

				token = strtok(NULL, ELEMENT_DELIMITER);
			}

			if (colsIter != cols) {
				result.errorCode = FILE_READ_ERROR;
			}

			rowsIter++;
		}

		if (rowsIter != rows) {
			result.errorCode = FILE_READ_ERROR;
		}

		fclose(file);
	}

	if (result.errorCode != NONE_ERROR) {
		destroyMatrix(&result.matrix);
	}

	return result;
}
