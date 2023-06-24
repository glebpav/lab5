#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include "GraphHelper.h"
#include "limits.h"
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

Vector *getColoredMarkedComputersArray(ComputerNetworkGraph graph) {
    Vector *coloredComputersArray = initVectorPtr(sizeof(ColoredMarkedComputer));
    for (int i = 0; i < graph.computesArray->arrayLength; ++i) {
        Computer *computerPtr = getItemFromVector(*(graph.computesArray), i);
        // ColoredMarkedComputer coloredComputer = {0, computerPtr};
        // addItemToVector(coloredComputersArray, &coloredComputer);
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

    if (startComputerIdx == -1) {
        destroyVector(availablePorts);
        destroyVector(availableComputers);
        return NULL;
    }

    printf("Available ports: ");
    for (int i = 0; i < availablePorts->arrayLength; ++i) {
        unsigned int *accessedPort1 = getItemFromVector(*(availablePorts), i);
        printf("%u ", *accessedPort1);
    }
    printf("\n");

    for (int portIdxCounter = 0; portIdxCounter < availablePorts->arrayLength; ++portIdxCounter) {
        unsigned int *accessedPort = getItemFromVector(*availablePorts, portIdxCounter);

        printf("Accessed port: %u\n", *accessedPort);

        struct Queue *q = createQueue();
        enqueue(q, startComputerIdx);

        while (!isEmpty(q)) {

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

                if (isAccessedConnection == false) {
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

                        if (coloredComputer1->computer->portIdx == *accessedPort) {
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
    return availableComputers;
}

Vector *getColoredConnectionsArray(ComputerNetworkGraph graph) {
    Vector *coloredConnectionsArray = initVectorPtr(sizeof(SubConnection));
    for (int i = 0; i < graph.computesArray->arrayLength; ++i) {
        Computer *computerPtr = getItemFromVector(*(graph.computesArray), i);
        for (int j = 0; j < computerPtr->connectionsList->listLength; ++j) {
            Connection *connectionPtr = getItemFromListByIdx(*(computerPtr->connectionsList), j);

            int destinationComputerIdx = -1;
            for (int k = 0; k < graph.computesArray->arrayLength; ++k) {
                Computer *computerLocale = getItemFromVector(*(graph.computesArray), k);
                if (strcmp(computerLocale->name, connectionPtr->destinationComputer) == 0) {
                    destinationComputerIdx = k;
                    break;
                }
            }
            if (destinationComputerIdx == -1) {
                destroyVector(coloredConnectionsArray);
                return NULL;
            }

            SubConnection coloredConnection = {i, destinationComputerIdx, connectionPtr};
            addItemToVector(coloredConnectionsArray, &coloredConnection);
        }
    }
    return coloredConnectionsArray;
}

int getShortestColoredConnectionIdx(Vector *coloredConnectionsArray) {
    /*int minDelay;
    int minDelayConnectionIdx;
    for (int i = 0; i < coloredConnectionsArray->arrayLength; ++i) {
        ColoredConnection *coloredConnectionPtr = getItemFromVector(*coloredConnectionsArray, i);
        if (coloredConnectionPtr->color == 0 && minD)
    }*/
}

Vector *
getShortestWay(int sourceComputerIdx, int destinationComputerIdx, Vector *computersArray, Vector *connectionsArray) {

    unsigned int countOfComputers = computersArray->arrayLength;
    unsigned int connectionsMatrix[countOfComputers][countOfComputers];
    unsigned int minDists[countOfComputers];
    int colors[countOfComputers];

    Computer *destComputerPtr = getItemFromVector(*computersArray, destinationComputerIdx);
    unsigned int accessedPort = destComputerPtr->portIdx;

    for (int i = 0; i < countOfComputers; ++i) {
        minDists[i] = INT_MAX;
        colors[i] = 1;
        for (int j = 0; j < countOfComputers; ++j) {
            connectionsMatrix[i][j] = 0;
            connectionsMatrix[j][i] = 0;
        }
    }
    minDists[sourceComputerIdx] = 0;

    for (int i = 0; i < connectionsArray->arrayLength; ++i) {
        SubConnection *connection = getItemFromVector(*connectionsArray, i);

        bool isAccessedPort = false;
        for (int j = 0; j < connection->connection->accessedPorts->arrayLength; ++j) {
            unsigned int *localeAccessedPort = getItemFromVector(*(connection->connection->accessedPorts), j);
            // printf("accessedPort: %u / locale port: %u / %d\n", accessedPort, *localeAccessedPort, *localeAccessedPort == accessedPort);
            if (*localeAccessedPort == accessedPort) {
                isAccessedPort = true;
                break;
            }
        }

        if (isAccessedPort && (connectionsMatrix[connection->comp1Idx][connection->comp2Idx] == 0 ||
                               connectionsMatrix[connection->comp1Idx][connection->comp2Idx] >
                               connection->connection->transmissionDelay)) {
            connectionsMatrix[connection->comp1Idx][connection->comp2Idx] = connection->connection->transmissionDelay;
            connectionsMatrix[connection->comp2Idx][connection->comp1Idx] = connection->connection->transmissionDelay;
        }
    }

    /*for (int i = 0; i < countOfComputers; ++i) {
        for (int j = 0; j < countOfComputers; ++j) {
            printf("%4d", connectionsMatrix[j][i]);
            // connectionsMatrix[j][i] = 0;
        }
        printf("\n");
    }*/

    unsigned int idxOfMinComputer;
    unsigned int min;
    unsigned int temp;

    do {
        idxOfMinComputer = INT_MAX;
        min = INT_MAX;
        for (int i = 0; i < countOfComputers; i++) {
            if ((colors[i] == 1) && (minDists[i] < min)) {
                min = minDists[i];
                idxOfMinComputer = i;
            }
        }

        if (idxOfMinComputer != INT_MAX) {
            for (int i = 0; i < countOfComputers; i++) {
                if (connectionsMatrix[idxOfMinComputer][i] > 0) {
                    temp = min + connectionsMatrix[idxOfMinComputer][i];
                    if (temp < minDists[i]) {
                        minDists[i] = temp;
                    }
                }
            }
            colors[idxOfMinComputer] = 0;
        }
    } while (idxOfMinComputer < INT_MAX);

    if (minDists[destinationComputerIdx] == INT_MAX) {
        printf("NO WAAAAAAY ((((\n");
        return NULL;
    }

    int ver[countOfComputers];
    int end = destinationComputerIdx;
    ver[0] = end;
    int k = 1;
    unsigned int weight = minDists[end];

    while (end != sourceComputerIdx) {
        for (int i = 0; i < countOfComputers; i++) {
            if (connectionsMatrix[i][end] != 0) {
                int temp1 = weight - connectionsMatrix[i][end];
                if (temp1 == minDists[i]) {
                    weight = temp1;
                    end = i;
                    ver[k] = i;
                    k++;
                }
            }
        }
    }

    Vector *outWay = initVectorPtr(sizeof(unsigned int));
    printf("The shortest way: ");
    for (int i = k - 1; i >= 0; i--) {
        Computer *computer = getItemFromVector(*computersArray, ver[i]);
        int computerIdx = ver[i];
        addItemToVector(outWay, &computerIdx);
        printf("%s ", computer->name);
    }

    printf("( sum transmission delay = %u )\n", minDists[destinationComputerIdx]);

    return outWay;
}

void dfs(bool **used, Vector *g[], Vector *comp, int v) {
    (*used)[v] = true;

    addItemToVector(comp, &v);
    for (int q = 0; q < g[v]->arrayLength; ++q) {
        int *element = getItemFromVector(*(g[v]), q);
        int to = *element;
        if (!(*used)[to])
            dfs(used, g, comp, to);
    }
}

void printComps(ComputerNetworkGraph graph, Vector *computersArray) {
    unsigned int n = computersArray->arrayLength;
    Vector *g[computersArray->arrayLength];

    for (int i = 0; i < computersArray->arrayLength; ++i) {
        g[i] = initVectorPtr(sizeof(int));
        Computer *computer = getItemFromVector(*computersArray, i);
        // if (computer->connectionsList)
        for (int j = 0; j < computer->connectionsList->listLength; ++j) {
            Connection *connection = getItemFromListByIdx(*(computer->connectionsList), j);
            int idx = getComputerIdx(graph, connection->destinationComputer);
            bool isUnique = true;
            for (int k = 0; k < g[i]->arrayLength; ++k) {
                int *localeIdx = getItemFromVector(*(g[i]), k);
                if (*localeIdx == idx) {
                    isUnique = false;
                    break;
                }
            }
            if (isUnique) addItemToVector(g[i], &idx);
        }
    }

    /*for (int i = 0; i < computersArray->arrayLength; ++i) {
        for (int j = 0; j < g[i]->arrayLength; ++j) {
            int *connection = getItemFromVector(*(g[i]), j);
            printf("%d ", *connection);
        }
        printf("\n");
    }*/

    // bool used[computersArray->arrayLength];
    bool ** used = calloc(1, sizeof(bool *));
    *used = calloc(computersArray->arrayLength, sizeof(int));
    Vector *comp = initVectorPtr(sizeof(int));

    for (int i = 0; i < n; ++i) (*used)[i] = false;

    for (int i = 0; i < n; ++i) {
        if (!(*used)[i]) {
            printf("\n");
            clearVector(comp);
            dfs(used, g, comp, i);
            printf("Component:");
            for (int j = 0; j < comp->arrayLength; ++j) {
                int *compIdx = getItemFromVector(*comp, j);
                Computer *computer = getItemFromVector(*computersArray, *compIdx);
                printf(" %s", computer->name);
            }
            printf("\n");
        }
    }

    for (int i = 0; i < computersArray->arrayLength; ++i) {
        destroyVector(g[i]);
    }
    destroyVector(comp);

    free(*used);
    free(used);
}