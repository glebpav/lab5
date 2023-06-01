#ifndef LAB4B_DIALOGCONFIG3_H
#define LAB4B_DIALOGCONFIG3_H

#include "../ComputerModifications.h"

Responses (*computerMdfCommandsPtr[])(ComputerNetworkGraph *) = {
        addComputerD,
        deleteComputerD,
        changeComputerNameD,
        changeComputerPortIdxD,
        readComputersFromFileD,
        returnBack3D
};

const char *computerModificationsMsgs[] = {
        "Add computer",
        "Delete computer",
        "Change computer name",
        "Change computer port idx",
        "Read computers from file",
        "Return back"
};

const int countOfComputerMdfMsgs = sizeof(computerModificationsMsgs) / sizeof(const char *);


#endif //LAB4B_DIALOGCONFIG3_H
