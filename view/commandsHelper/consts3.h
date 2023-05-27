#ifndef LAB4B_CONSTS3_H
#define LAB4B_CONSTS3_H

#include "../../controller/ComputerNetworkGraph.h"
#include "ComputerModifications.h"

Responses (*ComputerMdfCommandsPtr[])(ComputerNetworkGraph *) = {
        addComputerD,
        deleteComputerD,
        changeComputerNameD,
        changeComputerPortIdxD,
        returnBack3D
};

const char *computerModificationsMsgs[] = {
        "Add computer",
        "Delete computer",
        "Change computer name",
        "Change computer port idx",
        "Return back"
};

const int countOfComputerMdfMsgs = sizeof(computerModificationsMsgs) / sizeof(const char *);


#endif //LAB4B_CONSTS3_H
