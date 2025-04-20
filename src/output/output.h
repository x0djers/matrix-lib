/**
  @file output.h
  @author x0djers
  @brief Интерфейс для функций вывода строк.

  Предоставляет тип функции обратного вызова и реализации для вывода
  строки в стандартный поток или в файл.
*/

#ifndef OUTPUT_H
#define OUTPUT_H

/**
  @typedef outputFunc
  @brief Тип функции для вывода строки.
*/
typedef void (*outputFunc)(const char *, void *context);

/**
  @brief Выводит строку в стандартный поток вывода.
  @param buffer Указатель на строку, которая будет выведена.
  @param context Указатель на поток вывода.
*/
void outputToStd(const char *buffer, void *context);

/**
  @brief Выводит строку в файл.
  @param buffer Указатель на строку, которая будет записана в файл.
  @param context Путь до файла для записи.
*/
void outputToFile(const char *buffer, void *context);

#endif
