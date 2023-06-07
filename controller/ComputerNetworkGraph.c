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
    };
    return network;
}

void destroyComputerNetworkGraph(ComputerNetworkGraph *graph) {
    for (int i = 0; i < graph->computesArray->arrayLength; ++i) {
        Computer *computer = getItemFromVector(*(graph->computesArray), i);
        for (int j = 0; j < computer->connectionsList->listLength; ++j) {
            Connection *connection = getItemFromListByIdx(*(computer->connectionsList), j);
            free(connection->destinationComputer);
            free(connection->secondComputer);
            destroyVector(connection->accessedPorts);
        }
        destroyList(computer->connectionsList);
        free(computer->name);
    }
    destroyVector(graph->computesArray);
}

Responses addComputer(ComputerNetworkGraph *graph, char *newComputerName, unsigned portIdx) {

    for (int i = 0; i < graph->computesArray->arrayLength; ++i) {
        Computer *computer = (Computer *) getItemFromVector(*(graph->computesArray), i);
        if (strcmp(computer->name, newComputerName) == 0) {
            return PRIMARY_VALUE_DUPLICATION;
        }
    }

    Computer computer = {
            .name = strdup(newComputerName),
            .portIdx = portIdx,
            .connectionsList = initListPtr(sizeof(Connection))
    };

    addItemToVector(graph->computesArray, &computer);

    return SUCCESS_RESPONSE;
}

Responses addConnection(ComputerNetworkGraph *graph, char *computerName1, char *computerName2, unsigned int delay) {

    Computer *computer1 = NULL;
    Computer *computer2 = NULL;

    if (strcmp(computerName1, computerName2) == 0) return PRIMARY_VALUE_DUPLICATION;

    int usedComputers = 0;
    for (int i = 0; i < graph->computesArray->arrayLength && usedComputers < 2; ++i) {
        Computer *computer = (Computer *) getItemFromVector(*(graph->computesArray), i);
        if (strcmp(computer->name, computerName1) == 0) {
            computer1 = computer;
            usedComputers += 1;
        } else if (strcmp(computer->name, computerName2) == 0) {
            computer2 = computer;
            usedComputers += 1;
        }
    }
    if (computer1 != NULL && computer2 != NULL) {
        Connection connection1 = {
                delay,
                strdup(computerName2),
                initVectorPtr(sizeof(unsigned int)),
                strdup(computerName1)
        };
        printf("%p\n", computer1->connectionsList);
        addItemToList(computer1->connectionsList, &connection1);

        Connection connection2 = {
                delay,
                strdup(computerName1),
                initVectorPtr(sizeof(unsigned int)),
                strdup(computerName2)
        };
        printf("%p\n", computer2->connectionsList);
        addItemToList(computer2->connectionsList, &connection2);
        return SUCCESS_RESPONSE;
    }
    return UNKNOWN_KEY_EXCEPTION;
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

Responses deleteConnection(ComputerNetworkGraph *graph, Vector *deletingConnectionsArray) {

    Connection *connection = getItemFromVector(*deletingConnectionsArray, 0);
    char *computerName1 = strdup(connection->destinationComputer);
    char *computerName2 = strdup(connection->secondComputer);

    printf("debug: from deletingConnections.c\n");

    for (int i = 0; i < deletingConnectionsArray->arrayLength / 2; ++i) {
        Connection *connection1 = (Connection *) getItemFromVector(*deletingConnectionsArray, i);
        Connection *connection2 = (Connection *) getItemFromVector(*deletingConnectionsArray,
                                                                   i + deletingConnectionsArray->arrayLength / 2);

        // connection1->secondComputer = connection2->destinationComputer;
        // connection2->secondComputer = connection1->destinationComputer;

        printf(
                "[%d] - (\"%s\" <=> \"%s\" | delay = %u)\n",
                i,
                connection1->destinationComputer,
                connection2->destinationComputer,
                connection1->transmissionDelay
        );
    }

    printf("comp1: %s\n", computerName1);
    printf("comp2: %s\n", computerName2);

    for (int i = 0; i < graph->computesArray->arrayLength; ++i) {
        Computer *computer = getItemFromVector(*(graph->computesArray), i);

        if (strcmp(computer->name, computerName1) != 0
            && strcmp(computer->name, computerName2) != 0)
            continue;

        for (int k = 0; k < deletingConnectionsArray->arrayLength; ++k) {
            Connection *selectedConnection = (Connection *) getItemFromVector(*deletingConnectionsArray, k);

            if (strcmp(selectedConnection->destinationComputer, computer->name) == 0) {
                free(selectedConnection->destinationComputer);
                // free(selectedConnection->secondComputer);
                if (selectedConnection->accessedPorts) destroyVector(selectedConnection->accessedPorts);

                printf("delay: %u\n", selectedConnection->transmissionDelay);
                deleteItemFromList(computer->connectionsList, selectedConnection);

                deleteItemFromVector(deletingConnectionsArray, k);
                k -= 1;
            }
        }
    }

    free(computerName1);
    free(computerName2);
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

Responses changeConnectionDelay(ComputerNetworkGraph *graph, char *computerName1, char *computerName2, unsigned newDelay) {
    return SUCCESS_RESPONSE;
}

Responses addConnectionPort(ComputerNetworkGraph *graph, char *computerName1, char *computerName2, unsigned int newPort) {
    Computer *computer1 = NULL;
    Computer *computer2 = NULL;

    if (strcmp(computerName1, computerName2) == 0) return PRIMARY_VALUE_DUPLICATION;

    int usedComputers = 0;
    for (int i = 0; i < graph->computesArray->arrayLength && usedComputers < 2; ++i) {
        Computer *computer = (Computer *) getItemFromVector(*(graph->computesArray), i);
        if (strcmp(computer->name, computerName1) == 0) {
            computer1 = computer;
            usedComputers += 1;
        } else if (strcmp(computer->name, computerName2) == 0) {
            computer2 = computer;
            usedComputers += 1;
        }
    }
    if (computer1 != NULL && computer2 != NULL) {
        for (int i = 0; i < computer1->connectionsList->listLength; ++i) {
            Connection *connection = getItemFromListByIdx(*(computer1->connectionsList), i);
            if (strcmp(connection->destinationComputer, computerName2) == 0)
                addItemToVector(connection->accessedPorts, &newPort);
        }
        for (int i = 0; i < computer2->connectionsList->listLength; ++i) {
            Connection *connection = getItemFromListByIdx(*(computer2->connectionsList), i);
            if (strcmp(connection->destinationComputer, computerName2) == 0)
                addItemToVector(connection->accessedPorts, &newPort);
        }

        return SUCCESS_RESPONSE;
    }
    return UNKNOWN_KEY_EXCEPTION;
}

Responses deleteConnectionPort(ComputerNetworkGraph *graph, char *computerName1, char *computerName2, unsigned deletingPortIdx) {
    return SUCCESS_RESPONSE;
}

Responses printMatrix(ComputerNetworkGraph *graph) {
    return SUCCESS_RESPONSE;
}

void printAdjacencyList(ComputerNetworkGraph *graph) {

    if (graph->computesArray->arrayLength == 0) {
        printf("List of computers is empty ((");
        return;
    }

    for (int i = 0; i < graph->computesArray->arrayLength; ++i) {
        Computer *computer = (Computer *) getItemFromVector(*(graph->computesArray), i);
        printf("[ name = \"%s\"; portIdx = %u ] : ", computer->name, computer->portIdx);
        for (int j = 0; j < computer->connectionsList->listLength; ++j) {
            Connection *connection = (Connection *) getItemFromListByIdx(*(computer->connectionsList), j);
            printf("(delay = %u; destComputer = \"%s\") => ", connection->transmissionDelay,
                   connection->destinationComputer);
        }
        printf("NULL\n");
    }
}

Vector *findConnections(ComputerNetworkGraph *graph, char *computerName1, char *computerName2) {
    Vector *connectionsArray = initVectorPtr(sizeof(Connection));

    for (int i = 0; i < graph->computesArray->arrayLength; ++i) {
        Computer *computer = (Computer *) getItemFromVector(*(graph->computesArray), i);

        if (strcmp(computerName1, computer->name) != 0
            && strcmp(computerName2, computer->name) != 0)
            continue;

        for (int j = 0; j < computer->connectionsList->listLength; ++j) {
            Connection *connection = (Connection *) getItemFromListByIdx(*(computer->connectionsList), j);
            if (strcmp(connection->destinationComputer, computerName2) == 0 ||
                strcmp(connection->destinationComputer, computerName1) == 0)
                addItemToVector(connectionsArray, connection);
        }

    }

    return connectionsArray;
}

