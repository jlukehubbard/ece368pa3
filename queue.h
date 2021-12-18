#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "grid.h"

typedef struct qnode {
    short key;
    struct qnode *next;
} QueueNode;

typedef struct queue {
    QueueNode *head;
    QueueNode *tail;
} Queue;

typedef struct queue2d {
    Queue *row;
    Queue *col;
} Queue2D;


Queue *newQueue();
void enqueue(Queue *queue, short key);
short dequeue(Queue *queue);
void freeQueue(Queue *queue);
bool isEmpty(Queue *queue);

Queue2D *newQueue2D();
void enqueue2D(Queue2D *queue, short row, short col);
void dequeue2D(Queue2D *queue, short *row, short *col);
void freeQueue2D(Queue2D *queue);
bool isEmpty2D(Queue2D *queue);

#endif