#include <stdlib.h>

#include "matrix.h"


void createMatrix(Matrix **matrix, const int rows, const int columns) {
    *matrix = malloc(sizeof(Matrix));
    (*matrix)->rows = rows;
    (*matrix)->cols = columns;
    (*matrix)->data = malloc(sizeof(MATRIX_TYPE*) * rows);
    for (size_t rowsIter = 0; rowsIter < rows; rowsIter++) {
        (*matrix)->data[rowsIter] = malloc(sizeof(MATRIX_TYPE) * columns);
    }
}

void freeMatrix(Matrix **matrix) {
    for (size_t rowsIter = 0; rowsIter < (*matrix)->rows; rowsIter++) {
        free((*matrix)->data[rowsIter]);
    }

    (*matrix)->cols = 0;
    (*matrix)->rows = 0;
    free((*matrix)->data);
    (*matrix)->data = NULL;
    matrix = NULL;
}