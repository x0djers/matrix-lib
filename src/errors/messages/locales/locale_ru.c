#include "../messages.h"

const MatrixErrorMessage RU_MESSAGES[] = {
	[NONE_ERROR] = {NONE_ERROR, "Операция выполнена без ошибки."},
	[MATRIX_ALLOCATION_ERROR] = {MATRIX_ALLOCATION_ERROR, "Ошибка выделения памяти для матрицы."},
	[DATA_ALLOCATION_ERROR] = {DATA_ALLOCATION_ERROR, "Ошибка выделения памяти для элементов матрицы."},
	[INVALID_SIZE_ERROR] = {INVALID_SIZE_ERROR, "Некорректный размер матрицы."},
	[NULL_POINTER_ERROR] = {NULL_POINTER_ERROR, "Ошибка указателя. Передан нулевой указатель."},
	[SIZE_MISMATCH_ERROR] = {SIZE_MISMATCH_ERROR, "Ошибка несоотвествия размеров матриц."},
	[NOT_SQUARE_MATRIX_ERROR] = {NOT_SQUARE_MATRIX_ERROR, "Матрица не является квадратной."},
	[EXCLUSION_ERROR] = {EXCLUSION_ERROR, "Ошибка исключения строки/столбца."},
	[PREPARE_BUFFER_ERROR] = {PREPARE_BUFFER_ERROR, "Ошибка подготовки строкового представления."},
	[FILE_OPEN_ERROR] = {FILE_OPEN_ERROR, "Ошибка открытия файла."},
	[FILE_READ_ERROR] = {FILE_READ_ERROR, "Ошибка чтения файла."},
	[UNKNOWN_ERROR] = {UNKNOWN_ERROR, "Неизвестная ошибка."},
};

