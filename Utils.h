#ifndef LAB4A_UTILS_H
#define LAB4A_UTILS_H

#include "ResponsesHandler.h"
#include "model/MyVector.h"

Responses getSaveIntValue(int *value, char *messageToUser);

Responses getSaveStingValue(char **value, char *messageToUser);

Responses getSaveUnsignedValue(unsigned int *value, char *messageToUser);

int strcmpForSubStr(char *subStr, char *checkingStr);

Vector *getStringDifference(const char *str1, const char *str2);

bool isUnsignedNum(const char *inputStr);

#endif //LAB4A_UTILS_H
