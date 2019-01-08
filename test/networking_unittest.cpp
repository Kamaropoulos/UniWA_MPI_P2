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

TEST_CASE("[Internal] Line to Process Assignments: 3 lines, 4 processes", "[ilineToProcess]")
{
    CHECK(_lineToProcess(0, 3, 4) == 1);
    CHECK(_lineToProcess(1, 3, 4) == 2);
    CHECK(_lineToProcess(2, 3, 4) == 3);
}

TEST_CASE("[Internal] Line to Process Assignments: 4 lines, 4 processes", "[ilineToProcess]")
{
    CHECK(_lineToProcess(0, 4, 4) == 1);
    CHECK(_lineToProcess(1, 4, 4) == 2);
    CHECK(_lineToProcess(2, 4, 4) == 3);
    CHECK(_lineToProcess(3, 4, 4) == 1);
}

TEST_CASE("[Internal] Line to Process Assignments: 2 lines, 4 processes", "[ilineToProcess]")
{
    CHECK(_lineToProcess(0, 2, 4) == 1);
    CHECK(_lineToProcess(1, 2, 4) == 2);
}

TEST_CASE("[Internal] Line to Process Assignments: 1 line, 8 processes", "[ilineToProcess]")
{
    CHECK(_lineToProcess(0, 1, 8) == 1);
}

TEST_CASE("[Internal] Line to Process Assignments: 8 lines, 4 processes", "[ilineToProcess]"){
    CHECK(_lineToProcess(3, 8, 4) == 1);
    CHECK(_lineToProcess(5, 8, 4) == 3);
    CHECK(_lineToProcess(7, 8, 4) == 2);
}

TEST_CASE("Line to Process Assignments: 3 lines, 4 processes", "[lineToProcess]")
{
    CHECK(lineToProcess(0, 3, 4) == 1);
    CHECK(lineToProcess(1, 3, 4) == 2);
    CHECK(lineToProcess(2, 3, 4) == 3);
}

TEST_CASE("Line to Process Assignments: 4 lines, 4 processes", "[lineToProcess]")
{
    CHECK(lineToProcess(0, 4, 4) == 1);
    CHECK(lineToProcess(1, 4, 4) == 1);
    CHECK(lineToProcess(2, 4, 4) == 2);
    CHECK(lineToProcess(3, 4, 4) == 3);
}

TEST_CASE("Line to Process Assignments: 2 lines, 4 processes", "[lineToProcess]")
{
    CHECK(lineToProcess(0, 2, 4) == 1);
    CHECK(lineToProcess(1, 2, 4) == 2);
}

TEST_CASE("Line to Process Assignments: 1 line, 8 processes", "[lineToProcess]")
{
    CHECK(lineToProcess(0, 1, 8) == 1);
}

TEST_CASE("Line to Process Assignments: 8 lines, 4 processes", "[lineToProcess]"){
    CHECK(lineToProcess(0, 8, 4) == 1);
    CHECK(lineToProcess(1, 8, 4) == 1);
    CHECK(lineToProcess(2, 8, 4) == 1);
    CHECK(lineToProcess(3, 8, 4) == 2);
    CHECK(lineToProcess(4, 8, 4) == 2);
    CHECK(lineToProcess(5, 8, 4) == 2);
    CHECK(lineToProcess(6, 8, 4) == 3);
    CHECK(lineToProcess(7, 8, 4) == 3);
}

TEST_CASE("Lines assigned to a process", "[processToLines]")
{
    CHECK(processToLines(0, 5, 4).size() == 0);
    CHECK(processToLines(1, 5, 4).size() == 2);
    CHECK(processToLines(2, 5, 4).size() == 2);
    CHECK(processToLines(3, 5, 4).size() == 1);

    CHECK(processToLines(1, 5, 4)[0] == 0);
    CHECK(processToLines(1, 5, 4)[1] == 1);

    CHECK(processToLines(2, 5, 4)[0] == 2);
    CHECK(processToLines(2, 5, 4)[1] == 3);

    
    CHECK(processToLines(3, 5, 4)[0] == 4);


    CHECK(processToLines(0, 2, 4).size() == 0);
    CHECK(processToLines(3, 2, 4).size() == 0);
}

// TODO: Add test cases for processToLinesCount