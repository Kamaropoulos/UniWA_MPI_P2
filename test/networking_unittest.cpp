/**
 * @file networking_unittest.cpp
 * @author Konstantinos Kamaropoulos (kamaropoulos@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2019-01-05
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#define CATCH_CONFIG_MAIN

#include "../lib/catch.hpp"

#include "mpi.h"

#include "../src/networking.h"

/**
 * @brief Unit test for method _lineToProcess with 4 lines and 4 processes (p == n), ((n mod p) == 0)
 * 
 */
TEST_CASE("[Internal] Line to Process Assignments: (p == n), ((n mod p) == 0)", "[ilineToProcess]")
{
    CHECK(_lineToProcess(0, 4, 4) == 0);
    CHECK(_lineToProcess(1, 4, 4) == 1);
    CHECK(_lineToProcess(2, 4, 4) == 2);
    CHECK(_lineToProcess(3, 4, 4) == 3);
}

/**
 * @brief Unit test for method _lineToProcess with 8 lines and 4 processes (p < n), ((n mod p) == 0)
 * 
 */
TEST_CASE("[Internal] Line to Process Assignments: (p < n), ((n mod p) == 0)", "[ilineToProcess]")
{
    CHECK(_lineToProcess(0, 8, 4) == 0);
    CHECK(_lineToProcess(1, 8, 4) == 1);
    CHECK(_lineToProcess(2, 8, 4) == 2);
    CHECK(_lineToProcess(3, 8, 4) == 3);
    CHECK(_lineToProcess(4, 8, 4) == 0);
    CHECK(_lineToProcess(5, 8, 4) == 1);
    CHECK(_lineToProcess(6, 8, 4) == 2);
    CHECK(_lineToProcess(7, 8, 4) == 3);
}

/**
 * @brief Unit test for method _lineToProcess with 7 lines and 4 processes (p < n), ((n mod p) != 0)
 * 
 */
TEST_CASE("[Internal] Line to Process Assignments: (p < n), ((n mod p) != 0)", "[ilineToProcess]")
{
    CHECK(_lineToProcess(0, 7, 4) == 0);
    CHECK(_lineToProcess(1, 7, 4) == 1);
    CHECK(_lineToProcess(2, 7, 4) == 2);
    CHECK(_lineToProcess(3, 7, 4) == 3);
    CHECK(_lineToProcess(4, 7, 4) == 0);
    CHECK(_lineToProcess(5, 7, 4) == 1);
    CHECK(_lineToProcess(6, 7, 4) == 2);
}

/**
 * @brief Unit test for method _lineToProcess with 4 lines and 8 processes (p > n), ((n mod p) == 0)
 * 
 */
TEST_CASE("[Internal] Line to Process Assignments: (p > n), ((n mod p) == 0)", "[ilineToProcess]")
{
    CHECK(_lineToProcess(0, 4, 8) == 0);
    CHECK(_lineToProcess(1, 4, 8) == 1);
    CHECK(_lineToProcess(2, 4, 8) == 2);
    CHECK(_lineToProcess(3, 4, 8) == 3);
}

/**
 * @brief Unit test for method _lineToProcess with 5 lines and 8 processes (p > n), ((n mod p) != 0)
 * 
 */
TEST_CASE("[Internal] Line to Process Assignments: (p > n), ((n mod p) != 0)", "[ilineToProcess]")
{
    CHECK(_lineToProcess(0, 5, 8) == 0);
    CHECK(_lineToProcess(1, 5, 8) == 1);
    CHECK(_lineToProcess(2, 5, 8) == 2);
    CHECK(_lineToProcess(3, 5, 8) == 3);
    CHECK(_lineToProcess(4, 5, 8) == 4);
}

/**
 * @brief Unit test for method lineToProcess with 4 lines and 4 processes (p == n), ((n mod p) == 0)
 * 
 */
TEST_CASE("Line to Process Assignments: (p == n), ((n mod p) == 0)", "[lineToProcess]")
{
    CHECK(lineToProcess(0, 4, 4) == 0);
    CHECK(lineToProcess(1, 4, 4) == 1);
    CHECK(lineToProcess(2, 4, 4) == 2);
    CHECK(lineToProcess(3, 4, 4) == 3);
}

/**
 * @brief Unit test for method lineToProcess with 8 lines and 4 processes (p < n), ((n mod p) == 0)
 * 
 */
TEST_CASE("Line to Process Assignments: (p < n), ((n mod p) == 0)", "[lineToProcess]")
{
    CHECK(lineToProcess(0, 8, 4) == 0);
    CHECK(lineToProcess(1, 8, 4) == 0);
    CHECK(lineToProcess(2, 8, 4) == 1);
    CHECK(lineToProcess(3, 8, 4) == 1);
    CHECK(lineToProcess(4, 8, 4) == 2);
    CHECK(lineToProcess(5, 8, 4) == 2);
    CHECK(lineToProcess(6, 8, 4) == 3);
    CHECK(lineToProcess(7, 8, 4) == 3);
}

/**
 * @brief Unit test for method lineToProcess with 7 lines and 4 processes (p < n), ((n mod p) != 0)
 * 
 */
TEST_CASE("Line to Process Assignments: (p < n), ((n mod p) != 0)", "[lineToProcess]")
{
    CHECK(lineToProcess(0, 7, 4) == 0);
    CHECK(lineToProcess(1, 7, 4) == 0);
    CHECK(lineToProcess(2, 7, 4) == 1);
    CHECK(lineToProcess(3, 7, 4) == 1);
    CHECK(lineToProcess(4, 7, 4) == 2);
    CHECK(lineToProcess(5, 7, 4) == 2);
    CHECK(lineToProcess(6, 7, 4) == 3);
}

/**
 * @brief Unit test for method lineToProcess with 4 lines and 8 processes (p > n), ((n mod p) == 0)
 * 
 */
TEST_CASE("Line to Process Assignments: (p > n), ((n mod p) == 0)", "[lineToProcess]")
{
    CHECK(lineToProcess(0, 4, 8) == 0);
    CHECK(lineToProcess(1, 4, 8) == 1);
    CHECK(lineToProcess(2, 4, 8) == 2);
    CHECK(lineToProcess(3, 4, 8) == 3);
}

/**
 * @brief Unit test for method lineToProcess with 5 lines and 8 processes (p > n), ((n mod p) != 0)
 * 
 */
TEST_CASE("Line to Process Assignments: (p > n), ((n mod p) != 0)", "[lineToProcess]")
{
    CHECK(lineToProcess(0, 5, 8) == 0);
    CHECK(lineToProcess(1, 5, 8) == 1);
    CHECK(lineToProcess(2, 5, 8) == 2);
    CHECK(lineToProcess(3, 5, 8) == 3);
    CHECK(lineToProcess(4, 5, 8) == 4);
}

/**
 * @brief Unit test for method processToLines with 4 lines and 4 processes (p == n), ((n mod p) == 0)
 * 
 */
TEST_CASE("Lines assigned to a process: (p == n), ((n mod p) == 0)", "[processToLines]")
{
    CHECK(processToLines(0, 4, 4).size() == 1);
    CHECK(processToLines(1, 4, 4).size() == 1);
    CHECK(processToLines(2, 4, 4).size() == 1);
    CHECK(processToLines(3, 4, 4).size() == 1);

    CHECK(processToLines(0, 4, 4)[0] == 0);
    CHECK(processToLines(1, 4, 4)[0] == 1);
    CHECK(processToLines(2, 4, 4)[0] == 2);
    CHECK(processToLines(3, 4, 4)[0] == 3);
}

/**
 * @brief Unit test for method processToLines with 8 lines and 4 processes (p < n), ((n mod p) == 0)
 * 
 */
TEST_CASE("Lines assigned to a process: (p < n), ((n mod p) == 0)", "[processToLines]")
{
    CHECK(processToLines(0, 8, 4).size() == 2);
    CHECK(processToLines(1, 8, 4).size() == 2);
    CHECK(processToLines(2, 8, 4).size() == 2);
    CHECK(processToLines(3, 8, 4).size() == 2);
    CHECK(processToLines(0, 8, 4)[0] == 0);
    CHECK(processToLines(0, 8, 4)[1] == 1);
    CHECK(processToLines(1, 8, 4)[0] == 2);
    CHECK(processToLines(1, 8, 4)[1] == 3);
    CHECK(processToLines(2, 8, 4)[0] == 4);
    CHECK(processToLines(2, 8, 4)[1] == 5);
    CHECK(processToLines(3, 8, 4)[0] == 6);
    CHECK(processToLines(3, 8, 4)[1] == 7);
}

/**
 * @brief Unit test for method processToLines with 7 lines and 4 processes (p < n), ((n mod p) != 0)
 * 
 */
TEST_CASE("Lines assigned to a process: (p < n), ((n mod p) != 0)", "[processToLines]")
{
    CHECK(processToLines(0, 7, 4).size() == 2);
    CHECK(processToLines(1, 7, 4).size() == 2);
    CHECK(processToLines(2, 7, 4).size() == 2);
    CHECK(processToLines(3, 7, 4).size() == 1);
    CHECK(processToLines(0, 7, 4)[0] == 0);
    CHECK(processToLines(0, 7, 4)[1] == 1);
    CHECK(processToLines(1, 7, 4)[0] == 2);
    CHECK(processToLines(1, 7, 4)[1] == 3);
    CHECK(processToLines(2, 7, 4)[0] == 4);
    CHECK(processToLines(2, 7, 4)[1] == 5);
    CHECK(processToLines(3, 7, 4)[0] == 6);
}

/**
 * @brief Unit test for method processToLines with 4 lines and 8 processes (p > n), ((n mod p) == 0)
 * 
 */
TEST_CASE("Lines assigned to a process: (p > n), ((n mod p) == 0)", "[processToLines]")
{
    CHECK(processToLines(0, 4, 8).size() == 1);
    CHECK(processToLines(1, 4, 8).size() == 1);
    CHECK(processToLines(2, 4, 8).size() == 1);
    CHECK(processToLines(3, 4, 8).size() == 1);
    CHECK(processToLines(4, 4, 8).size() == 0);
    CHECK(processToLines(5, 4, 8).size() == 0);
    CHECK(processToLines(6, 4, 8).size() == 0);
    CHECK(processToLines(7, 4, 8).size() == 0);
    CHECK(processToLines(0, 4, 8)[0] == 0);
    CHECK(processToLines(1, 4, 8)[0] == 1);
    CHECK(processToLines(2, 4, 8)[0] == 2);
    CHECK(processToLines(3, 4, 8)[0] == 3);
}

/**
 * @brief Unit test for method processToLines with 5 lines and 8 processes (p > n), ((n mod p) != 0)
 * 
 */
TEST_CASE("Lines assigned to a process: (p > n), ((n mod p) != 0)", "[processToLines]")
{
    CHECK(processToLines(0, 5, 8).size() == 1);
    CHECK(processToLines(1, 5, 8).size() == 1);
    CHECK(processToLines(2, 5, 8).size() == 1);
    CHECK(processToLines(3, 5, 8).size() == 1);
    CHECK(processToLines(4, 5, 8).size() == 1);
    CHECK(processToLines(5, 5, 8).size() == 0);
    CHECK(processToLines(6, 5, 8).size() == 0);
    CHECK(processToLines(7, 5, 8).size() == 0);
    CHECK(processToLines(0, 5, 8)[0] == 0);
    CHECK(processToLines(1, 5, 8)[0] == 1);
    CHECK(processToLines(2, 5, 8)[0] == 2);
    CHECK(processToLines(3, 5, 8)[0] == 3);
    CHECK(processToLines(4, 5, 8)[0] == 4);
}

/**
 * @brief Unit test for method processToLinesCount with 4 lines and 4 processes (p == n), ((n mod p) == 0)
 * 
 */
TEST_CASE("Number of lines assigned to a process: (p == n), ((n mod p) == 0)", "[processToLinesCount]")
{
    CHECK(processToLines(0, 4, 4).size() == 1);
    CHECK(processToLines(1, 4, 4).size() == 1);
    CHECK(processToLines(2, 4, 4).size() == 1);
    CHECK(processToLines(3, 4, 4).size() == 1);
    CHECK(processToLines(0, 4, 4)[0] == 0);
    CHECK(processToLines(1, 4, 4)[0] == 1);
    CHECK(processToLines(2, 4, 4)[0] == 2);
    CHECK(processToLines(3, 4, 4)[0] == 3);
}

/**
 * @brief Unit test for method processToLinesCount with 8 lines and 4 processes (p < n), ((n mod p) == 0)
 * 
 */
TEST_CASE("Number of lines assigned to a process: (p < n), ((n mod p) == 0)", "[processToLinesCount]")
{
    CHECK(processToLines(0, 8, 4).size() == 2);
    CHECK(processToLines(1, 8, 4).size() == 2);
    CHECK(processToLines(2, 8, 4).size() == 2);
    CHECK(processToLines(3, 8, 4).size() == 2);
    CHECK(processToLines(0, 8, 4)[0] == 0);
    CHECK(processToLines(0, 8, 4)[1] == 1);
    CHECK(processToLines(1, 8, 4)[0] == 2);
    CHECK(processToLines(1, 8, 4)[1] == 3);
    CHECK(processToLines(2, 8, 4)[0] == 4);
    CHECK(processToLines(2, 8, 4)[1] == 5);
    CHECK(processToLines(3, 8, 4)[0] == 6);
    CHECK(processToLines(3, 8, 4)[1] == 7);
}

/**
 * @brief Unit test for method processToLinesCount with 7 lines and 4 processes (p < n), ((n mod p) != 0)
 * 
 */
TEST_CASE("Number of lines assigned to a process: (p < n), ((n mod p) != 0)", "[processToLinesCount]")
{
    CHECK(processToLines(0, 7, 4).size() == 2);
    CHECK(processToLines(1, 7, 4).size() == 2);
    CHECK(processToLines(2, 7, 4).size() == 2);
    CHECK(processToLines(3, 7, 4).size() == 1);
    CHECK(processToLines(0, 7, 4)[0] == 0);
    CHECK(processToLines(0, 7, 4)[1] == 1);
    CHECK(processToLines(1, 7, 4)[0] == 2);
    CHECK(processToLines(1, 7, 4)[1] == 3);
    CHECK(processToLines(2, 7, 4)[0] == 4);
    CHECK(processToLines(2, 7, 4)[1] == 5);
    CHECK(processToLines(3, 7, 4)[0] == 6);
}

/**
 * @brief Unit test for method processToLinesCount with 4 lines and 8 processes (p > n), ((n mod p) == 0)
 * 
 */
TEST_CASE("Number of lines assigned to a process: (p > n), ((n mod p) == 0)", "[processToLinesCount]")
{
    CHECK(processToLines(0, 4, 8).size() == 1);
    CHECK(processToLines(1, 4, 8).size() == 1);
    CHECK(processToLines(2, 4, 8).size() == 1);
    CHECK(processToLines(3, 4, 8).size() == 1);
    CHECK(processToLines(4, 4, 8).size() == 0);
    CHECK(processToLines(5, 4, 8).size() == 0);
    CHECK(processToLines(6, 4, 8).size() == 0);
    CHECK(processToLines(7, 4, 8).size() == 0);
    CHECK(processToLines(0, 4, 8)[0] == 0);
    CHECK(processToLines(1, 4, 8)[0] == 1);
    CHECK(processToLines(2, 4, 8)[0] == 2);
    CHECK(processToLines(3, 4, 8)[0] == 3);
}

/**
 * @brief Unit test for method processToLinesCount with 5 lines and 8 processes (p > n), ((n mod p) != 0)
 * 
 */
TEST_CASE("Number of lines assigned to a process: (p > n), ((n mod p) != 0)", "[processToLinesCount]")
{
    CHECK(processToLines(0, 5, 8).size() == 1);
    CHECK(processToLines(1, 5, 8).size() == 1);
    CHECK(processToLines(2, 5, 8).size() == 1);
    CHECK(processToLines(3, 5, 8).size() == 1);
    CHECK(processToLines(4, 5, 8).size() == 1);
    CHECK(processToLines(5, 5, 8).size() == 0);
    CHECK(processToLines(6, 5, 8).size() == 0);
    CHECK(processToLines(7, 5, 8).size() == 0);
    CHECK(processToLines(0, 5, 8)[0] == 0);
    CHECK(processToLines(1, 5, 8)[0] == 1);
    CHECK(processToLines(2, 5, 8)[0] == 2);
    CHECK(processToLines(3, 5, 8)[0] == 3);
    CHECK(processToLines(4, 5, 8)[0] == 4);
}

/**
 * @brief Unit test for method calculateDisplsScounts with 4 lines and 4 processes (p == n), ((n mod p) == 0)
 * 
 */
TEST_CASE("Calculate didpls and scounts for MPI_Scatterv: (p == n), ((n mod p) == 0)", "[calculateDisplsScounts]")
{
    int *displs, *scounts;
    int arraySize = 4;
    int processes = 4;
    int myRank = 0;

    calculateDisplsScounts(displs, scounts, arraySize, processes, myRank);

    CHECK(displs[0] == 0);
    CHECK(displs[1] == 4);
    CHECK(displs[2] == 8);
    CHECK(displs[3] == 12);

    CHECK(scounts[0] == 4);
    CHECK(scounts[1] == 4);
    CHECK(scounts[2] == 4);
    CHECK(scounts[3] == 4);

    delete[] displs;
    delete[] scounts;
}

/**
 * @brief Unit test for method calculateDisplsScounts with 8 lines and 4 processes (p < n), ((n mod p) == 0)
 * 
 */
TEST_CASE("Calculate didpls and scounts for MPI_Scatterv: (p < n), ((n mod p) == 0)", "[calculateDisplsScounts]")
{
    int *displs, *scounts;
    int arraySize = 8;
    int processes = 4;
    int myRank = 0;

    calculateDisplsScounts(displs, scounts, arraySize, processes, myRank);

    CHECK(displs[0] == 0);
    CHECK(displs[1] == 16);
    CHECK(displs[2] == 32);
    CHECK(displs[3] == 48);

    CHECK(scounts[0] == 16);
    CHECK(scounts[1] == 16);
    CHECK(scounts[2] == 16);
    CHECK(scounts[3] == 16);

    delete[] displs;
    delete[] scounts;
}

/**
 * @brief Unit test for method calculateDisplsScounts with 7 lines and 4 processes (p < n), ((n mod p) != 0)
 * 
 */
TEST_CASE("Calculate didpls and scounts for MPI_Scatterv: (p < n), ((n mod p) != 0)", "[calculateDisplsScounts]")
{
    int *displs, *scounts;
    int arraySize = 7;
    int processes = 4;
    int myRank = 0;

    calculateDisplsScounts(displs, scounts, arraySize, processes, myRank);

    CHECK(displs[0] == 0);
    CHECK(displs[1] == 14);
    CHECK(displs[2] == 28);
    CHECK(displs[3] == 42);

    CHECK(scounts[0] == 14);
    CHECK(scounts[1] == 14);
    CHECK(scounts[2] == 14);
    CHECK(scounts[3] == 7);

    delete[] displs;
    delete[] scounts;
}

/**
 * @brief Unit test for method calculateDisplsScounts with 4 lines and 8 processes (p > n), ((n mod p) == 0)
 * 
 */
TEST_CASE("Calculate didpls and scounts for MPI_Scatterv: (p > n), ((n mod p) == 0)", "[calculateDisplsScounts]")
{
    int *displs, *scounts;
    int arraySize = 4;
    int processes = 8;
    int myRank = 0;

    calculateDisplsScounts(displs, scounts, arraySize, processes, myRank);

    CHECK(displs[0] == 0);
    CHECK(displs[1] == 4);
    CHECK(displs[2] == 8);
    CHECK(displs[3] == 12);

    CHECK(scounts[0] == 4);
    CHECK(scounts[1] == 4);
    CHECK(scounts[2] == 4);
    CHECK(scounts[3] == 4);

    delete[] displs;
    delete[] scounts;
}

/**
 * @brief Unit test for method calculateDisplsScounts with 5 lines and 8 processes (p > n), ((n mod p) != 0)
 * 
 */
TEST_CASE("Calculate didpls and scounts for MPI_Scatterv: (p > n), ((n mod p) != 0)", "[calculateDisplsScounts]")
{
    int *displs, *scounts;
    int arraySize = 5;
    int processes = 8;
    int myRank = 0;

    calculateDisplsScounts(displs, scounts, arraySize, processes, myRank);

    CHECK(displs[0] == 0);
    CHECK(displs[1] == 5);
    CHECK(displs[2] == 10);
    CHECK(displs[3] == 15);
    CHECK(displs[4] == 20);

    CHECK(scounts[0] == 5);
    CHECK(scounts[1] == 5);
    CHECK(scounts[2] == 5);
    CHECK(scounts[3] == 5);
    CHECK(scounts[4] == 5);

    delete[] displs;
    delete[] scounts;
}

