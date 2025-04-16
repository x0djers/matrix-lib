/**
  @file matrix.h
  @brief Предоставляет функции для работы с матрицами.
*/

#ifndef MATRIX_H
#define MATRIX_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "../../include/config.h"
#include "../errors/errors.h"

/**
  @struct Matrix
  @brief Структура матрицы.
*/
typedef struct {
	uint64_t rows;		 ///< Количество строк.
	uint64_t cols;		 ///< Количеств столбцов.
	MATRIX_TYPE** data;	 ///< Двумерный массив элементов.
} Matrix;

/**
  @struct MatrixOutcome
  @brief Структура-обёртка для структуры матрицы.

  Хранит в себе код ошибки выполненной операции и
  указатель на структуру самой матрицы.
*/
typedef struct {
	Matrix* matrix;				///< Указатель на структуру матрицы.
	MatrixErrorCode errorCode;	///< Код ошибки.
} MatrixOutcome;

/**
  @struct MatrixDeterminant
  @brief Структура, хранящая значение детерминанта и код ошибки.
*/
typedef struct {
	DETERMINANT_TYPE determinant;  ///< Значение детерминанта.
	MatrixErrorCode errorCode;	   ///< Код ошибки.
} MatrixDeterminant;

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
  @brief Освобождает ресурсы структуры MatrixOutcome.
  @param matrixOutcome Указатель на структуру MatrixOutcome.
*/
void freeMatrixOutcome(MatrixOutcome* matrixOutcome);

/**
  @brief Заполняет матрицу данными из массива.
  @param A Указатель на структуру MatrixOutcome.
  @param data Указатель на массив данных.
  @note Размер массива должен соответствовать размерам матрицы.
 */
void fillMatrix(MatrixOutcome* A, const MATRIX_TYPE* data);

/**
  @brief Проверяет соответствие размеров матриц.
  @param A Первая матрица.
  @param B Вторая матрица.
  @return True если размеры совпадают, иначе False.
*/
bool isMatricesSizesEqual(MatrixOutcome A, MatrixOutcome B);

/**
  @brief Проверяет, является ли матрица квадратной.
  @param A Матрица для проверки.
  @return True если матрица является квадратной, иначе false.
*/
bool isSquareMatrix(MatrixOutcome A);

/**
  @brief Проверяет возможность исключения строки/столбца.
  @param count Общее количество строк/столбцов.
  @param currentIndex Индекс для исключения.
  @return Код ошибки MatrixErrorCode.
*/
MatrixErrorCode canExclude(size_t count, size_t currentIndex);

/**
  @brief Вычисляет сумму или разность матриц.
  @param A Первая матрица.
  @param B Вторая матрица.
  @param isDiff Флаг вычисления разности (true - разность, false - сумма).
  @return Структура MatrixOutcome.
  @note Если в ходе вычислений произошла ошибка и код ошибки не NONE_ERROR,
		то поле matrix структуры MatrixOutcome будет равно NULL.
*/
MatrixOutcome getSumOrDiffMatrices(MatrixOutcome A, MatrixOutcome B,
								   bool isDiff);

/**
  @brief Создает копию матрицы.
  @param source Исходная матрица для копирования.
  @return Структура MatrixOutcome.
  @note Если в ходе копирования произошла ошибка и код ошибки не NONE_ERROR,
	то поле matrix структуры MatrixOutcome будет равно NULL.
*/
MatrixOutcome getMatrixCopy(MatrixOutcome source);

/**
  @brief Транспонирует матрицу.
  @param A Исходная матрица.
  @return Структура MatrixOutcome.
  @note Если в ходе транспонирования произошла ошибка и код ошибки не
  NONE_ERROR, то поле matrix структуры MatrixOutcome будет равно NULL.
*/
MatrixOutcome transposeMatrix(MatrixOutcome A);

/**
  @brief Вычисляет произведение матриц.
  @param A Первая матрица.
  @param B Вторая матрица.
  @return Структура MatrixOutcome.
  @note Если в ходе умножения произошла ошибка и код ошибки не
  NONE_ERROR, то поле matrix структуры MatrixOutcome будет равно NULL.
*/
MatrixOutcome multiplyMatrices(MatrixOutcome A, MatrixOutcome B);

/**
  @brief Создает минор матрицы с заданными параметрами.
  @param A Исходная матрица.
  @param excludeRowIndex Индекс исключаемой строки.
  @param excludeColIndex Индекс исключаемого столбца.
  @return Структура MatrixOutcome.
  @note Если в ходе получения минора произошла ошибка и код ошибки не
  NONE_ERROR, то поле matrix структуры MatrixOutcome будет равно NULL.
*/
MatrixOutcome getMinor(MatrixOutcome A, size_t excludeRowIndex,
					   size_t excludeColIndex);

/**
  @brief Вычисляет определитель матрицы.
  @param A Исходная матрица.
  @return Структура MatrixDeterminant.
  @note Если матрица A не является квадратной, то в поле errorCode структуры
  MatrixDeterminant будет указана ошибка, а поле determinant будет равно 0.
 */
MatrixDeterminant calculateDeterminant(MatrixOutcome A);

#endif