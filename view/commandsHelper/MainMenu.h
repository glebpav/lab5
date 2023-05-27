#ifndef LAB4A_COMMANDHELPER_H
#define LAB4A_COMMANDHELPER_H

#include "../../ResponsesHandler.h"
#include "../../controller/ComputerNetworkGraph.h"

Responses openNetworkInteractionMenuD(ComputerNetworkGraph *graph);

Responses printGraphAdjacencyListD(ComputerNetworkGraph *graph);

Responses printMatrixD(ComputerNetworkGraph *graph);

Responses networkBypassD(ComputerNetworkGraph *graph);

Responses findShortestWayD(ComputerNetworkGraph *graph);

Responses splitToSubnetsD(ComputerNetworkGraph *graph);

Responses exitProgramD(ComputerNetworkGraph *graph);

Responses returnBackD(ComputerNetworkGraph *graph);

#endif //LAB4A_COMMANDHELPER_H
