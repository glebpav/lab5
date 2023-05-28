#include "view/DialogHelper.h"
#include "view/commandsHelper/dialgConfigs/DialogConfig1.h"

int main() {

    int operationIdx;
    Responses response;
    ComputerNetworkGraph network = initComputerNetworkGraph();

    do {
        operationIdx = selectOperation(mainCommandMsgs, countOfMainMsgs);
        response = mainMenuCommandsPtr[operationIdx](&network);
    } while (operationIdx != getExitOperationIdx() && !isException(response));

    destroyComputerNetworkGraph(&network);

    return 0;
}
