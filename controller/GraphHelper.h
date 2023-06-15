#ifndef LAB5_GRAPHHELPER_H
#define LAB5_GRAPHHELPER_H

#include "ComputerNetworkGraph.h"

typedef struct ColoredComputer {
    int color;
    Computer *computer;
} ColoredComputer;

Vector *getColoredComputersArray(ComputerNetworkGraph graph);

Vector *getAvailableComputers(Vector coloredComputesArray, char *sourceComputerName);

#endif //LAB5_GRAPHHELPER_H
