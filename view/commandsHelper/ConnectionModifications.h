#ifndef LAB4B_CONNECTIONMODIFICATIONS_H
#define LAB4B_CONNECTIONMODIFICATIONS_H

#include "../../controller/ComputerNetworkGraph.h"

Responses addConnectionD(ComputerNetworkGraph *graph);

Responses deleteConnectionD(ComputerNetworkGraph *graph);

Responses changeConnectionDelayD(ComputerNetworkGraph *graph);

Responses addConnectionPortD(ComputerNetworkGraph *graph);

Responses deleteConnectionPortD(ComputerNetworkGraph *graph);

Responses readConnectionsFromFileD(ComputerNetworkGraph *graph);

Responses returnBack2D(ComputerNetworkGraph *graph);


#endif //LAB4B_CONNECTIONMODIFICATIONS_H
