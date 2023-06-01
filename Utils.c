#include <stdlib.h>
#include <string.h>
#include "Utils.h"
#include "stdio.h"
#include "ResponsesHandler.h"

int getInt(int *var) {
    int clearBuffer, res = scanf("%d", var);
    while ((clearBuffer = getchar()) != '\n' && clearBuffer != EOF) {}
    return res;
}

char *getLine(void) {
    char *line = (char *) malloc(100), *linep = line;
    size_t lenMax = 100, len = lenMax;
    int c;

    if (line == NULL)
        return NULL;

    for (;;) {
        c = fgetc(stdin);
        if (c == EOF) {
            free(line);
            return NULL;
        }

        if (--len == 0) {
            len = lenMax;
            char *linen = (char *) realloc(linep, lenMax *= 2);
            if (linen == NULL) {
                free(linep);
                return NULL;
            }
            line = linen + (line - linep);
            linep = linen;
        }

        if ((*line++ = c) == '\n') break;
    }
    *line--;
    *line = '\0';
    return linep;
}

Responses getSaveStingValue(char **value, char *messageToUser) {
    printf("%s>> ", messageToUser);
    *value = getLine();
    return value == NULL ? EXIT_RESPONSE : SUCCESS_RESPONSE;
}

Responses getSaveIntValue(int *value, char *messageToUser) {
    int res;
    printf("%s>> ", messageToUser);
    do {
        res = getInt(value);
        if (res == 0) throughException(NOT_INT_VALUE_EXCEPTION);
        else if (res == EOF) return EXIT_RESPONSE;
    } while (res <= 0);
    return SUCCESS_RESPONSE;
}

Responses getSaveUnsignedValue(unsigned int *unsignedValue, char *messageToUser) {
    int res;
    int value = 0;
    printf("%s", messageToUser);
    do {
        printf(">> ");
        res = getInt(&value);
        if (res == EOF) return EXIT_RESPONSE;
        else if (value < 0) throughException(NOT_UNSIGNED_VALUE_EXCEPTION), res = 0;
        else if (res == 0) throughException(NOT_INT_VALUE_EXCEPTION);
    } while (res <= 0);
    *unsignedValue = value;
    return SUCCESS_RESPONSE;
}

int strcmpForSubStr(char *subStr, char *checkingStr) {
    int i = 0;
    if (strlen(subStr) > strlen(checkingStr)) return 1;
    while (subStr[i] != '\0' && checkingStr[i] != '\0') {
        if (subStr[i] != checkingStr[i]) return 1;
        i++;
    }
    return 0;
}

Vector *getStringDifference(const char *str1, const char *str2) {
    Vector *difference = initVectorPtr(sizeof(int));
    // printf("str1 = %s\n", str1);
    // printf("str2 = %s\n", str2);
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        // printf("i - %d\n", i);
        int dif = (int) (str1[i] - str2[i]);
        addItemToVector(difference, &dif);
        i += 1;
    }
    return difference;
}

bool isUnsignedNum(const char *inputStr) {
    for (int i = 0; i < strlen(inputStr); i++)
        if ((int) inputStr[i] < '0' || (int) inputStr[i] > '9') return false;
    return true;
}