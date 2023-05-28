#ifndef LAB4A_RESPONSESHANDLER_H
#define LAB4A_RESPONSESHANDLER_H

#include <stdbool.h>

typedef enum ResponsesTypes {
    NOT_INT_VALUE_EXCEPTION,
    PRIMARY_VALUE_DUPLICATION,
    NOT_UNSIGNED_VALUE_EXCEPTION,
    INPUT_NOT_IN_RANGE_EXCEPTION,
    TABLE_OVERFLOW_EXCEPTION,
    NO_SUCH_FILE_EXCEPTION,
    INCORRECT_FILE_FORMAT_EXCEPTION,
    UNKNOWN_KEY_EXCEPTION,
    COMMON_EXCEPTION,
    FILE_EXCEPTION,
    EMPTY_FIELD_EXCEPTION,
    SUCCESS_RESPONSE,
    RETURN_BACK_RESPONSE,
    EXIT_RESPONSE
} Responses;

bool isException(Responses response);
char *getResponseMessage(Responses responsesTypes);
void throughException(Responses exceptions);
void printSuccessMessage(Responses response);


#endif //LAB4A_RESPONSESHANDLER_H
