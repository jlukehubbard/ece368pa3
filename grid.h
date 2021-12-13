#ifndef __GRID_H__
#define __GRID_H__

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

typedef struct {
    short rows;
    short cols;
    short **array;
} Grid;



Grid *readGridFromFile(char *binaryGridFilename);
void printGrid(Grid *grid, FILE *stream);


#endif