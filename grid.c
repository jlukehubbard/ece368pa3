#include "grid.h"

Grid *readGridFromFile(char *binaryGridFilename) {
    FILE *fp = fopen(binaryGridFilename, "r");
    if (!fp) {
        fprintf(stderr, "can't open %s: %s\n", binaryGridFilename, strerror(errno));
    }

    //Read grid size
    short m, n;
    int numRead;
    numRead = fread(&m, sizeof(short), 1, fp);
    if (numRead != 1) {return NULL;}
    numRead = fread(&n, sizeof(short), 1, fp);
    if (numRead != 1) {return NULL;}

    Grid *new = newGrid(m, n);

    int i,j;

    for(i = 0; i < (new -> rows); i++) {
        for (j = 0; j < (new -> cols); j++) {
            Cell *into = &(new -> cells)[(new -> cols) * i + j];
            fread(&(into -> cost), sizeof(short), 1, fp);
        }
    }

    free(fp);

    return new;
}

void printGrid(Grid *grid, FILE *stream) {
    //print shape
    fprintf(stream, "%hd %hd\n", grid -> rows, grid -> cols);

    int i,j;

    //print content
    for (i = 0; i < grid -> rows; i++) {
        for (j = 0; j < grid -> cols; j++) {
            Cell *outof = cellDeref(grid, i, j);
            fprintf(stream, "%hd", outof -> cost);
            if (j == (grid -> cols) - 1) { 
                fprintf(stream, "\n");
                break;
            }
            fprintf(stream, " ");
        }
    }
}

Grid *newGrid(short rows, short cols) {
    Grid *new = malloc(sizeof(Grid));
    new -> rows = rows;
    new -> cols = cols;
    new -> cells = malloc((rows * cols) * sizeof(Cell));

    int i,j;

    for(i = 0; i < (new -> rows); i++) {
        for (j = 0; j < (new -> cols); j++) {
            Cell *into = cellDeref(new, i, j);
            into -> row = i;
            into -> col = j;
            into -> color = WHITE;
            into -> prev = NULL;
            into -> enterTime = SHRT_MAX;
            into -> exitTime = SHRT_MAX;
        }
    }

    return new;
}

Cell *cellDeref(Grid *grid, short row, short col) {
    return &(grid -> cells)[(grid -> cols) * row + col];
}

void freeGrid(Grid *grid) {
    free(grid -> cells);
    free(grid);
}

void BFS(Grid *grid, short row, short col) {
    Queue2D *points = malloc(sizeof(Queue2D));
    enqueueCell(points, grid, row, col);
    Cell *curr;
    short time = 0;

    while (!isEmpty2D(points)) {
        curr -> enterTime = time;
        time += 
        curr -> exitTime = 
        curr = dequeueCell(points, grid);
        enqueueNeighbors(points, grid, curr);

    }
    
}

void bfs(Grid *grid, Queue2D *queue, short row, short col) {
    
}