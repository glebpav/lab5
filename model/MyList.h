#ifndef LAB5_MYLIST_H
#define LAB5_MYLIST_H

typedef struct ListItem {
    void *data;
    struct ListItem* prevListItem;
    struct ListItem* nextListItem;
} ListItem;

typedef struct List {
    int typeSize;
    int listLength;
    ListItem *firstElement;
} List;

List *initListPtr(int typeSize);

void addItemToList(List *list, void *data);

void *deleteItemFromListByIdx(List *list, int deletingItemIdx);

void *deleteItemFromList(List *list, void *data);

void setItemList(List *list, void *data, ListItem *listItem);

void* getItemFromListByIdx(List list, int itemIdx);

// bool isListContains(List list, void *data);

void destroyList(List *list);

#endif //LAB5_MYLIST_H
