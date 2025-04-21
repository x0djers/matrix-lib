/**
  @file tests_matrix.c
  @author x0djers
  @brief Модуль реализации тестов для matrix.c
*/
#include <CUnit/Basic.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../src/matrix/matrix.h"

// Тест создания матрицы
void test_createMatrix(void) {
	{
		// Тест на создание валидной матрицы
		MatrixOutcome matr = createMatrix(2, 3);
		CU_ASSERT_PTR_NOT_NULL(matr.matrix);
		CU_ASSERT_PTR_NOT_NULL(matr.matrix->data);
		CU_ASSERT_EQUAL(matr.matrix->rows, 2);
		CU_ASSERT_EQUAL(matr.matrix->cols, 3);
		CU_ASSERT_EQUAL(matr.errorCode, NONE_ERROR);
		freeMatrixOutcome(&matr);
	}

	{
		// Тест на создание матрицы с нулевыми размерами
		MatrixOutcome invalid = createMatrix(0, 0);
		CU_ASSERT_EQUAL(invalid.errorCode, INVALID_SIZE_ERROR);
		freeMatrixOutcome(&invalid);
	}
}

// Тест на проверку равенства размеров матриц
void test_isMatricesSizesEqual(void) {
	MatrixOutcome A = createMatrix(2, 2);
	MatrixOutcome B = createMatrix(2, 2);
	MatrixOutcome C = createMatrix(3, 2);

	CU_ASSERT_TRUE(isMatricesSizesEqual(A, B));
	CU_ASSERT_FALSE(isMatricesSizesEqual(A, C));

	freeMatrixOutcome(&A);
	freeMatrixOutcome(&B);
	freeMatrixOutcome(&C);
}

// Тест на проверку, является ли матрица квадратной
void test_isSquareMatrix(void) {
	MatrixOutcome A = createMatrix(3, 3);
	MatrixOutcome B = createMatrix(2, 3);

	CU_ASSERT_TRUE(isSquareMatrix(A));
	CU_ASSERT_FALSE(isSquareMatrix(B));

	freeMatrixOutcome(&A);
	freeMatrixOutcome(&B);
}

// Тест на умножение матриц
void test_multiplyMatrices(void) {
	MatrixOutcome A = createMatrix(2, 3);
	MatrixOutcome B = createMatrix(3, 2);
	MatrixOutcome C = createMatrix(5, 4);

	MATRIX_TYPE dataA[6] = {1, 2, 3, 4, 5, 6};
	MATRIX_TYPE dataB[6] = {7, 8, 9, 10, 11, 12};
	fillMatrix(&A, dataA);
	fillMatrix(&B, dataB);

	MatrixOutcome result = multiplyMatrices(A, B);
	CU_ASSERT_EQUAL(result.matrix->rows, 2);
	CU_ASSERT_EQUAL(result.matrix->cols, 2);
	CU_ASSERT_EQUAL(result.errorCode, NONE_ERROR);

	result = multiplyMatrices(A, C);
	CU_ASSERT_EQUAL(result.errorCode, SIZE_MISMATCH_ERROR);

	freeMatrixOutcome(&A);
	freeMatrixOutcome(&B);
	freeMatrixOutcome(&C);
	freeMatrixOutcome(&result);
}

// Тест на операцию сложения и вычитания матриц
void test_getSumOrDiffMatrices(void) {
	MatrixOutcome A = createMatrix(2, 2);
	MatrixOutcome B = createMatrix(2, 2);

	MATRIX_TYPE dataA[4] = {1, 2, 3, 4};
	MATRIX_TYPE dataB[4] = {5, 6, 7, 8};
	fillMatrix(&A, dataA);
	fillMatrix(&B, dataB);

	MatrixOutcome result = getSumOrDiffMatrices(A, B, false);
	CU_ASSERT_EQUAL(result.matrix->data[0][0], 6);	 // 1 + 5
	CU_ASSERT_EQUAL(result.matrix->data[1][1], 12);	 // 4 + 8
	CU_ASSERT_EQUAL(result.errorCode, NONE_ERROR);

	result = getSumOrDiffMatrices(A, B, true);
	CU_ASSERT_EQUAL(result.matrix->data[0][0], -4);	 // 1 - 5
	CU_ASSERT_EQUAL(result.matrix->data[1][1], -4);	 // 4 - 8
	CU_ASSERT_EQUAL(result.errorCode, NONE_ERROR);

	freeMatrixOutcome(&A);
	freeMatrixOutcome(&B);
	freeMatrixOutcome(&result);
}

// Тест на создание копии матрицы
void test_getMatrixCopy(void) {
	MatrixOutcome A = createMatrix(2, 2);
	MATRIX_TYPE dataA[4] = {1, 2, 3, 4};
	fillMatrix(&A, dataA);

	MatrixOutcome copy = getMatrixCopy(A);
	CU_ASSERT_PTR_NOT_NULL(copy.matrix);
	CU_ASSERT_EQUAL(copy.matrix->data[0][0], 1);
	CU_ASSERT_EQUAL(copy.matrix->data[1][1], 4);
	CU_ASSERT_EQUAL(copy.errorCode, NONE_ERROR);

	freeMatrixOutcome(&A);
	freeMatrixOutcome(&copy);
}

// Тест на транспонирование матрицы
void test_transposeMatrix(void) {
	MatrixOutcome A = createMatrix(2, 3);
	MATRIX_TYPE dataA[6] = {1, 2, 3, 4, 5, 6};
	fillMatrix(&A, dataA);

	MatrixOutcome result = transposeMatrix(A);
	CU_ASSERT_EQUAL(result.matrix->rows, 3);
	CU_ASSERT_EQUAL(result.matrix->cols, 2);
	CU_ASSERT_EQUAL(result.matrix->data[0][1], 4);
	CU_ASSERT_EQUAL(result.matrix->data[1][0], 2);
	CU_ASSERT_EQUAL(result.errorCode, NONE_ERROR);

	freeMatrixOutcome(&A);
	freeMatrixOutcome(&result);
}

// Тест на подсчёт определителя
void test_calculateDeterminant(void) {
	{
		MatrixOutcome matr = createMatrix(2, 2);
		matr.matrix->data[0][0] = 1.0;
		matr.matrix->data[0][1] = 2.0;
		matr.matrix->data[1][0] = 3.0;
		matr.matrix->data[1][1] = 4.0;

		MatrixDeterminant det = calculateDeterminant(matr);
		CU_ASSERT_EQUAL(det.errorCode, NONE_ERROR);
		CU_ASSERT_DOUBLE_EQUAL(det.determinant, -2.0, 0.001);

		freeMatrixOutcome(&matr);
	}

	{
		MatrixOutcome nonSquare = createMatrix(2, 3);
		MatrixDeterminant det = calculateDeterminant(nonSquare);
		CU_ASSERT_NOT_EQUAL(det.errorCode, NONE_ERROR);

		freeMatrixOutcome(&nonSquare);
	}
}

// Тест на загрузку из файла
void test_loadMatrixFromFile(void) {
	const char* filename = "test_matrix.txt";

	FILE* f = fopen(filename, "w");
	fprintf(f, "1.1 2.2\n3.3 4.4");
	fclose(f);

	MatrixOutcome loaded = loadMatrixFromFile(filename);
	CU_ASSERT_PTR_NOT_NULL(loaded.matrix);
	CU_ASSERT_PTR_NOT_NULL(loaded.matrix->data);

	CU_ASSERT_EQUAL(loaded.matrix->rows, 2);
	CU_ASSERT_EQUAL(loaded.matrix->cols, 2);

	CU_ASSERT_DOUBLE_EQUAL(loaded.matrix->data[0][0], 1.1, 0.001);
	CU_ASSERT_DOUBLE_EQUAL(loaded.matrix->data[1][1], 4.4, 0.001);

	freeMatrixOutcome(&loaded);
	remove(filename);
}

/**
 * @brief Функция-регистратор всех тестов для работы с матрицами.
 */
void register_matrix_tests(void) {
	CU_pSuite suite = CU_add_suite("Matrix Tests", NULL, NULL);
	CU_add_test(suite, "Create Matrix", test_createMatrix);
	CU_add_test(suite, "Check Matrices Sizes", test_isMatricesSizesEqual);
	CU_add_test(suite, "Check Square Matrix", test_isSquareMatrix);
	CU_add_test(suite, "Matrix Multiplication", test_multiplyMatrices);
	CU_add_test(suite, "Matrix Sum and Difference", test_getSumOrDiffMatrices);
	CU_add_test(suite, "Matrix Copy", test_getMatrixCopy);
	CU_add_test(suite, "Matrix Transposition", test_transposeMatrix);
	CU_add_test(suite, "Matrix Determinant", test_calculateDeterminant);
	CU_add_test(suite, "Load Matrix", test_loadMatrixFromFile);
}