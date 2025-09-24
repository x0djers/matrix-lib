/**
  @file matrix.h
  @author x0djers
  @brief Предоставляет функции для работы с матрицами.
*/

#ifndef MATRIX_H
#define MATRIX_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "config.h"
#include "errors.h"
#include "output.h"

/**
  @struct Matrix
  @brief Структура матрицы.
*/
typedef struct {
	size_t rows;		 ///< Количество строк.
	size_t cols;		 ///< Количеств столбцов.
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
MatrixOutcome createMatrix(size_t rows, size_t columns);

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
 * @brief Получает элемент матрицы по заданным индексам строки и столбца
 *
 * Функция безопасно извлекает значение элемента матрицы, выполняя проверку
 * корректности входных параметров и границ массива. В случае ошибки
 * возвращает соответствующий код, а при успехе записывает значение элемента
 * по переданному указателю.
 *
 * @param[in] A Указатель на структуру MatrixOutcome, содержащую матрицу
 * @param[in] row Индекс строки (начинается с 0)
 * @param[in] column Индекс столбца (начинается с 0)
 * @param[out] element Указатель для записи значения элемента матрицы
 *
 * @return Код ошибки типа MatrixErrorCode:
 *
 * @note Функция записывает значение элемента только при успешном выполнении.
 *       Перед использованием указателя element рекомендуется проверять
 *       возвращаемый код ошибки.
 */
MatrixErrorCode getMatrixElement(const MatrixOutcome* A,
                                 size_t row,
                                 size_t column,
                                 MATRIX_TYPE* element);

/**
 * @brief Устанавливает значение элемента матрицы.
 *
 * Функция записывает переданное значение `value` в элемент матрицы `A`
 * на позицию с индексами `row` и `column`.
 *
 * @param A Указатель на структуру MatrixOutcome, содержащую матрицу.
 * @param row Индекс строки элемента (0-based).
 * @param column Индекс столбца элемента (0-based).
 * @param value Значение, которое будет установлено в элемент матрицы.
 *
 * @return Код ошибки типа MatrixErrorCode.
 */
MatrixErrorCode setMatrixElement(const MatrixOutcome* A,
                                 size_t row,
                                 size_t column,
                                 MATRIX_TYPE value);

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
  @brief Проверяет возможность умножения матриц.
  @param A Первая матрица.
  @param B Вторая матрица.
  @return Код ошибки MatrixErrorCode.
*/
bool canMultiplyMatrices(MatrixOutcome A, MatrixOutcome B);

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

/**
  @brief Формирует строковое представление матрицы.
  Эта функция выделяет динамический буфер и заполняет его строковым
  представлением содержимого матрицы, хранящейся в объекте MatrixOutcome.
  Каждый элемент форматируется согласно спецификатору MATRIX_ELEMENT_SPEC.
  Элементы разделяются пробелами, строки - символами новой строки.
  @param A Матрица для вывода.
  @return Указатель на строку с текстовым представлением матрицы.
		  Возвращает `NULL`, если не удалось выделить память.
  @note После использования, память, используемая для буфера, должна быть
  очищена вручную.
*/
char* prepareMatrixBuffer(MatrixOutcome A);

/**
  @brief Выводит матрицу, используя пользовательскую функцию вывода.
  @param A Структура содержащая матрицу и возможный код ошибки.
  @param output Функция обратного вызова для вывода строки.
  @param context Контекст, передаваемый в функцию вывода (например, путь на до
  файла или указатель на поток вывода).
  @return Код ошибки MatrixErrorCode.
*/
MatrixErrorCode printMatrix(MatrixOutcome A, outputFunc output, void* context);

/**
  @param fileName Имя файла, из которого нужно считать матрицу.
 *
 * @brief Загружает матрицу из текстового файла.
  Функция считывает значения матрицы из файла, в котором данные представлены
  в табличной форме без указания размеров. Размеры определяются автоматически
  по количеству строк и столбцов в первой строке.
  Разделители между элементами определяются параметром ELEMENT_DELIMITER в
 конфиге. Тип элементов и формат чтения определяются параметрами MATRIX_TYPE и
 MATRIX_ELEMENT_SPEC.
  @return MatrixOutcome Структура с результатом загрузки.
*/
MatrixOutcome loadMatrixFromFile(const char* fileName);
#endif