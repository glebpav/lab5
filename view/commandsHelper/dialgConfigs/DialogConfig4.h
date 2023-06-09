#ifndef LAB4B_DIALOGCONFIG4_H
#define LAB4B_DIALOGCONFIG4_H

#include "../ConnectionModifications.h"

Responses (*connectionMdfCommandsPtr[])(ComputerNetworkGraph *) = {
        addConnectionD,
        deleteConnectionD,
        changeConnectionDelayD,
        addConnectionPortD,
        deleteConnectionPortD,
        readConnectionsFromFileD,
        returnBack2D
};

const char *connectionModificationsMsgs[] = {
        "Add connection",
        "Delete connection",
        "Change connection delay",
        "Add connection port",
        "Delete connection port",
        "Read connections from file",
        "Return back"
};

const int countOfConnectionMdfMsgs = sizeof (connectionModificationsMsgs) / sizeof(const char *);


#endif //LAB4B_DIALOGCONFIG4_H
