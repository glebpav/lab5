#ifndef LAB4B_CONNECTIONMODIFICATIONS_H
#define LAB4B_CONNECTIONMODIFICATIONS_H

#include "../../controller/ComputerNetworkGraph.h"

Responses addConnectionD(ComputerNetworkGraph *graph);

Responses deleteConnectionD(ComputerNetworkGraph *graph);

Responses changeConnectionDelayD(ComputerNetworkGraph *graph);

Responses addConnectionPortD(ComputerNetworkGraph *graph);

Responses deleteConnectionPortD(ComputerNetworkGraph *graph);

Responses returnBack2D(ComputerNetworkGraph *graph);

Responses (*ConnectionMdfCommandsPtr[])(ComputerNetworkGraph *) = {
        addConnectionD,
        deleteConnectionD,
        changeConnectionDelayD,
        addConnectionPortD,
        deleteConnectionPortD,
        returnBack2D
};

const char *connectionModificationsMsgs[] = {
        "Add connection",
        "Delete connection",
        "Change connection delay",
        "Add connection port",
        "Delete connection port",
        "Return back"
};

const int countOfConnectionMdfMsgs = sizeof (connectionModificationsMsgs) / sizeof(const char *);

#endif //LAB4B_CONNECTIONMODIFICATIONS_H
