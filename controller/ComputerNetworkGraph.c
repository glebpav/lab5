#include <stdlib.h>
#include <stdio.h>
#include "../ResponsesHandler.h"
#include "ComputerNetworkGraph.h"
#include "string.h"
#include "../Utils.h"
#include <math.h>

ComputerNetworkGraph initComputerNetworkGraph() {
    ComputerNetworkGraph network = {
            initVectorPtr(sizeof(Computer)),
            initVectorPtr(sizeof(Connection))
    };
    return network;
}

void destroyComputerNetworkGraph(ComputerNetworkGraph *graph) {

}

Responses addComputer(ComputerNetworkGraph *graph, char *newComputerName, unsigned portIdx) {

    for (int i = 0; i < graph->computesArray->arrayLength; ++i) {
        Computer *computer = (Computer *) getItemFromVector(*(graph->computesArray), i);
        if (strcmp(computer->name, newComputerName) == 0) {
            return PRIMARY_VALUE_DUPLICATION;
        }
    }

    Computer computer = {strdup(newComputerName), portIdx};
    addItemToVector(graph->computesArray, &computer);

    return SUCCESS_RESPONSE;
}

Responses addConnection(ComputerNetworkGraph *graph, char *computerName1, char *computerName2) {
    return SUCCESS_RESPONSE;
}

Responses deleteComputer(ComputerNetworkGraph *graph, char *computerName) {

    for (int i = 0; i < graph->computesArray->arrayLength; ++i) {
        Computer *computer = (Computer *) getItemFromVector(*(graph->computesArray), i);
        if (strcmp(computer->name, computerName) == 0) {
            deleteItemFromVector(graph->computesArray, i);
            return SUCCESS_RESPONSE;
        }
    }

    return UNKNOWN_KEY_EXCEPTION;
}

Responses deleteConnection(ComputerNetworkGraph *graph, char *computerName1, char *computerName2) {
    return SUCCESS_RESPONSE;
}

Responses changeComputerName(ComputerNetworkGraph *graph, char *oldComputerName, char *newComputerName) {

    for (int i = 0; i < graph->computesArray->arrayLength; ++i) {
        Computer *computer = (Computer *) getItemFromVector(*(graph->computesArray), i);
        if (strcmp(computer->name, oldComputerName) == 0) {
            computer->name = strdup(newComputerName);
            setItemVector(graph->computesArray, computer, i);
            return SUCCESS_RESPONSE;
        }
    }
    return UNKNOWN_KEY_EXCEPTION;
}

Responses changeComputerPortIdx(ComputerNetworkGraph *graph, char *computerName, unsigned newPortIdx) {

    for (int i = 0; i < graph->computesArray->arrayLength; ++i) {
        Computer *computer = (Computer *) getItemFromVector(*(graph->computesArray), i);
        if (strcmp(computer->name, computerName) == 0) {
            computer->portIdx = newPortIdx;
            setItemVector(graph->computesArray, computer, i);
            return SUCCESS_RESPONSE;
        }
    }
    return UNKNOWN_KEY_EXCEPTION;
}

Responses
changeConnectionDelay(ComputerNetworkGraph *graph, char *computerName1, char *computerName2, unsigned newDelay) {
    return SUCCESS_RESPONSE;
}

Responses addConnectionPort(ComputerNetworkGraph *graph, char *computerName1, char *computerName2, unsigned newPort) {
    return SUCCESS_RESPONSE;
}

Responses
deleteConnectionPort(ComputerNetworkGraph *graph, char *computerName1, char *computerName2, unsigned deletingPortIdx) {
    return SUCCESS_RESPONSE;
}

Responses printMatrix(ComputerNetworkGraph *graph) {
    return SUCCESS_RESPONSE;
}

Responses printAdjacencyList(ComputerNetworkGraph *graph) {

    if (graph->computesArray->arrayLength == 0) {
        printf("List of computers is empty ((");
        return SUCCESS_RESPONSE;
    }

    for (int i = 0; i < graph->computesArray->arrayLength; ++i) {
        Computer *computer = (Computer *) getItemFromVector(*(graph->computesArray), i);
        printf("[ name = \"%s\"; portIdx = %u ] -> \n", computer->name, computer->portIdx);
    }

    return SUCCESS_RESPONSE;
}