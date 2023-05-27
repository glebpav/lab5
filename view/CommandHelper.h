#ifndef LAB4A_COMMANDHELPER_H
#define LAB4A_COMMANDHELPER_H

#include "ResponsesHandler.h"
#include "../controller/ComputerNetworkGraph.h"

ResponsesTypes addNewItem(ScapeGoatTree *);

ResponsesTypes deleteItem(ScapeGoatTree *);

ResponsesTypes directBypassCommand(ScapeGoatTree *);

ResponsesTypes directBypassSpecial(ScapeGoatTree *);

ResponsesTypes searchItem(ScapeGoatTree *);

ResponsesTypes searchItemSpecial(ScapeGoatTree *);

ResponsesTypes printTree(ScapeGoatTree *);

ResponsesTypes printTreeInGraphViz(ScapeGoatTree *);

ResponsesTypes readTreeFromFile(ScapeGoatTree *);

ResponsesTypes exitProgram(ScapeGoatTree *);

#endif //LAB4A_COMMANDHELPER_H
