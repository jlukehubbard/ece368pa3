#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "queue.h"
#include "grid.h"



bool getDimensions()



int main(int argc, char **argv) {
    
    //#define TESTMAINFUNCTIONALITY
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



    //#define TESTARRLOAD
    #ifdef TESTARRLOAD

    if (argc != 2) {
        fprintf(stdout, "bad arguments");
        return EXIT_FAILURE;
    }

    char *binaryGridFilename = argv[1];
    Grid *outGrid = readGridFromFile(binaryGridFilename);

    printGrid(outGrid, stdout);

    freeGrid(outGrid);

    #endif



    //#define TESTDIJKSTRA
    #ifdef TESTDIJKSTRA

    if (argc != 2) {
        fprintf(stdout, "bad args");
        return EXIT_FAILURE;
    }

 
    char *binaryGridFilename = argv[1];
    Grid *outGrid = readGridFromFile(binaryGridFilename);

    printGrid(outGrid, stdout);

    

    //for (int i = 0; i < (outGrid -> cols))

    freeGrid(outGrid);
    #endif



    #define NOGRID
    #ifdef NOGRID

    if (argc != 2) {
        fprintf(stdout, "bad args");
        return EXIT_FAILURE;
    }

    char *binfileName = argv[1];
    short *dim[2];
    if (!getDimensions(dim, binfileName)) {
        return EXIT_FAILURE;
    }

    fprintf(stdout, "%hd %hd\n", (*dim)[0], (*dim)[1]);

    /*
    short n = ((*dim)[0] * (*dim)[1]);
    short *inGraph = malloc(n * sizeof(short));
    short *costAdjMatrix = malloc(n * n * sizeof(short));

    fprintGraoh(stdout, inGraph);
    fillCostAdj(costAdjMatrix, n * n);

    for (int = 0; i < (*dim)[1])
    */
    #endif


    return EXIT_SUCCESS;
}