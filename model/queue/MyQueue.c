#include <stdio.h>
#include <malloc.h>
#include "MyQueue.h"


struct Queue *createQueue() {
    struct Queue *q = malloc(sizeof(struct Queue));
    q->front = -1;
    q->rear = -1;
    return q;
}

int isEmpty(struct Queue *q) {
    if (q->rear == -1) return 1;
    else return 0;
}

void enqueue(struct Queue *q, int value) {
    if (q->rear != SIZE - 1) {
        if (q->front == -1)
            q->front = 0;
        q->rear++;
        q->items[q->rear] = value;
    }
}

int dequeue(struct Queue *q) {
    int item;
    if (isEmpty(q)) item = -1;
    else {
        item = q->items[q->front];
        q->front++;
        if (q->front > q->rear) {
            q->front = q->rear = -1;
        }
    }
    return item;
}
