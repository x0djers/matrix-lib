/**
  @file config.h
  @author x0djers
  @brief Конфигурационный файл для настройки параметров библиотеки.
  Содержит основные макросы и определения типов, используемых в проекте.
  Позволяет централизованно управлять директориями, буферами, форматами вывода
  и типами данных.
*/

#ifndef CONFIG_H
#define CONFIG_H

/**
  @def DATA_DIR
  @brief Базовая директория для хранения всех данных (входных и выходных).
*/
#define DATA_DIR "data/"

/**
  @def INPUT_FILE_DIR
  @brief Директория входных файлов.
*/
#define INPUT_FILE_DIR DATA_DIR "input/"

/**
  @def OUTPUT_FILE_DIR
  @brief Директория выходных файлов.
*/
#define OUTPUT_FILE_DIR DATA_DIR "output/"

/**
  @def CURRENT_LANG
  @brief Язык для сообщений об ошибках.
  Возможные значения:
  - ::RU_LANGUAGE — русский язык (значение 0)
  - ::EN_LANGUAGE — английский язык (значение 1)
  @see MessageLanguage
*/
#define CURRENT_LANG 0

/**
  @def BUFFER_SIZE
  @brief Размер буфера для операций ввода/вывода (в байтах).
*/
#define BUFFER_SIZE 1024

/**
  @def MATRIX_ELEMENT_SPEC
  @brief Формат для представления элементов матрицы в строках ввода/вывода.
*/
#define MATRIX_ELEMENT_SPEC "%lf"

/**
  @def ELEMENT_DELIMITER
  @brief Строка с символами-разделителями между элементами матрицы.
*/
#define ELEMENT_DELIMITER " \t\n"

/**
  @typedef MATRIX_TYPE
  @brief Тип данных, используемый для хранения элементов матрицы.
*/
typedef double MATRIX_TYPE;

/**
  @typedef DETERMINANT_TYPE
  @brief Тип данных, используемый для хранения значения определителя.
*/
typedef double DETERMINANT_TYPE;

#endif