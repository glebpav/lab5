#ifndef LAB4B_DIALOGCONFIG1_H
#define LAB4B_DIALOGCONFIG1_H

#include "../MainMenu.h"

const char *mainCommandMsgs[] = {
        "Open network (graph) interactions menu",
        "Print network Adjacency list",
        "Print network matrix",
        "Make network bypass",
        "Find the fastest way a - b",
        "Split to subnets",
        "Exit program =("
};

Responses (*mainMenuCommandsPtr[])(ComputerNetworkGraph *) = {
        openNetworkInteractionMenuD,
        printGraphAdjacencyListD,
        printMatrixD,
        networkBypassD,
        findShortestWayD,
        splitToSubnetsD,
        exitProgramD,
};

const int countOfMainMsgs = sizeof(mainCommandMsgs) / sizeof(const char *);


#endif //LAB4B_DIALOGCONFIG1_H
