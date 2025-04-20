#include "../messages.h"

const MatrixErrorMessage EN_MESSAGES[] = {
    [NONE_ERROR] = {NONE_ERROR, "Operation completed successfully." },
    [MATRIX_ALLOCATION_ERROR] = {MATRIX_ALLOCATION_ERROR, "Failed to allocate memory for matrix."},
    [DATA_ALLOCATION_ERROR] = {DATA_ALLOCATION_ERROR, "Failed to allocate memory for matrix elements."},
    [INVALID_SIZE_ERROR] = {INVALID_SIZE_ERROR, "Invalid matrix size."},
    [NULL_POINTER_ERROR] = {NULL_POINTER_ERROR, "Pointer error. A null pointer has been passed."},
    [SIZE_MISMATCH_ERROR] = {SIZE_MISMATCH_ERROR, "Error in the disobedience of the size of the matrices."},
    [NOT_SQUARE_MATRIX_ERROR] = {NOT_SQUARE_MATRIX_ERROR, "Matrix is not square."},
    [EXCLUSION_ERROR] = {EXCLUSION_ERROR, "Error excluding row or column."},
    [PREPARE_BUFFER_ERROR] = {PREPARE_BUFFER_ERROR, "Failed to prepare string representation."},
    [FILE_OPEN_ERROR] = {FILE_OPEN_ERROR, "Failed to open file."},
    [FILE_READ_ERROR] = {FILE_READ_ERROR, "Failed to read file."},
	[UNKNOWN_ERROR] = {UNKNOWN_ERROR, "Unknown error."},
};