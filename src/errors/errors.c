#include <stdlib.h>
#include <stdio.h>

#include "errors.h"
#include "messages/messages.h"

const char* getErrorMessage(const MatrixErrorCode code) {
    const char* errorMessage;

    if (errorMessages[0] == NULL)
        initErrorMessages();

    const MessageLanguage language = getCurrentLanguage();

    if (code < ERRORS_COUNT) {
        errorMessage = errorMessages[language][code].message;
    } else {
        errorMessage = errorMessages[language][UNKNOWN_ERROR].message;
    }

    return errorMessage;
}