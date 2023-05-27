#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "CommandHelper.h"
#include "../Utils.h"
#include "../model/FileHelper.h"
#include "GrpahVisHelper.h"

void printTreeLevel(Node *treeRoot, int level) {
    if (treeRoot != NULL) {
        printTreeLevel(treeRoot->left, level + 1);
        for (int i = 0; i < level; i++) printf("   ");
        // printf("%p; ", treeRoot);
        printf("%d\n", treeRoot->key);
        printTreeLevel(treeRoot->right, level + 1);
    }
}

ResponsesTypes addNewItem(ScapeGoatTree *tree) {
    int newKey;
    char *newValue;

    if (!getSaveIntValue(&newKey, "Please, input new KEY\n"))
        return EXIT_RESPONSE;
    if (!getSaveStingValue(&newValue, "Please, input new VALUE\n"))
        return EXIT_RESPONSE;

    clock_t startTime = clock();
    insertScapeGoat(tree, newKey, newValue);
    clock_t spendTime = (clock() - startTime) * 1000 / CLOCKS_PER_SEC;
    printf("Spend: %ld ms\n", spendTime);

    free(newValue);

    return SUCCESS_RESPONSE;
}

ResponsesTypes deleteItem(ScapeGoatTree *tree) {

    int deletingNodeKey;
    if (!getSaveIntValue(&deletingNodeKey, "Please, input KEY of deleting Node\n"))
        return EXIT_RESPONSE;

    clock_t startTime = clock();
    deleteNode(tree, deletingNodeKey);
    clock_t spendTime = (clock() - startTime) * 1000 / CLOCKS_PER_SEC;
    printf("Spend: %ld ms\n", spendTime);

    return SUCCESS_RESPONSE;
}

ResponsesTypes directBypassCommand(ScapeGoatTree *tree) {
    clock_t startTime = clock();
    printInorder(*tree);
    clock_t spendTime = (clock() - startTime) * 1000 / CLOCKS_PER_SEC;
    printf("Spend: %ld ms\n", spendTime);
    return SUCCESS_RESPONSE;
}

ResponsesTypes directBypassSpecial(ScapeGoatTree *tree) {

    int countOfNums;
    if (!getSaveIntValue(&countOfNums, "Please, input COUNT of numbers\n"))
        return EXIT_RESPONSE;
    if (countOfNums < 1) {
        printf("Incorrect input\n");
        return SUCCESS_RESPONSE;
    }

    clock_t startTime = clock();
    printSpecialOrder(*tree, countOfNums);
    clock_t spendTime = (clock() - startTime) * 1000 / CLOCKS_PER_SEC;
    printf("Spend: %ld ms\n", spendTime);
    return SUCCESS_RESPONSE;
}

ResponsesTypes searchItem(ScapeGoatTree *tree) {
    int requiredKey;

    if (!getSaveIntValue(&requiredKey, "Please, input required KEY\n"))
        return EXIT_RESPONSE;

    clock_t startTime = clock();
    Node *foundNode = searchNode(tree->root, requiredKey);
    clock_t spendTime = (clock() - startTime) * 1000 / CLOCKS_PER_SEC;

    if (foundNode == NULL) printf("No such key\n");
    else {
        printf("Found node: key - %u, value - %s\n", foundNode->key, foundNode->data);
        printf("Spend: %ld ms\n", spendTime);
    }

    return SUCCESS_RESPONSE;
}

ResponsesTypes searchItemSpecial(ScapeGoatTree *tree) {
    int requiredKey;

    if (!getSaveIntValue(&requiredKey, "Please, input required KEY\n"))
        return EXIT_RESPONSE;

    if (tree == NULL || tree->root == NULL) {
        throughException(EMPTY_FIELD_EXCEPTION);
        return SUCCESS_RESPONSE;
    }

    clock_t startTime = clock();

    Node **nodeArray = calloc(tree->countOfNodes, sizeof(Node *));
    packIntoArray(tree->root, nodeArray, 0);

    int resultNodeIdx = -1;
    for (int i = 0; i < tree->countOfNodes; i++) {
        if (nodeArray[i]->key >= requiredKey) {
            break;
        }
        resultNodeIdx = i;
    }
    clock_t spendTime = (clock() - startTime) * 1000 / CLOCKS_PER_SEC;
    if (resultNodeIdx == -1) printf("No less node\n");
    else {
        printf("Result of search: [ key = %u, data = %s ]\n", nodeArray[resultNodeIdx]->key,
               nodeArray[resultNodeIdx]->data);
    }
    printf("Spend: %ld ms\n", spendTime);
    free(nodeArray);

    return SUCCESS_RESPONSE;
}

ResponsesTypes printTree(ScapeGoatTree *tree) {
    printTreeLevel(tree->root, 1);
    return SUCCESS_RESPONSE;
}

ResponsesTypes printTreeInGraphViz(ScapeGoatTree *tree) {

    if (tree == NULL || tree->root == NULL) {
        throughException(EMPTY_FIELD_EXCEPTION);
        return SUCCESS_RESPONSE;
    }

    FILE *fp;

    fp = fopen("files/treeDiagram.dot", "w+");
    if (fp == NULL) {
        throughException(FILE_EXCEPTION);
        return SUCCESS_RESPONSE;
    }
    printTreeGraphVis(tree->root, fp);
    fclose(fp);

    system("dot -Tpng files/treeDiagram.dot -o files/tree.png");
    system("catimg files/tree.png");

    return SUCCESS_RESPONSE;
}

ResponsesTypes readTreeFromFile(ScapeGoatTree *tree) {

    char *fileName;
    int stringArrayLen = 0;
    char **stringArray = NULL;
    ResponsesTypes response;

    response = getSaveStingValue(&fileName, "Please, input file NAME\n");
    if (fileName == NULL) return SUCCESS_RESPONSE;

    response = readFile(fileName, &stringArray, &stringArrayLen);
    free(fileName);
    if (isException(response)) {
        throughException(response);
        return SUCCESS_RESPONSE;
    }

    response = getTreeFromString(stringArray, stringArrayLen, tree);

    for (int i = 0; i < stringArrayLen; ++i) free(stringArray[i]);
    free(stringArray);

    if (isException(response)) throughException(response);

    return SUCCESS_RESPONSE;
}

ResponsesTypes exitProgram(ScapeGoatTree *tree) {
    return EXIT_RESPONSE;
}