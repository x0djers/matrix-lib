#ifndef MESSAGES_H
#define MESSAGES_H

#include "../errors.h"

#define DEFAULT_LANGUAGE EN_LANGUAGE

/**
  @var errorMessages
  @brief Массив указателей на сообщения об ошибках для различных языков.
  Индекс массива соответствует значению из перечисления MessageLanguage.
  Каждое сообщение в массиве представляет собой указатель на массив структур MatrixErrorMessage,
  содержащих текстовые описания ошибок для соответствующего языка.
*/
extern const MatrixErrorMessage* errorMessages[LANGUAGES_COUNT];

/**
  @brief Инициализация сообщений об ошибках для всех поддерживаемых языков.
  Эта функция вызывается перед использованием функции getErrorMessage() для корректной работы.
  Она загружает текстовые сообщения об ошибках для каждого языка, определяя массивы для каждого языка.
*/
void initErrorMessages();

/**
  @brief Получение текущего языка для отображения сообщений об ошибках.
  Возвращает значение параметра CURRENT_LANG из конфига. Если значение в конфиге задано некорректно,
  то возвращает значение по умолчанию (обычно EN_LANGUAGE)
  @return Текущий язык, используемый для отображения сообщений об ошибках (тип MessageLanguage).
*/
MessageLanguage getCurrentLanguage();

#endif
