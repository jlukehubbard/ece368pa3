#include <stdlib.h>
#include <stdio.h>

#include "grid.h"


int main(int argc, char **argv) {
    if (argc != 5) {
        return EXIT_FAILURE;
    }
    char *binaryGridFilename = argv[1];
    char *textGridFilename = argv[2];
    char *fastestTimesFilename = argv[3];
    char *fastestPathFilename = argv[4];

    Grid *inputGrid = readGridFromFile(binaryGridFilename);
    if (!inputGrid) {
        return EXIT_FAILURE;
    }

    printGrid(inputGrid, stdout);

    return EXIT_SUCCESS;
}