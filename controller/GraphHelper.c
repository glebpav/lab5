#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include "GraphHelper.h"
#include "../model/queue/MyQueue.h"


Vector *getColoredComputersArray(ComputerNetworkGraph graph) {
    Vector *coloredComputersArray = initVectorPtr(sizeof(ColoredComputer));
    for (int i = 0; i < graph.computesArray->arrayLength; ++i) {
        Computer *computerPtr = getItemFromVector(*(graph.computesArray), i);
        ColoredComputer coloredComputer = {0, computerPtr};
        addItemToVector(coloredComputersArray, &coloredComputer);
    }
    return coloredComputersArray;
}

Vector *getAvailableComputers(Vector coloredComputesArray, char *sourceComputerName) {

    Vector *availableComputers = initVectorPtr(sizeof(Computer *));
    Vector *availablePorts = initVectorPtr(sizeof(unsigned int));
    int startComputerIdx = -1;

    // color source computer
    for (int i = 0; i < coloredComputesArray.arrayLength; ++i) {
        ColoredComputer *coloredComputer = getItemFromVector(coloredComputesArray, i);
        if (strcmp(sourceComputerName, coloredComputer->computer->name) == 0) {
            for (int j = 0; j < coloredComputer->computer->connectionsList->listLength; ++j) {
                Connection *connection = getItemFromListByIdx(*(coloredComputer->computer->connectionsList), j);
                for (int k = 0; k < connection->accessedPorts->arrayLength; ++k) {
                    unsigned int *accessedPort = getItemFromVector(*(connection->accessedPorts), k);
                    addItemToVector(availablePorts, accessedPort);
                }
            }
            startComputerIdx = i;
            coloredComputer->color = 1;
            break;
        }
    }

    // make availablePorts array unique
    for (int i = 0; i < availablePorts->arrayLength; ++i) {
        unsigned int *accessedPort1 = getItemFromVector(*(availablePorts), i);
        for (int j = i + 1; j < availablePorts->arrayLength; ++j) {
            unsigned int *accessedPort2 = getItemFromVector(*(availablePorts), j);
            if (*accessedPort1 == *accessedPort2) {
                deleteItemFromVector(availablePorts, j);
                j -= 1;
            }
        }
    }

    if (startComputerIdx == -1) return NULL;

    printf("Available ports: ");
    for (int i = 0; i < availablePorts->arrayLength; ++i) {
        unsigned int *accessedPort1 = getItemFromVector(*(availablePorts), i);
        printf("%u ", *accessedPort1);
    }
    printf("\n");

    for (int portIdxCounter = 0; portIdxCounter < availablePorts->arrayLength; ++portIdxCounter) {
        unsigned int *accessedPort = getItemFromVector(*availablePorts, portIdxCounter);

        printf("Accessed port: %u\n", *accessedPort);

        struct queue* q = createQueue();
        enqueue(q, startComputerIdx);

        while (!isEmpty(q)) {

            printQueue(q);
            int currentVertex = dequeue(q);

            ColoredComputer *coloredComputer = getItemFromVector(coloredComputesArray, currentVertex);
            ListItem *temp = coloredComputer->computer->connectionsList->firstElement;

            while (temp) {
                Connection *connection = temp->data;

                bool isAccessedConnection = false;
                for (int i = 0; i < connection->accessedPorts->arrayLength; ++i) {
                    unsigned int *localeAccessedPort = getItemFromVector(*(connection->accessedPorts), i);
                    if (*localeAccessedPort == *accessedPort) {
                        isAccessedConnection = true;
                        break;
                    }
                }

                if (isAccessedConnection == false){
                    temp = temp->nextListItem;
                    continue;
                }

                Vector *destCompsIdxArray = initVectorPtr(sizeof(int));

                for (int i = 0; i < coloredComputesArray.arrayLength; ++i) {
                    ColoredComputer *coloredComputer1 = getItemFromVector(coloredComputesArray, i);
                    if (strcmp(connection->destinationComputer, coloredComputer1->computer->name) == 0) {
                        int localeIdx = i;
                        addItemToVector(destCompsIdxArray, &localeIdx);
                    }
                }

                for (int i = 0; i < destCompsIdxArray->arrayLength; ++i) {
                    int *compIdx = getItemFromVector(*(destCompsIdxArray), i);
                    ColoredComputer *coloredComputer1 = getItemFromVector(coloredComputesArray, *compIdx);

                    if (coloredComputer1->color == 0) {
                        coloredComputer1->color = 1;

                        if (coloredComputer1->computer->portIdx == *accessedPort){
                            printf("%s comp is available\n", coloredComputer1->computer->name);
                            addItemToVector(availableComputers, coloredComputer1->computer);
                        }

                        enqueue(q, *compIdx);
                    }
                }

                destroyVector(destCompsIdxArray);
                temp = temp->nextListItem;
            }
        }

        free(q);

        for (int i = 0; i < coloredComputesArray.arrayLength; ++i) {
            ColoredComputer *coloredComputer = getItemFromVector(coloredComputesArray, i);
            if (i != startComputerIdx) coloredComputer->color = 0;
        }
    }

    destroyVector(availablePorts);
    return NULL;
}
