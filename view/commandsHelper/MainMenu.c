#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../../Utils.h"
#include "../../model/FileHelper.h"
#include "../GrpahVisHelper.h"
#include "../DialogHelper.h"
#include "GraphInteraction.h"
#include "dialgConfigs/DialogConfig2.h"
#include "../../controller/GraphHelper.h"

Responses openNetworkInteractionMenuD(ComputerNetworkGraph *graph) {
    int operationIdx;
    Responses response;

    do {
        operationIdx = selectOperation(
                graphInteractionsMsgs,
                countOfGraphInteractionsMsgs
        );
        response = graphIaCommandsPtr[operationIdx](graph);
    } while (response != RETURN_BACK_RESPONSE && response != EXIT_RESPONSE);

    return response;
}

Responses printGraphAdjacencyListD(ComputerNetworkGraph *graph) {
    printAdjacencyList(graph);
    return SUCCESS_RESPONSE;
}

Responses printMatrixD(ComputerNetworkGraph *graph) {
    return SUCCESS_RESPONSE;
}

Responses networkBypassD(ComputerNetworkGraph *graph) {

    char *sourceComputerName;

    if (getSaveStingValue(&sourceComputerName, "Please, input source computer NAME\n") == EXIT_RESPONSE)
        return EXIT_RESPONSE;

    // BFS

    Vector *coloredComputerArray = getColoredComputersArray(*graph);
    Vector *availableComputersArray = getAvailableComputers(*coloredComputerArray, sourceComputerName);

    free(sourceComputerName);
    if (coloredComputerArray != NULL) destroyVector(coloredComputerArray);
    if (availableComputersArray != NULL) destroyVector(availableComputersArray);

    return SUCCESS_RESPONSE;
}

Responses findShortestWayD(ComputerNetworkGraph *graph) {
    return SUCCESS_RESPONSE;
}

Responses splitToSubnetsD(ComputerNetworkGraph *graph) {
    return SUCCESS_RESPONSE;
}

Responses exitProgramD(ComputerNetworkGraph *graph) {
    return SUCCESS_RESPONSE;
}

Responses returnBackD(ComputerNetworkGraph *graph) {
    return RETURN_BACK_RESPONSE;
}