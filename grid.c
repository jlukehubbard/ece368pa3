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

    short *array[m][n] = malloc((m*n) * sizeof(short));

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            numRead = fread(&(array[i][j]), sizeof(short), 1, fp);
            if (numRead != 1) {return NULL;}
        }
    }

    Grid *newGrid = malloc(sizeof(Grid));
    newGrid -> rows = m;
    newGrid -> cols = n;
    newGrid -> array = array;

    return newGrid;
}

void printGrid(Grid *grid, FILE *stream) {
    //print shape
    fprintf(stream, "%hd %hd\n", grid -> rows, grid -> cols);

    //print content
    for (int i = 0; i < grid -> rows; i++) {
        for (int j = 0; j < grid -> cols; j++) {
            fprintf(stream, "%hd", (grid -> array) [i][j]);
            if (j == (grid -> cols) - 1) { 
                fprintf(stream, "\n");
                break;
            }
            fprintf(stream, " ");
        }
    }
}