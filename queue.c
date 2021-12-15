#include "queue.h"

// Standard Queue

Queue *newQueue() {
    Queue* new = malloc(sizeof(Queue));

    new -> head = NULL;
    new -> tail = NULL;

    return new;
}

void enqueue(Queue *queue, short key) {
    QueueNode *newNode = malloc(sizeof(QueueNode));
    newNode -> key = key;
    newNode -> next = NULL;

    if (!(queue -> head)) {
        queue -> head = queue -> tail = newNode;
    } else {
        (queue -> tail) -> next = newNode;
        queue -> tail = (queue -> tail) -> next;
    }
}

short dequeue(Queue *queue) {
    short key = (queue -> head) -> key;
    QueueNode *tmp = queue -> head;
    queue -> head = tmp -> next;
    free(tmp);
    return key;
}

void freeQueue(Queue *queue) {
    short tmp;
    while (queue -> head) {
        tmp = dequeue(queue);
    }
    free(queue);
}

bool isEmpty(Queue *queue) {
    return (bool) !(queue -> head);
}



//2D Queue

Queue2D *newQueue2D() {
    Queue *newRow = newQueue();
    Queue *newCol = newQueue();

    Queue2D *new =malloc(sizeof (Queue2D));

    new -> row = newRow;
    new -> col = newCol;

    return new;
}

void enqueue2D(Queue2D *queue, short row, short col) {
    enqueue(queue -> row, row);
    enqueue(queue -> col, col);
}

void dequeue2D(Queue2D *queue, short *row, short *col) {
    *row = dequeue(queue -> row);
    *col = dequeue(queue -> col);
}

void freeQueue2D(Queue2D *queue) {
    freeQueue(queue -> row);
    freeQueue(queue -> col);
    free(queue);
}

bool isEmpty2D(Queue2D *queue) {
    return (isEmpty(queue -> row) || isEmpty(queue -> col));
}

//Cell Queue

QueueCell *newQueueCell(Grid *grid) {
    if (!grid) {
        return NULL;
    }
    QueueCell *new = malloc(sizeof(QueueCell));
    new -> head = new -> tail = NULL;
    new -> grid = grid;

    return new;
}

void enqueueCell(QueueCell *queue, Cell *cell) {
    if ((cell -> color != WHITE) || !queue) {
        return;
    }

    QueueNodeCell *new = malloc(sizeof(QueueNodeCell));

    new -> cell = cell;
    new -> next = NULL;

    if (isEmptyCell(queue)) {
        queue -> head = queue -> tail = new;
    } else {
        (queue -> tail) -> next = new;
        queue -> tail = (queue -> tail) -> next;
    }
}

Cell *dequeueCell(QueueCell *queue) {
    if (!queue || isEmptyCell(queue)) {
        return NULL;
    }

    QueueNodeCell *tmp = queue -> head;
    Cell *ret = tmp -> cell;
    queue -> head = tmp -> next;
    free(tmp);

    return ret;
}

void enqueueNeighbors(QueueCell *queue, Cell *cell) {

}

bool isEmptyCell(QueueCell *queue) {
    return (bool) !(queue -> head);
}