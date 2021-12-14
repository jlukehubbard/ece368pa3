#include <stdlib.h>
#include <stdio.h>

#include "queue.h"


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
    

    #define TESTQUEUE2D
    #ifdef TESTQUEUE2D
    Queue2D *testQ = newQueue2D();

    enqueue2D(testQ, 3, 3);
    enqueue2D(testQ, 1, 1);
    enqueue2D(testQ, 4, 4);

    fprintf(stdout, "%d %d %d\n", dequeue2D(testQ), dequeue2D(testQ), dequeue2D(testQ));


    #endif

    return EXIT_SUCCESS;
}