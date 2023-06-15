#ifndef LAB4A_MYVECTOR_H
#define LAB4A_MYVECTOR_H

#include <stdbool.h>

typedef struct Vector {
    void **array;
    unsigned arrayLength;
    unsigned typeSize;
} Vector;

Vector initVector(int typeSize);

Vector *initVectorPtr(int typeSize);

void clearVector(Vector *vector);

void addItemToVector(Vector *vector, void *item);

void deleteItemFromVector(Vector *vector, int deletingItemIdx);

void setItemVector(Vector *vector, void *data, unsigned idx);

void* getItemFromVector(Vector vector, int itemIdx);

bool isVectorContains(Vector vector, void *data);

void destroyVector(Vector *vector);

#endif //LAB4A_MYVECTOR_H
