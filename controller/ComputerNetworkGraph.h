#include "../ResponsesHandler.h"
#include "../model/MyVector.h"

#ifndef LAB4B_COMPGRAPH
#define LAB4B_COMPGRAPH

typedef struct Computer {
    char *name;
    unsigned portIdx;
} Computer;

typedef struct Connection {
    char *computerName1;
    char *computerName2;
    Vector *accessedPorts;
    unsigned int transmissionDelay;
} Connection;

typedef struct ComputerNetworkGraph {
    Vector *computesArray;
    Vector *connectionsArray;
} ComputerNetworkGraph;


ComputerNetworkGraph initComputerNetworkGraph();

void destroyComputerNetworkGraph(ComputerNetworkGraph *graph);

Responses addComputer(ComputerNetworkGraph *graph, char *computerName, unsigned portIdx);

Responses addConnection(ComputerNetworkGraph *graph, char *computerName1, char *computerName2);

Responses deleteComputer(ComputerNetworkGraph *graph, char *computerName);

Responses deleteConnection(ComputerNetworkGraph *graph, char *computerName1, char *computerName2);

Responses changeComputerName(ComputerNetworkGraph *graph, char *oldComputerName, char *newComputerName);

Responses changeComputerPortIdx(ComputerNetworkGraph *graph, char *computerName, unsigned newPortIdx);

Responses changeConnectionDelay(ComputerNetworkGraph *graph, char *computerName1, char *computerName2, unsigned newDelay);

Responses addConnectionPort(ComputerNetworkGraph *graph, char *computerName1, char *computerName2, unsigned newPort);

Responses deleteConnectionPort(ComputerNetworkGraph *graph, char *computerName1, char *computerName2, unsigned deletingPortIdx);

Responses printMatrix(ComputerNetworkGraph *graph);

Responses printAdjacencyList(ComputerNetworkGraph *graph);

#endif
