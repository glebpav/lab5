#ifndef LAB5_GRAPHHELPER_H
#define LAB5_GRAPHHELPER_H

#include "ComputerNetworkGraph.h"

typedef struct ColoredComputer {
    int color;
    Computer *computer;
} ColoredComputer;

typedef struct SubConnection {
    int comp1Idx;
    int comp2Idx;
    Connection *connection;
} SubConnection;

typedef struct ColoredMarkedComputer {
    int color;
    int mark;
    Computer *computer;
} ColoredMarkedComputer;

Vector *getColoredComputersArray(ComputerNetworkGraph graph);

Vector *getColoredConnectionsArray(ComputerNetworkGraph graph);

Vector *getAvailableComputers(Vector coloredComputesArray, char *sourceComputerName);

// Vector *getShortestWay(int sourceComputerIdx, int destinationComputerIdx, Vector *coloredConnectionsArray);

Vector *getShortestWay(int sourceComputerIdx, int destinationComputerIdx, Vector *computersArray, Vector *connectionsArray);

void printComps(ComputerNetworkGraph graph, Vector *computersArray);

#endif //LAB5_GRAPHHELPER_H
