#ifndef ERRORS_H
#define ERRORS_H

/**
  @enum MatrixErrorCode
  @brief Перечисление всех возможных кодов ошибок, связанных с работой с
  матрицами.
*/
typedef enum {
	NONE_ERROR,				  ///< Операция выполнена без ошибки.
	MATRIX_ALLOCATION_ERROR,  ///< Ошибка выделения памяти для матрицы.
	DATA_ALLOCATION_ERROR,	///< Ошибка выделения памяти для элементов матрицы.
	INVALID_ELEMENT_ERROR, /// Ошибка неверного элемента матрицы.
	INVALID_SIZE_ERROR,		///< Некорректный размер матрицы.
	NULL_POINTER_ERROR,		///< Ошибка нулевого указателя.
	SIZE_MISMATCH_ERROR,	///< Ошибка несовпадения размеров.
	NOT_SQUARE_MATRIX_ERROR,  ///< Матрица не является квадратной.
	EXCLUSION_ERROR,		  ///< Ошибка исключения строки/столбца.
	PREPARE_BUFFER_ERROR,	  ///< Ошибка подготовки строкового представления.
	FILE_OPEN_ERROR,		  ///< Ошибка открытия файла.
	FILE_READ_ERROR,		  ///< Ошибка чтения файла.
	UNKNOWN_ERROR,			  ///< Неизвестная ошибка.
	ERRORS_COUNT,			  ///< Количество ошибок (служебное значение).
} MatrixErrorCode;

/**
  @struct MatrixErrorMessage
  @brief Структура, описывающая сообщение об ошибке.
  Используется для отображения текстовых описаний ошибок на разных языках.
*/
typedef struct {
	MatrixErrorCode code;
	const char* message;
} MatrixErrorMessage;

/**
  @enum MessageLanguage
  @brief Языки, поддерживаемые для отображения сообщений об ошибках.
*/
typedef enum {
	RU_LANGUAGE,
	EN_LANGUAGE,
	LANGUAGES_COUNT,
} MessageLanguage;

/**
  @brief Получает текстовое описание ошибки по коду.
  Функция возвращает строку с описанием ошибки на языке, заданном в конфиге.
  Если язык задан некорректно, то используется язык по умолчанию (обычно
  `EN_LANGUAGE`).
  @param code Код ошибки из перечисления MatrixErrorCode.
  @return Строка с описанием ошибки.
*/
const char* getErrorMessage(MatrixErrorCode code);

#endif
