#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "MainMenu.h"
#include "../../Utils.h"
#include "../../model/FileHelper.h"
#include "../GrpahVisHelper.h"
#include "../DialogHelper.h"
#include "GraphInteraction.h"
#include "dialgConfigs/DialogConfig2.h"

Responses openNetworkInteractionMenuD(ComputerNetworkGraph *graph) {
    int operationIdx;
    Responses response;

    do {
        operationIdx = selectOperation(
                graphInteractionsMsgs,
                countOfGraphInteractionsMsgs
        );
        response = graphIaCommandsPtr[operationIdx](graph);
    } while (response != RETURN_BACK_RESPONSE);

    return SUCCESS_RESPONSE;
}

Responses printGraphAdjacencyListD(ComputerNetworkGraph *graph) {
    return SUCCESS_RESPONSE;
}

Responses printMatrixD(ComputerNetworkGraph *graph) {
    return SUCCESS_RESPONSE;
}

Responses networkBypassD(ComputerNetworkGraph *graph) {
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