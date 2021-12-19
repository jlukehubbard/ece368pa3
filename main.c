#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "queue.h"
#include "grid.h"



#define IGNORE_RETURN (void)!



void dijkstra(short **G, short *dim[2], short **CA, int **distArr, int **predArr, int source);

int getIndex(short *dim[2], short row, short column);
int getSquareIndex(int n, short row, short column);
int dimToCount(short *dim[2]);
int getRow(short *dim[2], int index);
int getCol(short *dim[2], int index);

bool getDimensions(short *dim[2], FILE *binfile);
bool fillGraph(short **G, short *dim[2], FILE *binfile);
void fprintGraph(FILE *stream, short **G, short *dim[2]);
void fprintIntGraph(FILE *stream, int **G, short *dim[2]);
bool fillCostAdj(short **CA, short *dim[2], short **G);
void fprintSquareGraph(FILE *stream, short **CA, int n);


void fprintFastest(FILE *stream, int **distArr, short **dim);
void fprintFastPath(FILE *stream, int **distArr, int **predArr, short **dim);
void fwriteFastPath(FILE * timefile, FILE *pathfile, int **distanceArrays, int **predecessorArrays, short **dim);



int main(int argc, char **argv) {
    
    #define TESTMAINFUNCTIONALITY
    #ifdef TESTMAINFUNCTIONALITY
    if (argc != 5) {
        return EXIT_FAILURE;
    }
    char *binfileName = argv[1];
    char *textfileName = argv[2];
    char *fastestTimesFilename = argv[3];
    char *fastestPathFilename = argv[4];

    short *dimensions = malloc(2 * sizeof(short));
    short **dim = &dimensions;

    FILE *binfile = fopen(binfileName, "rb");

    if (!getDimensions(dim, binfile)) {
        return EXIT_FAILURE;
    }


    //IGNORE_RETURN fprintf(stdout, "%hd %hd\n", (*dim)[0], (*dim)[1]);

    int n = dimToCount(dim);
    short *inGraph = malloc(n * sizeof(short));
    short *costAdjMatrix = malloc(n * n * sizeof(short));

    short **G = &inGraph;
    short **CA = &costAdjMatrix;

    fillGraph(G, dim, binfile);
    fillCostAdj(CA, dim, G);

    fclose(binfile);
    // array of pointers to arrays
    int **distanceArrays = malloc((*dim)[1] * sizeof(int*));
    int **predecessorArrays = malloc((*dim)[1] * sizeof(int*));


    for (size_t i = 0; i < (*dim)[1]; i++) {
        distanceArrays[i] = malloc(n * sizeof(int));
        predecessorArrays[i] = malloc(n * sizeof(int));
        dijkstra(G, dim, CA, &distanceArrays[i], &predecessorArrays[i], i);
    }

    FILE *textfile = fopen(textfileName, "wb");
    FILE *timefile = fopen(fastestTimesFilename, "wb");
    FILE *pathfile = fopen(fastestPathFilename, "wb");

    fprintGraph(textfile, G, dim);
    fwriteFastPath(timefile, pathfile, distanceArrays, predecessorArrays, dim);

    fclose(textfile);
    fclose(timefile);
    fclose(pathfile);

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



    //#define NOGRID
    #ifdef NOGRID

    if (argc != 2) {
        fprintf(stdout, "bad args");
        return EXIT_FAILURE;
    }

    char *binfileName = argv[1];
    short *dimensions = malloc(2 * sizeof(short));
    short **dim = &dimensions;

    FILE *binfile = fopen(binfileName, "rb");

    if (!getDimensions(dim, binfile)) {
        return EXIT_FAILURE;
    }

    //IGNORE_RETURN fprintf(stdout, "%hd %hd\n", (*dim)[0], (*dim)[1]);

    int n = dimToCount(dim);
    short *inGraph = malloc(n * sizeof(short));
    short *costAdjMatrix = malloc(n * n * sizeof(short));

    short **G = &inGraph;
    short **CA = &costAdjMatrix;

    //fprintGraph(stdout, G, dim);
    fillGraph(G, dim, binfile);
    //fprintGraph(stdout, G, dim);
    fillCostAdj(CA, dim, G);
    //fprintSquareGraph(stdout, CA, n);

    // array of pointers to arrays
    int **distanceArrays = malloc((*dim)[1] * sizeof(int*));
    int **predecessorArrays = malloc((*dim)[1] * sizeof(int*));

    
    for (size_t i = 0; i < (*dim)[1]; i++) {
        distanceArrays[i] = malloc(n * sizeof(int));
        predecessorArrays[i] = malloc(n * sizeof(int));
        dijkstra(G, dim, CA, &distanceArrays[i], &predecessorArrays[i], i);
        fprintf(stdout, "%d:\n", (int) i);
        fprintIntGraph(stdout, &distanceArrays[i], dim);
        fprintIntGraph(stdout, &predecessorArrays[i], dim);
        fprintFastest(stdout, &distanceArrays[i], dim);
        fprintFastPath(stdout, &distanceArrays[i], &predecessorArrays[i], dim);
    }

    /**/


    #endif


    return EXIT_SUCCESS;
}



void dijkstra(short **G, short *dim[2], short **CA, int **distArr, int **predArr, int source) {
    int n = dimToCount(dim), minDist, next;
    CellColor *color = malloc(n * sizeof(CellColor));

    for (size_t i = 0; i < n; i++) {
        (*distArr)[i] = INT_MAX;
        (*predArr)[i] = source;
        color[i] = WHITE;
    }

    (*distArr)[source] = 0; // was (*G)[source];
    (*predArr)[source] = INT_MAX;
    //color[source] = BLACK;


    for (size_t i = 0; i < (n-2); i++) {
        minDist = INT_MAX;

        for (size_t j = 0; j < n; j++) {
            if ((*distArr)[j] < minDist && color[j] == WHITE) {
                minDist = (*distArr)[j];
                next = j;
            }
        }

        color[next] = BLACK;

        for (size_t j = 0; j < n; j++) {
            if (color[j] == WHITE) {
                if (minDist + (*CA)[getSquareIndex(n, next, j)] < (*distArr)[j]) {
                    (*distArr)[j] = minDist + (*CA)[getSquareIndex(n, next, j)];
                    (*predArr)[j] = next;
                }
            }
        }
    }

}

int getIndex(short *dim[2], short row, short column) {
    return ((*dim)[1] * row) + column;
}

int getSquareIndex(int n, short row, short column) {
    return (n * row) + column;
}

int getRow(short *dim[2], int index){

    return ((index - getCol(dim, index)) / (*dim)[1]);
}

int getCol(short *dim[2], int index) {
    return index % (*dim)[1];
}

int dimToCount(short *dim[2]) {
    return ((*dim)[0] * (*dim)[1]);
}

bool getDimensions(short *dim[2], FILE *binfile) {

    IGNORE_RETURN fseek(binfile, 0, SEEK_SET);

    return (bool) fread((*dim), sizeof(short), 2, binfile);
}

bool fillGraph(short **G, short *dim[2], FILE *binfile) {

    int currCell;
    short i,j;

    for(i = 0; i < (*dim)[0]; i++) {
        for (j = 0; j < (*dim)[1]; j++) {
            //Cell *into = &(new -> cells)[(new -> cols) * i + j];
            //fread(&(into -> cost), sizeof(short), 1, fp);

            currCell = getIndex(dim, i, j);

            fread(&((*G)[currCell]), sizeof(short), 1, binfile);
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

            currCell = getIndex(dim, i, j);

            fprintf(stream, "%hd", (*G)[currCell]);
            if (j == (*dim)[1] - 1) {
                fprintf(stream, "\n");
                break;
            }
            fprintf(stream, " ");
        }
    }
}

void fprintIntGraph(FILE *stream, int **G, short *dim[2]) {

    short i, j;
    int currCell;
    
    fprintf(stream, "%hd %hd\n", (*dim)[0], (*dim)[1]);

    //print content
    for (i = 0; i < (*dim)[0]; i++) {
        for (j = 0; j < (*dim)[1]; j++) {

            currCell = getIndex(dim, i, j);

            if((*G)[currCell] != INT_MAX) {
                fprintf(stream, "%3d", (*G)[currCell]);
            } else {
                fprintf(stream, "inf");
            }

            if (j == (*dim)[1] - 1) {
                fprintf(stream, "\n");
                break;
            }
            fprintf(stream, " ");
        }
    }
}

bool fillCostAdj(short **CA, short *dim[2], short **G) {

    int n = dimToCount(dim);
    int i, j;
    short fromRow, fromCol, toRow, toCol;

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            (*CA)[getSquareIndex(n, i, j)] = SHRT_MAX;
        }
    }
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            fromRow = getRow(dim, i);
            fromCol = getCol(dim, i);
            toRow = getRow(dim, j);
            toCol = getCol(dim, j);

            short rowOffs = toRow - fromRow;
            short colOffs = toCol - fromCol;

            if(rowOffs == -1 || rowOffs == 1) {
                if (colOffs == 0) {
                    (*CA)[getSquareIndex(n, i, j)] = (*G)[i];
                }
            } else if (rowOffs == 0) {
                if (colOffs == -1 || colOffs == 1) {
                    (*CA)[getSquareIndex(n, i, j)] = (*G)[i];
                }
            }
            /*
            switch(toRow - fromRow) {
                case 0:
                    switch(toCol - fromCol) {
                        case -1:
                        case 1:
                            (*CA)[getSquareIndex(n, i, j)] = (*G)[j];
                            break;
                        default:
                            goto infty;
                    }
                    break;
                case -1:
                case 1:
                    switch(toCol - fromCol) {
                        case -1:
                        case 0:
                        case 1:
                            (*CA)[getSquareIndex(n, i, j)] = (*G)[j];
                            break;
                        default:
                            goto infty;
                    }
                    break;
                default:
                    infty:
                    (*CA)[getSquareIndex(n, i, j)] = SHRT_MAX;
            }
            */
        }
    }

    return true;
}

void fprintSquareGraph(FILE *stream, short **CA, int n) {
    short i,j;
    int currCell;
    
    fprintf(stream, "%hd %hd\n", n, n);

    //print content
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {

            currCell = getSquareIndex(n, i, j);

            if((*CA)[currCell] != SHRT_MAX) {
                fprintf(stream, "%3hd", (*CA)[currCell]);
            } else {
                fprintf(stream, "inf");
            }
            if (j == n - 1) {
                fprintf(stream, "\n");
                break;
            }
            fprintf(stream, " ");
        }
    }
}

void fprintFastest(FILE *stream, int **distArr, short **dim) {
    short rows = (*dim)[0];
    short cols = (*dim)[1];
    int n = rows * cols;
    fprintf(stream, "%d\n", cols);
    for (int i = (n - cols); i < n; i++) {
        fprintf(stream, "%hd", (*distArr)[i]);
        if (i == n - 1) {
            fprintf(stream, "\n");
        } else {
            fprintf(stream, " ");
        }
    }
}

void fprintFastPath(FILE *stream, int **distArr, int **predArr, short **dim) {
    int n = (*dim)[0] * (*dim)[1];
    int curr = (*dim)[0] * ((*dim)[1] - 1);
    int end = curr;
    int count = 0;

    int minDist = INT_MAX;

    while (curr < n) {
        if ((*distArr)[curr] < minDist) {
            minDist = (*distArr)[curr];
            end = curr;
        }
        curr++;
    }

    curr = end;

    fprintf(stream, "%d\n", (*distArr)[curr]);

    while (curr != INT_MAX) {
        count++;
        fprintf(stream, "%d (%hd, %hd)\n", curr, getRow(dim, curr), getCol(dim, curr));
        curr = (*predArr)[curr];
    }

    fprintf(stream, "%d\n", count);
}

void fwriteFastPath(FILE *timefile, FILE *pathfile, int **distanceArrays, int **predecessorArrays, short **dim) {
    int n = (*dim)[0] * (*dim)[1];
    int curr, count = 0, minTime;
    int *fastestTimes = malloc((*dim)[1] * sizeof(int));
    int **distArr, **predArr;

    FILE *stream = stdout;

    for (size_t i = 0; i < (*dim)[1]; i++) {
        distArr = &distanceArrays[i];
        predArr = &predecessorArrays[i];
        curr = (*dim)[0] * ((*dim)[1] - 1);

        minTime = INT_MAX;

        while (curr < n) {
            if ((*distArr)[curr] < minTime) {
                minTime = (*distArr)[curr];
            }
            curr++;
        }

        fastestTimes[i] = minTime;
    }

    minTime = INT_MAX;
    int pathnum;

    for (size_t i = 0; i < (*dim)[1]; i++) {
        //reusing minTime, don't get confused
        if (fastestTimes[i] < minTime) {
            minTime = fastestTimes[i];
            pathnum = i;
        }
    }

    distArr = &distanceArrays[pathnum];
    predArr = &predecessorArrays[pathnum];
    minTime = INT_MAX;

    for (size_t i = n - (*dim)[1]; i < n; i++) {
        if ((*distArr)[i] < minTime) {
            curr = i;
            minTime = (*distArr)[i];
        }
    }

    //fastest times file
    fwrite(&(*dim)[1], sizeof(short), 1, timefile);
    fwrite(fastestTimes, sizeof(int), (*dim)[1], timefile);

    int *points = malloc(n * sizeof(int));

    while (curr != INT_MAX) {
        count++;
        points[count] = curr;
        curr = (*predArr)[curr];
    }

    //fastest path file
    int row, col;
    fwrite(&minTime, sizeof(int), 1, pathfile);
    fwrite(&count, sizeof(int), 1, pathfile);
    for (size_t i = count - 1; i >= 0; i--) {
        row = getRow(dim, points[i]);
        col = getCol(dim, points[i]);
        fprintf(stdout, "%hd %hd\n", row, col);
        fwrite(&row, sizeof(short), 1, pathfile);
        fwrite(&col, sizeof(short), 1, pathfile);
    }


    fprintf(stream, "%d\n", count);
}















