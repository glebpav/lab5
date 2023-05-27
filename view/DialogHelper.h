#ifndef LAB4A_DIALOGHELPER_H
#define LAB4A_DIALOGHELPER_H

#include "../controller/ComputerNetworkGraph.h"
#include "CommandHelper.h"

const char *commandsMessages[] = {
        "Commit Network (graph) interactions",
        "Make network bypass",
        "Find the fastest way a - b",
        "Split to subnets",
        "Exit program =("
};

ResponsesTypes (*commandsPointers[])(ComputerNetworkGraph *) = {
        addNewItem,
        deleteItem,
        directBypassCommand,
        directBypassSpecial,
        searchItem,
        searchItemSpecial,
        printTree,
        printTreeInGraphViz,
        readTreeFromFile,
        exitProgram
};

const int countOfCommands = sizeof(commandsMessages) / sizeof(commandsMessages[0]);

int selectOperation(const char *commandsMessages[], int countOfMessages);

int getExitOperationIdx();


#endif //LAB4A_DIALOGHELPER_H
