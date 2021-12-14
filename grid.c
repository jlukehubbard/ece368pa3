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
            fread(into -> key, sizeof(short), 1, fp);
        }
    }

    return new;
}

void printGrid(Grid *grid, FILE *stream) {
    //print shape
    fprintf(stream, "%hd %hd\n", grid -> rows, grid -> cols);

    int i,j;

    //print content
    for (i = 0; i < grid -> rows; i++) {
        for (j = 0; j < grid -> cols; j++) {
            Cell *outof = &(grid -> cells)[(grid -> cols) * i + j];
            fprintf(stream, "%hd", outof -> key);
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

    return new;
}