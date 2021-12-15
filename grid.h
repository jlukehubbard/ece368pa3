#ifndef __GRID_H__
#define __GRID_H__

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "queue.h"

typedef enum {
    WHITE,
    GRAY,
    BLACK
} CellColor;

typedef struct gridcell {
    short row;
    short col;
    short cost;
    CellColor color;
    struct gridcell *prev;
    short enterTime;
    short exitTime;
} Cell;

typedef struct {
    short rows;
    short cols;
    Cell *cells;
} Grid;



Grid *readGridFromFile(char *binaryGridFilename);
void printGrid(Grid *grid, FILE *stream);
Grid *newGrid(short rows, short cols);
Cell *cellDeref(Grid *grid, short row, short col);
void freeGrid(Grid *grid);
void BFS(Grid *grid, short row, short col);
void bfs(Grid *grid, Queue2D *queue, short row, short col);


#endif