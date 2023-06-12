#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ConnectionModifications.h"
#include "../../Utils.h"
#include "../../model/FileHelper.h"

Responses addConnectionD(ComputerNetworkGraph *graph) {

    char *computerName1;
    char *computerName2;
    unsigned transmissionDelay;

    if (!getSaveStingValue(&computerName1, "Please, input first computer NAME\n")
        || !getSaveStingValue(&computerName2, "Please, input second computer NAME\n")
        || !getSaveUnsignedValue(&transmissionDelay, "Please, input transmission DELAY\n"))
        return EXIT_RESPONSE;

    Responses response = addConnection(graph, computerName1, computerName2, transmissionDelay);
    if (isException(response)) throughException(response);

    return SUCCESS_RESPONSE;
}

Responses deleteConnectionD(ComputerNetworkGraph *graph) {

    int deletingConnectionIdx = -2;
    char *computerName1;
    char *computerName2;

    if (!getSaveStingValue(&computerName1, "Please, input first computer NAME\n")
        || !getSaveStingValue(&computerName2, "Please, input second computer NAME\n"))
        return EXIT_RESPONSE;

    Vector *connectionsArray = findConnections(graph, computerName1, computerName2);

    free(computerName1);
    free(computerName2);

    printf("found connections: %d\n", connectionsArray->arrayLength);

    if (connectionsArray->arrayLength == 0) {
        destroyVector(connectionsArray);
        return UNKNOWN_KEY_EXCEPTION;
    } else if (connectionsArray->arrayLength > 2) {
        bool inRangeStatement;

        printf("Found connections:\n");
        for (int i = 0; i < connectionsArray->arrayLength / 2; ++i) {
            Connection *connection1 = (Connection *) getItemFromVector(*connectionsArray, i);
            Connection *connection2 = (Connection *) getItemFromVector(*connectionsArray,
                                                                       i + connectionsArray->arrayLength / 2);

            // connection1->secondComputer = strdup(connection2->destinationComputer);
            // connection2->secondComputer = strdup(connection1->destinationComputer);

            printf(
                    "[%d] - (\"%s\" <=> \"%s\" | delay = %u)\n",
                    i,
                    connection1->destinationComputer,
                    connection2->destinationComputer,
                    connection1->transmissionDelay
            );
        }

        do {
            if (!getSaveIntValue(
                    &deletingConnectionIdx,
                    "Please, input IDX of deleting connection (-1 in case delete all)\n"
            )) {
                destroyVector(connectionsArray);
                return EXIT_RESPONSE;
            }

            inRangeStatement = deletingConnectionIdx >= -1 ||
                               deletingConnectionIdx < (connectionsArray->arrayLength / 2);

            if (!inRangeStatement) throughException(INPUT_NOT_IN_RANGE_EXCEPTION);

        } while (!inRangeStatement);

        if (deletingConnectionIdx != -1) {
            Vector *deletingConnectionsArray = initVectorPtr(sizeof(Connection));
            addItemToVector(deletingConnectionsArray, getItemFromVector(*connectionsArray, deletingConnectionIdx));
            addItemToVector(deletingConnectionsArray, getItemFromVector(*connectionsArray, deletingConnectionIdx +
                                                                                           connectionsArray->arrayLength /
                                                                                           2));
            deleteConnection(graph, deletingConnectionsArray);
            destroyVector(deletingConnectionsArray);
        } else {
            deleteConnection(graph, connectionsArray);
        }
    } else {
        Connection *connection1 = (Connection *) getItemFromVector(*connectionsArray, 0);
        Connection *connection2 = (Connection *) getItemFromVector(*connectionsArray, 1);
        // connection1->secondComputer = strdup(connection2->destinationComputer);
        // connection2->secondComputer = strdup(connection1->destinationComputer);
        deleteConnection(graph, connectionsArray);
    }

    destroyVector(connectionsArray);
    return SUCCESS_RESPONSE;
}

Responses changeConnectionDelayD(ComputerNetworkGraph *graph) {

    int deletingConnectionIdx = -2;
    char *computerName1;
    char *computerName2;

    if (!getSaveStingValue(&computerName1, "Please, input first computer NAME\n")
        || !getSaveStingValue(&computerName2, "Please, input second computer NAME\n"))
        return EXIT_RESPONSE;

    Vector *connectionsArray = findConnectionsPtr(graph, computerName1, computerName2);

    free(computerName1);
    free(computerName2);

    printf("found connections: %d\n", connectionsArray->arrayLength);

    if (connectionsArray->arrayLength == 0) {
        destroyVector(connectionsArray);
        return UNKNOWN_KEY_EXCEPTION;
    } else if (connectionsArray->arrayLength > 2) {
        bool inRangeStatement;

        printf("Found connections:\n");
        for (int i = 0; i < connectionsArray->arrayLength / 2; ++i) {
            Connection **connection1Ptr = (Connection **) (getItemFromVector(*connectionsArray, i));
            Connection **connection2Ptr = (Connection **) getItemFromVector(*connectionsArray,
                                                                            i + connectionsArray->arrayLength / 2);

            Connection *connection1 = *connection1Ptr;
            Connection *connection2 = *connection2Ptr;

            printf(
                    "[%d] - (\"%s\" <=> \"%s\" | delay = %u)\n",
                    i,
                    connection1->destinationComputer,
                    connection2->destinationComputer,
                    connection1->transmissionDelay
            );
        }

        do {
            if (!getSaveIntValue(
                    &deletingConnectionIdx,
                    "Please, input IDX of connection\n"
            )) {
                destroyVector(connectionsArray);
                return EXIT_RESPONSE;
            }

            inRangeStatement = deletingConnectionIdx >= 0 ||
                               deletingConnectionIdx < (connectionsArray->arrayLength / 2);

            if (!inRangeStatement) throughException(INPUT_NOT_IN_RANGE_EXCEPTION);

        } while (!inRangeStatement);

        Connection **selectedConnection1 = getItemFromVector(*connectionsArray, deletingConnectionIdx);
        Connection **selectedConnection2 = getItemFromVector(*connectionsArray, deletingConnectionIdx + connectionsArray->arrayLength / 2);

        unsigned int newDelay;
        if (!getSaveUnsignedValue(&newDelay, "Please, input new connection DELAY\n"))
            return EXIT_RESPONSE;

        changeConnectionDelay(graph, *selectedConnection1, newDelay);
        changeConnectionDelay(graph, *selectedConnection2, newDelay);

    } else {
        Connection **selectedConnection1 = getItemFromVector(*connectionsArray, 0);
        Connection **selectedConnection2 = getItemFromVector(*connectionsArray, 1);

        unsigned int newDelay;
        if (!getSaveUnsignedValue(&newDelay, "Please, input new connection DELAY\n"))
            return EXIT_RESPONSE;

        changeConnectionDelay(graph, *selectedConnection1, newDelay);
        changeConnectionDelay(graph, *selectedConnection2, newDelay);
    }

    destroyVector(connectionsArray);
    return SUCCESS_RESPONSE;
}

Responses addConnectionPortD(ComputerNetworkGraph *graph) {
    int deletingConnectionIdx = -2;
    char *computerName1;
    char *computerName2;

    if (!getSaveStingValue(&computerName1, "Please, input first computer NAME\n")
        || !getSaveStingValue(&computerName2, "Please, input second computer NAME\n"))
        return EXIT_RESPONSE;

    Vector *connectionsArray = findConnectionsPtr(graph, computerName1, computerName2);

    free(computerName1);
    free(computerName2);

    printf("found connections: %d\n", connectionsArray->arrayLength);

    if (connectionsArray->arrayLength == 0) {
        destroyVector(connectionsArray);
        return UNKNOWN_KEY_EXCEPTION;
    } else if (connectionsArray->arrayLength > 2) {
        bool inRangeStatement;

        printf("Found connections:\n");
        for (int i = 0; i < connectionsArray->arrayLength / 2; ++i) {
            Connection **connection1Ptr = (Connection **) (getItemFromVector(*connectionsArray, i));
            Connection **connection2Ptr = (Connection **) getItemFromVector(*connectionsArray,
                                                                            i + connectionsArray->arrayLength / 2);

            Connection *connection1 = *connection1Ptr;
            Connection *connection2 = *connection2Ptr;

            printf(
                    "[%d] - (\"%s\" <=> \"%s\" | delay = %u)\n",
                    i,
                    connection1->destinationComputer,
                    connection2->destinationComputer,
                    connection1->transmissionDelay
            );
        }

        do {
            if (!getSaveIntValue(
                    &deletingConnectionIdx,
                    "Please, input IDX of connection\n"
            )) {
                destroyVector(connectionsArray);
                return EXIT_RESPONSE;
            }

            inRangeStatement = deletingConnectionIdx >= 0 ||
                               deletingConnectionIdx < (connectionsArray->arrayLength / 2);

            if (!inRangeStatement) throughException(INPUT_NOT_IN_RANGE_EXCEPTION);

        } while (!inRangeStatement);

        Connection **selectedConnection1 = getItemFromVector(*connectionsArray, deletingConnectionIdx);
        Connection **selectedConnection2 = getItemFromVector(*connectionsArray, deletingConnectionIdx + connectionsArray->arrayLength / 2);

        unsigned int newPort;
        if (!getSaveUnsignedValue(&newPort, "Please, input new connection DELAY\n"))
            return EXIT_RESPONSE;

        addConnectionPortPtr(*selectedConnection1, newPort);
        addConnectionPortPtr(*selectedConnection2, newPort);

    } else {
        Connection **selectedConnection1 = getItemFromVector(*connectionsArray, 0);
        Connection **selectedConnection2 = getItemFromVector(*connectionsArray, 1);

        unsigned int newPort;
        if (!getSaveUnsignedValue(&newPort, "Please, input new connection DELAY\n"))
            return EXIT_RESPONSE;

        addConnectionPortPtr(*selectedConnection1, newPort);
        addConnectionPortPtr(*selectedConnection2, newPort);
    }

    destroyVector(connectionsArray);
    return SUCCESS_RESPONSE;
}

Responses deleteConnectionPortD(ComputerNetworkGraph *graph) {
    int deletingConnectionIdx = -2;
    char *computerName1;
    char *computerName2;

    if (!getSaveStingValue(&computerName1, "Please, input first computer NAME\n")
        || !getSaveStingValue(&computerName2, "Please, input second computer NAME\n"))
        return EXIT_RESPONSE;

    Vector *connectionsArray = findConnectionsPtr(graph, computerName1, computerName2);

    free(computerName1);
    free(computerName2);

    printf("found connections: %d\n", connectionsArray->arrayLength);

    if (connectionsArray->arrayLength == 0) {
        destroyVector(connectionsArray);
        return UNKNOWN_KEY_EXCEPTION;
    } else if (connectionsArray->arrayLength > 2) {
        bool inRangeStatement;

        printf("Found connections:\n");
        for (int i = 0; i < connectionsArray->arrayLength / 2; ++i) {
            Connection **connection1Ptr = (Connection **) (getItemFromVector(*connectionsArray, i));
            Connection **connection2Ptr = (Connection **) getItemFromVector(*connectionsArray,
                                                                            i + connectionsArray->arrayLength / 2);

            Connection *connection1 = *connection1Ptr;
            Connection *connection2 = *connection2Ptr;

            printf(
                    "[%d] - (\"%s\" <=> \"%s\" | delay = %u)\n",
                    i,
                    connection1->destinationComputer,
                    connection2->destinationComputer,
                    connection1->transmissionDelay
            );
        }

        do {
            if (!getSaveIntValue(
                    &deletingConnectionIdx,
                    "Please, input IDX of connection\n"
            )) {
                destroyVector(connectionsArray);
                return EXIT_RESPONSE;
            }

            inRangeStatement = deletingConnectionIdx >= 0 ||
                               deletingConnectionIdx < (connectionsArray->arrayLength / 2);

            if (!inRangeStatement) throughException(INPUT_NOT_IN_RANGE_EXCEPTION);

        } while (!inRangeStatement);

        Connection **selectedConnection1 = getItemFromVector(*connectionsArray, deletingConnectionIdx);
        Connection **selectedConnection2 = getItemFromVector(*connectionsArray, deletingConnectionIdx + connectionsArray->arrayLength / 2);

        unsigned int deletingPort;
        if (!getSaveUnsignedValue(&deletingPort, "Please, input deleting connection port\n"))
            return EXIT_RESPONSE;

        deleteConnectionPortPtr(*selectedConnection1, deletingPort);
        deleteConnectionPortPtr(*selectedConnection2, deletingPort);

    } else {
        Connection **selectedConnection1 = getItemFromVector(*connectionsArray, 0);
        Connection **selectedConnection2 = getItemFromVector(*connectionsArray, 1);

        unsigned int deletingPort;
        if (!getSaveUnsignedValue(&deletingPort, "Please, input deleting connection port\n"))
            return EXIT_RESPONSE;

        deleteConnectionPortPtr(*selectedConnection1, deletingPort);
        deleteConnectionPortPtr(*selectedConnection2, deletingPort);
    }

    destroyVector(connectionsArray);
    return SUCCESS_RESPONSE;
}

Responses readConnectionsFromFileD(ComputerNetworkGraph *graph) {
    char *fileName;
    Vector *inputStrArray = initVectorPtr(sizeof(char *));
    Vector *connectionsArray = initVectorPtr(sizeof(Connection));

    if (!getSaveStingValue(&fileName, "Please, input FILENAME\n"))
        return EXIT_RESPONSE;

    Responses response = readFile(fileName, inputStrArray);
    free(fileName);

    if (isException(response)) {
        throughException(response);
        return SUCCESS_RESPONSE;
    }

    char *a;
    for (int i = 0; i < inputStrArray->arrayLength; i += 1) {
        a = *((char **) getItemFromVector(*inputStrArray, i));
        printf("-%s\\n\n", a);
    }

    response = getConnectionsFromStr(inputStrArray, connectionsArray);
    if (isException(response)) {
        throughException(response);
        return SUCCESS_RESPONSE;
    }

    for (int i = 0; i < connectionsArray->arrayLength; ++i) {
        Connection *connection = getItemFromVector(*connectionsArray, i);
        addConnection(
                graph,
                connection->destinationComputer,
                connection->secondComputer,
                connection->transmissionDelay
        );
        for (int j = 0; j < connection->accessedPorts->arrayLength; ++j) {
            unsigned int portIdx = *((unsigned int *) getItemFromVector(*(connection->accessedPorts), j));
            addConnectionPort(graph, connection->destinationComputer, connection->secondComputer, portIdx);
        }
        destroyVector(connection->accessedPorts);
    }

    destroyVector(connectionsArray);
    destroyVector(inputStrArray);
    return SUCCESS_RESPONSE;
}

Responses returnBack2D(ComputerNetworkGraph *graph) {
    return RETURN_BACK_RESPONSE;
}