#ifndef OUTPUT_H
#define OUTPUT_H

#include <stdio.h>

/**
  @brief Выводит строку в стандартный поток вывода.
  @param buffer Указатель на строку, которая будет выведена.
*/
void outputToStdOut(const char *buffer);

/**
  @brief Выводит строку в файл.
  @param buffer Указатель на строку, которая будет записана в файл.
  @param file Указатель на открытый файловый поток.
*/
void outputToFile(const char *buffer, FILE *file);

#endif
