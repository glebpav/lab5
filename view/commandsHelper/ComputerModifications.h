#ifndef LAB4B_COMPUTERMODIFICATIONS_H
#define LAB4B_COMPUTERMODIFICATIONS_H

#include "../../controller/ComputerNetworkGraph.h"

Responses addComputerD(ComputerNetworkGraph *graph);

Responses deleteComputerD(ComputerNetworkGraph *graph);

Responses changeComputerNameD(ComputerNetworkGraph *graph);

Responses changeComputerPortIdxD(ComputerNetworkGraph *graph);

Responses readComputersFromFileD(ComputerNetworkGraph *graph);

Responses returnBack3D(ComputerNetworkGraph *graph);


#endif //LAB4B_COMPUTERMODIFICATIONS_H
