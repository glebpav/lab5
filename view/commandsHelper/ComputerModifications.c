#include <stdlib.h>
#include <stdio.h>
#include "ComputerModifications.h"
#include "../../Utils.h"
#include "../../model/FileHelper.h"


Responses addComputerD(ComputerNetworkGraph *graph) {
    char *newComputerName;
    unsigned newPortIdx;

    if (!getSaveStingValue(&newComputerName, "Please, input new computer NAME\n"))
        return EXIT_RESPONSE;
    if (!getSaveUnsignedValue(&newPortIdx, "Please, input new computer PORT IDX\n"))
        return EXIT_RESPONSE;

    Responses responses = addComputer(graph, newComputerName, newPortIdx);
    if (isException(responses)) throughException(responses);
    free(newComputerName);

    return SUCCESS_RESPONSE;
}

Responses deleteComputerD(ComputerNetworkGraph *graph) {
    char *newComputerName;

    if (!getSaveStingValue(&newComputerName, "Please, input deleting computer NAME\n"))
        return EXIT_RESPONSE;

    Responses response = deleteComputer(graph, newComputerName);
    if (isException(response)) throughException(response);
    free(newComputerName);

    return SUCCESS_RESPONSE;
}

Responses changeComputerNameD(ComputerNetworkGraph *graph) {
    char *oldComputerName;
    char *newComputerName;

    if (!getSaveStingValue(&oldComputerName, "Please, input OLD computer NAME\n"))
        return EXIT_RESPONSE;
    if (!getSaveStingValue(&newComputerName, "Please, input NEW computer NAME\n"))
        return EXIT_RESPONSE;

    Responses response = changeComputerName(graph, oldComputerName, newComputerName);
    if (isException(response)) throughException(response);

    free(oldComputerName);
    free(newComputerName);

    return SUCCESS_RESPONSE;
}

Responses changeComputerPortIdxD(ComputerNetworkGraph *graph) {
    char *computerName;
    unsigned int newPortIdx;

    if (!getSaveStingValue(&computerName, "Please, input computer NAME\n"))
        return EXIT_RESPONSE;
    if (!getSaveUnsignedValue(&newPortIdx, "Please, input NEW PORT IDX\n"))
        return EXIT_RESPONSE;

    Responses response = changeComputerPortIdx(graph, computerName, newPortIdx);
    if (isException(response)) throughException(response);

    free(computerName);

    return SUCCESS_RESPONSE;
}

Responses readComputersFromFileD(ComputerNetworkGraph *graph) {
    char *fileName;
    Vector *inputStrArray = initVectorPtr(sizeof(char *));
    Vector *computerArray = initVectorPtr(sizeof(Computer));

    if (!getSaveStingValue(&fileName, "Please, input FILENAME\n"))
        return EXIT_RESPONSE;

    Responses response = readFile(fileName, inputStrArray);
    if (isException(response)) {
        throughException(response);
        return SUCCESS_RESPONSE;
    }

    response = getComputesFromStr(inputStrArray, computerArray);
    if (isException(response)) {
        throughException(response);
        return SUCCESS_RESPONSE;
    }

    for (int i = 0; i < computerArray->arrayLength; ++i) {
        Computer *computer = getItemFromVector(*computerArray, i);
        addComputer(graph, computer->name, computer->portIdx);
    }

    return SUCCESS_RESPONSE;
}

Responses returnBack3D(ComputerNetworkGraph *graph) {
    return RETURN_BACK_RESPONSE;
}