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