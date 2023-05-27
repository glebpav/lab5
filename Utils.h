#ifndef LAB4A_UTILS_H
#define LAB4A_UTILS_H

#include "ResponsesHandler.h"
#include "model/MyVector.h"

Responses getSaveIntValue(int *value, char *messageToUser);

Responses getSaveStingValue(char **value, char *messageToUser);

int strcmpForSubStr(char *subStr, char *checkingStr);

Vector *getStringDifference(char *str1, char *str2);

#endif //LAB4A_UTILS_H
