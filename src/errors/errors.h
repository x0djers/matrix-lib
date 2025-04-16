#ifndef ERRORS_H
#define ERRORS_H

typedef enum {
	NONE_ERROR,				  ///< Операция выполнена без ошибки.
	MATRIX_ALLOCATION_ERROR,  ///< Ошибка выделения памяти для матрицы.
	DATA_ALLOCATION_ERROR,	///< Ошибка выделения памяти для элементов матрицы.
	INVALID_SIZE_ERROR,		///< Некорректный размер матрицы.
	NULL_POINTER_ERROR,		///< Ошибка нулевого указателя.
	SIZE_MISMATCH_ERROR,	///< Ошибка несовпадения размеров.
	NOT_SQUARE_MATRIX_ERROR,  ///< Матрица не является квадратной.
	EXCLUSION_ERROR,		  ///< Ошибка исключения строки/столбца.
	PREPARE_BUFFER_ERROR,	  ///< Ошибка подготовки строкового представления.
} MatrixErrorCode;

#endif
