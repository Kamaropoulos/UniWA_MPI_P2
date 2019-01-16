#include "mpi.h"
#include "../src/networking.h"

#defin ROOT_PROCESS 0

#define isRoot(callback)               \
    int argc = 1;                      \
    char **argv = new char *[1];       \
    argv[0] = (char *)"./bin/test";    \
    MPI_Init(&argc, &argv);            \
    int processes, myRank;             \
    GetMPIParams(&processes, &myRank); \
    if (myRank == ROOT_PROCESS)        \
    {                                  \
        callback                       \
    }                                  \
    MPI_Finalize();

#define MPI_TEST_CASE(...) INTERNAL_CATCH_TESTCASE(__VA_ARGS__)