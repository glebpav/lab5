#ifndef LAB4A_BINTREE_H
#define LAB4A_BINTREE_H

#include "../view/ResponsesHandler.h"
#include "../model/MyVector.h"

typedef struct Computer {
    char *hostName;
    unsigned portIdx;
} Computer;

typedef struct Connection {
    Vector *accessedPorts;
    unsigned transmissionDelay;
} Connection;

typedef struct ComputerNetworkGraph {
    Vector *computesArray;
    Vector *connectionsArray;
} ComputerNetworkGraph;

#endif //LAB4A_BINTREE_H
