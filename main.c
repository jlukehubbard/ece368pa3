#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "queue.h"
#include "grid.h"



#define IGNORE_RETURN (void)!



int coordConvert(short *dim[2], short row, short column);

bool getDimensions(short *dim[2], FILE *binfile);
bool fillGraph(short **G, short *dim[2], FILE *binfile);
void fprintGraph(FILE *stream, short **G, short *dim[2]);
bool fillCostAdj(short **costAdj, short *dim[2], short **G);



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

    FILE *binfile = fopen(binfileName, "rb");

    if (!getDimensions(dim, binfile)) {
        return EXIT_FAILURE;
    }

    //IGNORE_RETURN fprintf(stdout, "%hd %hd\n", (*dim)[0], (*dim)[1]);

    short n = ((*dim)[0] * (*dim)[1]);
    short **inGraph = malloc(n * sizeof(short));
    short **costAdjMatrix = malloc(n * n * sizeof(short));

    fillGraph(inGraph, dim, binfile);
    fprintGraph(stdout, inGraph, dim);
    fillCostAdj(costAdjMatrix, dim, inGraph);

    #endif


    return EXIT_SUCCESS;
}



int coordConvert(short *dim[2], short row, short column) {
    return ((*dim)[1] * row) + column;
}

bool getDimensions(short *dim[2], FILE *binfile) {

    IGNORE_RETURN fseek(binfile, 0, SEEK_SET);

    return (bool) fread(*dim, sizeof(short), 2, binfile);
}

bool fillGraph(short **G, short *dim[2], FILE *binfile) {

    int currCell;
    short i,j;

    for(i = 0; i < (*dim)[0]; i++) {
        for (j = 0; j < (*dim)[1]; j++) {
            //Cell *into = &(new -> cells)[(new -> cols) * i + j];
            //fread(&(into -> cost), sizeof(short), 1, fp);

            currCell = coordConvert(dim, i, j);

            fread(&(G[currCell]), sizeof(short), 1, binfile);
        }
    }

    return true;
}

void fprintGraph(FILE *stream, short **G, short *dim[2]) {

    short i,j;
    int currCell;
    
    fprintf(stream, "%hd %hd\n", (*dim)[0], (*dim)[1]);

    //print content
    for (i = 0; i < (*dim)[0]; i++) {
        for (j = 0; j < (*dim)[1]; j++) {

            currCell = coordConvert(dim, i, j);

            fprintf(stream, "%hd", G[currCell]);
            if (j == (*dim)[1] - 1) {
                fprintf(stream, "\n");
                break;
            }
            fprintf(stream, " ");
        }
    }
}

bool fillCostAdj(short **costAdj, short *dim[2], short **G) {
    return true;
}




















