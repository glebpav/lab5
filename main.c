#include <stdlib.h>
#include "view/DialogHelper.h"
#include "view/commandsHelper/dialgConfigs/DialogConfig1.h"
#include "view/commandsHelper/ConnectionModifications.h"
#include "view/commandsHelper/ComputerModifications.h"

int main() {

    int operationIdx;
    Responses response;
    ComputerNetworkGraph network = initComputerNetworkGraph();

    if (readComputersFromFileD(&network) == EXIT_RESPONSE
        || readConnectionsFromFileD(&network) == EXIT_RESPONSE) {
        destroyComputerNetworkGraph(&network);
        return 0;
    }

    do {
        operationIdx = selectOperation(mainCommandMsgs, countOfMainMsgs);
        response = mainMenuCommandsPtr[operationIdx](&network);
    } while (operationIdx != getExitOperationIdx() && !isException(response));

    destroyComputerNetworkGraph(&network);

    return 0;
}
