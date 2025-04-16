#ifndef ERRORS_H
#define ERRORS_H

typedef enum {
	NONE_ERROR,
	MATRIX_ALLOCATION_ERROR,
	DATA_ALLOCATION_ERROR,
	INVALID_FREE_ERROR,
	INVALID_SIZE_ERROR,
	NULL_POINTER_ERROR,
	SIZE_MISMATCH_ERROR,
	NOT_SQUARE_MATRIX_ERROR,
	EXCLUSION_ERROR,
} MatrixErrorCode;

#endif
