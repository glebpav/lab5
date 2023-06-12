#include "../ResponsesHandler.h"
#include "../model/MyVector.h"
#include "../model/MyList.h"

#ifndef LAB4B_COMPGRAPH
#define LAB4B_COMPGRAPH

typedef struct Connection {
    unsigned int transmissionDelay;
    char *destinationComputer;
    Vector *accessedPorts; // <unsigned int> array
    // sub-field
    char *secondComputer;
} Connection;

typedef struct Computer {
    char *name;
    unsigned portIdx;
    List *connectionsList; // <Connection> list
} Computer;

typedef struct ComputerNetworkGraph {
    Vector *computesArray;
} ComputerNetworkGraph;


ComputerNetworkGraph initComputerNetworkGraph();

void destroyComputerNetworkGraph(ComputerNetworkGraph *graph);

Responses addComputer(ComputerNetworkGraph *graph, char *computerName, unsigned portIdx);

Responses addConnection(ComputerNetworkGraph *graph, char *computerName1, char *computerName2, unsigned int delay);

Responses deleteComputer(ComputerNetworkGraph *graph, char *computerName);

Responses deleteConnection(ComputerNetworkGraph *graph, Vector *deletingConnectionsArray);

Responses changeComputerName(ComputerNetworkGraph *graph, char *oldComputerName, char *newComputerName);

Responses changeComputerPortIdx(ComputerNetworkGraph *graph, char *computerName, unsigned newPortIdx);

Responses changeConnectionDelay(ComputerNetworkGraph *graph, Connection *connection, unsigned newDelay);

Responses addConnectionPort(ComputerNetworkGraph *graph, char *computerName1, char *computerName2, unsigned newPort);

Responses addConnectionPortPtr(Connection *connection, unsigned int connectionPort);

Responses deleteConnectionPort(ComputerNetworkGraph *graph, char *computerName1, char *computerName2, unsigned deletingPortIdx);

Responses deleteConnectionPortPtr(Connection *connection, unsigned int deletingPort);

Responses printMatrix(ComputerNetworkGraph *graph);

Vector *findConnections(ComputerNetworkGraph *graph, char *computer1, char *computer2);

Vector *findConnectionsPtr(ComputerNetworkGraph *graph, char *computer1, char *computer2);

void printAdjacencyList(ComputerNetworkGraph *graph);

#endif
