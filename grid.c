#include "grid.h"

Grid *readGridFromFile(char *binaryGridFilename) {
    FILE *fp = fopen(binaryGridFilename, "rb");

    //Read grid size
    short m, n;
    fread(&m, sizeof(short), 1, fp);
    fread(&n, sizeof(short), 1, fp);

    short **array = malloc((m * n) * sizeof(short));

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            fread(array[i][j], sizeof(short), 1, fp);
        }
    }

    Grid *newGrid = malloc(sizeof Grid);
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