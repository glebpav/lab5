#include "GraphInteraction.h"
#include "../DialogHelper.h"
#include "dialgConfigs/DialogConfig3.h"
#include "dialgConfigs/DialogConfig4.h"

Responses openComputerModificationsMenuD(ComputerNetworkGraph *graph){
    int operationIdx;
    Responses response;

    do {
        operationIdx = selectOperation(
                computerModificationsMsgs,
                countOfComputerMdfMsgs
        );
        response = computerMdfCommandsPtr[operationIdx](graph);
    } while (response != RETURN_BACK_RESPONSE);

    return SUCCESS_RESPONSE;
}

Responses openConnectionModificationMenuD(ComputerNetworkGraph *graph){
    int operationIdx;
    Responses response;

    do {
        operationIdx = selectOperation(
                connectionModificationsMsgs,
                countOfConnectionMdfMsgs
        );
        response = connectionMdfCommandsPtr[operationIdx](graph);
    } while (response != RETURN_BACK_RESPONSE);

    return SUCCESS_RESPONSE;
}

Responses returnBack1D(ComputerNetworkGraph *graph) {
    return RETURN_BACK_RESPONSE;
}