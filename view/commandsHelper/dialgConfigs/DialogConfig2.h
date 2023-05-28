#ifndef LAB4B_DIALOGCONFIG2_H
#define LAB4B_DIALOGCONFIG2_H

#include "../../../controller/ComputerNetworkGraph.h"
#include "../GraphInteraction.h"

const char *graphInteractionsMsgs[] = {
        "Modify computer",
        "Modify connection",
        "Return back"
};

Responses (*graphIaCommandsPtr[])(ComputerNetworkGraph *) = {
        openComputerModificationsMenuD,
        openConnectionModificationMenuD,
        returnBack1D
};

const int countOfGraphInteractionsMsgs = sizeof(graphInteractionsMsgs) / sizeof(const char *);


#endif //LAB4B_DIALOGCONFIG2_H
