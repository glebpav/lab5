#ifndef LAB4A_FILEHELPER_H
#define LAB4A_FILEHELPER_H

#include "../ResponsesHandler.h"
#include "MyVector.h"


// TODO: make implementation of reading from file

Responses readFile(char *fileName, Vector *outputStrVector);

Responses getComputesFromStr(Vector *stringArray, Vector *computersArray);

Responses getConnectionsFromStr(Vector *stringArray, Vector *computersArray);

/*
Responses getTreeFromString(char **stringArray, int stringArrayLen, ScapeGoatTree *tree);*/


#endif //LAB4A_FILEHELPER_H
