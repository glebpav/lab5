#ifndef LAB5_MYQUEUE_H
#define LAB5_MYQUEUE_H

#include "../../controller/GraphHelper.h"

#define SIZE 100
typedef struct Queue {
    int items[SIZE];
    int front;
    int rear;
} Queue;

Queue *createQueue();

void enqueue(Queue *q, int);

int dequeue(Queue *q);


int isEmpty(Queue *q);

void printQueue(Queue *q);

#endif //LAB5_MYQUEUE_H
