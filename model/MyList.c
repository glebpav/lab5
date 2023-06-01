#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "MyList.h"

List *initListPtr(int typeSize) {
    List *list = calloc(1, sizeof(List));
    list->typeSize = typeSize;
    return list;
}

void addItemToList(List *list, void *data) {
    if (list == NULL) return;

    list->listLength += 1;
    ListItem *newItem = calloc(1, sizeof(ListItem));
    newItem->data = calloc(1, list->typeSize);
    memcpy(newItem->data, data, list->typeSize);

    ListItem *thisItem = list->firstElement;
    ListItem *prevItem;

    if (thisItem == NULL) {
        list->firstElement = newItem;
        return;
    }

    while (thisItem != NULL) {
        prevItem = thisItem;
        thisItem = thisItem->nextListItem;
    }

    prevItem->nextListItem = newItem;
    newItem->prevListItem = prevItem;
}

void *deleteItemFromListByIdx(List *list, int deletingItemIdx){
    return false;
}

void *deleteItemFromList(List *list, void *data) {
    if (list == NULL) return NULL;

    ListItem *thisItem = list->firstElement;
    ListItem *prevItem = NULL;
    void *deletingItemData = NULL;

    while (thisItem != NULL) {
        if (strcmp(thisItem->data, data) == 0) {
            list->listLength -= 1;
            if (prevItem == NULL) list->firstElement = thisItem->nextListItem;
            else prevItem->nextListItem = thisItem->nextListItem;
            deletingItemData = thisItem->data;
            free(thisItem->data);
            free(thisItem);
            break;
        }
        thisItem = thisItem->nextListItem;
        prevItem = thisItem;
    }

    return deletingItemData;
}

void setItemList(List *list, void *data, ListItem *listItem) {
    // TODO: implement this
}

void* getItemFromListByIdx(List list, int itemIdx) {
    int idx = 0;
    ListItem *thisItem = list.firstElement;
    ListItem *prevItem = NULL;

    while (thisItem != NULL) {
        if (itemIdx == idx) return thisItem->data;
        thisItem = thisItem->nextListItem;
        idx += 1;
    }

    return NULL;
}