#ifndef LAB5_MYQUEUE_H
#define LAB5_MYQUEUE_H

#include "../../controller/GraphHelper.h"

#define SIZE 100
struct queue {
    int items[SIZE];
    int front;
    int rear;
};
struct queue* createQueue();
void enqueue(struct queue* q, int);
int dequeue(struct queue* q);
void display(struct queue* q);
int isEmpty(struct queue* q);
void printQueue(struct queue* q);

#endif //LAB5_MYQUEUE_H
