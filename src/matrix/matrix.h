#ifndef MATRIX_H
#define MATRIX_H

#include <stdint.h>

#include "../../include/config.h"
#include "../errors/errors.h"

typedef struct {
	uint64_t rows;
	uint64_t cols;
	MATRIX_TYPE** data;
} Matrix;

typedef struct {
	Matrix* matrix;
	MatrixErrorCode errorCode;
} ResultMatrix;

ResultMatrix createMatrix(uint64_t rows, uint64_t columns);
void destroyMatrix(Matrix** matrix);
void freeResultMatrix(ResultMatrix* resultMatrix);

#endif