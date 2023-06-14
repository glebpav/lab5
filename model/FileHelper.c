#include <stdio.h>
#include "errno.h"
#include "FileHelper.h"
#include "string.h"
#include "stdlib.h"
#include "../controller/ComputerNetworkGraph.h"
#include "../Utils.h"

Responses readFile(char *fileName, Vector *outputStrVector) {
    FILE *fp;

    char *prefix = strdup("files/");
    char *filePath = calloc(strlen(prefix) + strlen(fileName) + 1, sizeof(char));
    filePath = strcat(filePath, prefix);
    filePath = strcat(filePath, fileName);

    free(prefix);
    // printf("prefix: %s\n", filePath);
    if ((fp = fopen(filePath, "r+")) == NULL) {
        free(filePath);
        return NO_SUCH_FILE_EXCEPTION;
    }
    free(filePath);

    char *item = calloc(128, sizeof(char));

    while (1) {
        int ret = fscanf(fp, "%s", item);
        if (ret == 1) {
            char *itemPtr = strdup(item);
            // printf("-%s\\n\n", itemPtr);
            addItemToVector(outputStrVector, &itemPtr);
            // memset(item, 0, 128 *sizeof(char));
        } else if (errno != 0) {
            perror("scanf:");
            break;
        } else if (ret == EOF) {
            break;
        } else {
            puts("No or partial match.\n");
            break;
        }
    }
    if (feof(fp)) {
        fclose(fp);
    }
    free(item);
    return SUCCESS_RESPONSE;
}

Responses getComputesFromStr(Vector *stringArray, Vector *computersArray) {
    char *computerName;
    char *portIdx;

    if (stringArray->arrayLength % 2 == 1) return INCORRECT_FILE_FORMAT_EXCEPTION;

    for (int i = 0; i < stringArray->arrayLength; i += 2) {
        computerName = *((char **) getItemFromVector(*stringArray, i));
        portIdx = *((char **) getItemFromVector(*stringArray, i + 1));
        Computer computer = {.name = computerName, .connectionsList = NULL};
        if (isUnsignedNum(portIdx)) computer.portIdx = atoi(portIdx);
        else computer.portIdx = 0;
        addItemToVector(computersArray, &computer);

        if (portIdx != NULL) {
            free(portIdx);
        }
    }

    return SUCCESS_RESPONSE;
}

Responses getConnectionsFromStr(Vector *stringArray, Vector *connectionsArray) {
    char *computerName1;
    char *computerName2;
    char *transmissionDelay;
    char *accessedPorts;

    if (stringArray->arrayLength % 4 != 0) return INCORRECT_FILE_FORMAT_EXCEPTION;

    for (int i = 0; i < stringArray->arrayLength; i += 4) {
        computerName1 = *(char **) (getItemFromVector(*stringArray, i));
        computerName2 = *(char **) (getItemFromVector(*stringArray, i + 1));
        transmissionDelay = *(char **) (getItemFromVector(*stringArray, i + 2));
        accessedPorts = *(char **)(getItemFromVector(*stringArray, i + 3));
        Vector *portsArray = initVectorPtr(sizeof(unsigned int));

        char *port = strtok(accessedPorts, "/");
        while (port != NULL) {
            unsigned int portIdx = atoi(port);
            addItemToVector(portsArray, &portIdx);
            port = strtok(NULL, "/");
        }

        Connection connection1 = {
                .destinationComputer = computerName1,
                .secondComputer = computerName2,
                .accessedPorts = portsArray
        };

        if (isUnsignedNum(transmissionDelay)) {
            connection1.transmissionDelay = atoi(transmissionDelay);
        } else {
            connection1.transmissionDelay = 0;
        }

        free(accessedPorts);
        free(transmissionDelay);
        // destroyVector(portsArray);
        addItemToVector(connectionsArray, &connection1);
    }

    return SUCCESS_RESPONSE;
}
