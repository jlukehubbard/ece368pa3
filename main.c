#include <stdlib.h>
#include <stdio.h>

#include "queue.h"
#include "grid.h"


int main(int argc, char **argv) {
    
    #ifdef TESTMAINFUNCTIONALITY
    if (argc != 5) {
        return EXIT_FAILURE;
    }
    char *binaryGridFilename = argv[1];
    char *textGridFilename = argv[2];
    char *fastestTimesFilename = argv[3];
    char *fastestPathFilename = argv[4];
    #endif



    //#define TESTQUEUE2D
    #ifdef TESTQUEUE2D
    Queue2D *testQ = newQueue2D();

    enqueue2D(testQ, 3, 3);
    enqueue2D(testQ, 1, 1);
    enqueue2D(testQ, 4, 4);

    short points[3][2];
    for (int i = 0; i < 3; i++) {
        dequeue2D(testQ, &(points[i][0]), &(points[i][1]));
        fprintf(stdout, "(%d, %d)\n", points[i][0], points[i][1]);
    }
    
    freeQueue2D(testQ);
    #endif



    #define TESTARRLOAD
    #ifdef TESTARRLOAD

    if (argc != 2) {
        fprintf(stdout, "bad arguments");
        return EXIT_FAILURE;
    }

    char *binaryGridFilename = argv[1];
    Grid *outGrid = readGridFromFile(binaryGridFilename);

    printGrid(outGrid, stdout);

    #endif
    return EXIT_SUCCESS;
}