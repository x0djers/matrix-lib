/**
  @file matrix.h
  @brief Предоставляет функции для работы с матрицами.
*/

#ifndef MATRIX_H
#define MATRIX_H

#include <stdint.h>

#include "../../include/config.h"
#include "../errors/errors.h"


/**
  @struct Matrix
  @brief Структура матрицы.
*/
typedef struct {
	uint64_t rows; ///< Количество строк.
	uint64_t cols; ///< Количеств столбцов.
	MATRIX_TYPE** data; ///< Двумерный массив элементов.
} Matrix;

/**
  @struct MatrixOutcome
  @brief Структура-обёртка для структуры матрицы.

  Хранит в себе код ошибки выполненной операции и
  указатель на структуру самой матрицы.
*/
typedef struct {
	Matrix* matrix; ///< Указатель на структуру матрицы.
	MatrixErrorCode errorCode; ///< Код ошибки.
} MatrixOutcome;


/**
  @brief Создает новую матрицу с заданным размером.
  @param rows Количество строк.
  @param columns Количество столбцов.
  @return Структура MatrixOutcome.
  @note Если в ходе создания произошла ошибка и код ошибки не NONE_ERROR,
  то поле matrix структуры MatrixOutcome будет равно NULL.
 */
MatrixOutcome createMatrix(uint64_t rows, uint64_t columns);

/**
  @brief Освобождает память, выделенную под матрицу.
  @param matrix Указатель на указатель на структуру матрицу.
*/
void destroyMatrix(Matrix** matrix);

/**
  @brief Освобождает ресурсы структуры MatrixResult.
  @param matrixOutcome Указатель на структуру MatrixOutcome.
*/
void freeMatrixOutcome(MatrixOutcome* matrixOutcome);

#endif