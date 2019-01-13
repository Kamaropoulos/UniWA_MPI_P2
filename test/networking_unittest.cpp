/**
 * @file networking_unittest.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2019-01-05
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#define CATCH_CONFIG_MAIN

#include "../lib/catch.hpp"

#include "../src/networking.h"

TEST_CASE("[Internal] Line to Process Assignments: (p == n), ((n mod p) == 0)", "[ilineToProcess]")
{
    CHECK(_lineToProcess(0, 4, 4) == 0);
    CHECK(_lineToProcess(1, 4, 4) == 1);
    CHECK(_lineToProcess(2, 4, 4) == 2);
    CHECK(_lineToProcess(3, 4, 4) == 3);
}

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

TEST_CASE("[Internal] Line to Process Assignments: (p > n), ((n mod p) == 0)", "[ilineToProcess]")
{
    CHECK(_lineToProcess(0, 4, 8) == 0);
    CHECK(_lineToProcess(1, 4, 8) == 1);
    CHECK(_lineToProcess(2, 4, 8) == 2);
    CHECK(_lineToProcess(3, 4, 8) == 3);
}

TEST_CASE("[Internal] Line to Process Assignments: (p > n), ((n mod p) != 0)", "[ilineToProcess]")
{
    CHECK(_lineToProcess(0, 5, 8) == 0);
    CHECK(_lineToProcess(1, 5, 8) == 1);
    CHECK(_lineToProcess(2, 5, 8) == 2);
    CHECK(_lineToProcess(3, 5, 8) == 3);
    CHECK(_lineToProcess(4, 5, 8) == 4);
}

TEST_CASE("Line to Process Assignments: (p == n), ((n mod p) == 0)", "[lineToProcess]")
{
    CHECK(lineToProcess(0, 4, 4) == 0);
    CHECK(lineToProcess(1, 4, 4) == 1);
    CHECK(lineToProcess(2, 4, 4) == 2);
    CHECK(lineToProcess(3, 4, 4) == 3);
}

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

TEST_CASE("Line to Process Assignments: (p > n), ((n mod p) == 0)", "[lineToProcess]")
{
    CHECK(lineToProcess(0, 4, 8) == 0);
    CHECK(lineToProcess(1, 4, 8) == 1);
    CHECK(lineToProcess(2, 4, 8) == 2);
    CHECK(lineToProcess(3, 4, 8) == 3);
}

TEST_CASE("Line to Process Assignments: (p > n), ((n mod p) != 0)", "[lineToProcess]")
{
    CHECK(lineToProcess(0, 5, 8) == 0);
    CHECK(lineToProcess(1, 5, 8) == 1);
    CHECK(lineToProcess(2, 5, 8) == 2);
    CHECK(lineToProcess(3, 5, 8) == 3);
    CHECK(lineToProcess(4, 5, 8) == 4);
}


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
