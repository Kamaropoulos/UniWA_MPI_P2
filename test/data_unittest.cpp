/**
 * @file data_unittest.cpp
 * @author Konstantinos Kamaropoulos (kamaropoulos@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2019-01-05
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "../lib/catch.hpp"

#include "../src/data.h"

#include <iostream>

TEST_CASE("Convert a vector<vector<int> object to int**", "[vector2DToArray2D]")
{
    // // Initialize vector
    // std::vector<std::vector<int>> vec;
    // for (int i = 0; i < 4; i++)
    // {
    //     for (int j = 0; j < 4; j++)
    //     {
    //         vec[i].push_back(j);
    //     }
    // }

    // int **result = vector2DToArray2D(vec);

    // for (int i = 0; i < 4; i++)
    // {
    //     for (int j = 0; j < 4; j++)
    //     {
    //         CHECK(result[i][j] == vec[i][j]);
    //     }
    // }

    // // Clean up
    // // for (int i = 0; i < 4; i++)
    // // {
    // //     delete[] result[i];
    // // }
    // delete[] result;
}

TEST_CASE("Convert 2D array to 1D Row-Major", "[array2DTo1DRowMajor]")
{
    // Initialize array
    int **array = new int *[4];
    for (int i = 0; i < 4; i++)
    {
        array[i] = new int[4];
        for (int j = 0; j < 4; j++)
        {
            array[i][j] = j;
        }
    }

    int *result = array2DTo1DRowMajor(array, 4, 4);

    for (int i = 0; i < (4 * 4); i++)
    {
        CHECK(result[i] == (i % 4));
    }

    // Clean up
    for (int i = 0; i < 4; i++)
    {
        delete[] array[i];
    }
    delete[] array;
    delete[] result;
}

TEST_CASE("Prepare Data for Gathering: 1x4", "[prepareData]")
{
    int elementsPerLine = 4;
    std::vector<std::vector<int>> vec;
    std::vector<int> l0 = {1, 2, 3, 4};
    vec.push_back(l0);

    int *arr = new int[vec.size() * 4];
    prepareData(vec, arr);

    CHECK(arr[0] == vec[0][0]);
    CHECK(arr[1] == vec[0][1]);
    CHECK(arr[2] == vec[0][2]);
    CHECK(arr[3] == vec[0][3]);
}

TEST_CASE("Convert 2D Array to 1D Array in Row-Major Order", "[array2DTo1DRowMajor]")
{
    int **arr2D = new int *[1];
    arr2D[0] = new int[4];

    arr2D[0][0] = 1;
    arr2D[0][1] = 2;
    arr2D[0][2] = 3;
    arr2D[0][3] = 4;

    int *arr1D = array2DTo1DRowMajor(arr2D, 1, 4);

    CHECK(arr1D[0] == arr2D[0][0]);
    CHECK(arr1D[1] == arr2D[0][1]);
    CHECK(arr1D[2] == arr2D[0][2]);
    CHECK(arr1D[3] == arr2D[0][3]);
}

TEST_CASE("Prepare Data for Gathering: 2x4", "[prepareData]")
{
    int elementsPerLine = 4;
    std::vector<std::vector<int>> vec;
    std::vector<int> l0 = {1, 2, 3, 4};
    std::vector<int> l1 = {5, 6, 7, 8};
    vec.push_back(l0);
    vec.push_back(l1);

    int *arr = new int[vec.size() * 4];
    prepareData(vec, arr);

    CHECK(arr[0] == vec[0][0]);
    CHECK(arr[1] == vec[0][1]);
    CHECK(arr[2] == vec[0][2]);
    CHECK(arr[3] == vec[0][3]);
    CHECK(arr[4] == vec[1][0]);
    CHECK(arr[5] == vec[1][1]);
    CHECK(arr[6] == vec[1][2]);
    CHECK(arr[7] == vec[1][3]);
}

TEST_CASE("Check criteria for local data: true", "[checkCriteriaLocal]")
{
    std::vector<std::vector<int>> localData;
    int arraySize = 4;

    std::vector<int> d0 = {12, 3, 4, 1};
    std::vector<int> d1 = {3, 46, 1, 1};
    std::vector<int> d2 = {4, 1, 38, 2};
    std::vector<int> d3 = {3, 2, 1, 25};
    localData.push_back(d0);
    localData.push_back(d1);
    localData.push_back(d2);
    localData.push_back(d3);

    int maxLocal;

    bool resultLocal = checkCriteriaLocal(localData, arraySize, 0, 1, &maxLocal);

    CHECK(resultLocal == true);
    CHECK(maxLocal == 46);
}

TEST_CASE("Check criteria for local data: false", "[checkCriteriaLocal]")
{
    std::vector<std::vector<int>> localData;
    int arraySize = 4;

    std::vector<int> d0 = {12, 3, 4, 1};
    std::vector<int> d1 = {3, 1, 1, 1};
    std::vector<int> d2 = {4, 1, 38, 2};
    std::vector<int> d3 = {3, 2, 1, 25};
    localData.push_back(d0);
    localData.push_back(d1);
    localData.push_back(d2);
    localData.push_back(d3);

    int maxLocal;

    bool resultLocal = checkCriteriaLocal(localData, arraySize, 0, 1, &maxLocal);

    CHECK(resultLocal == false);
    CHECK(maxLocal == 38);
}

TEST_CASE("Calculate Local B Lines: Process 0, 4 Lines, 4 Processes", "[calculateBLocal]")
{
    std::vector<std::vector<int>> localData;
    int arraySize = 4, myRank = 0, max = 12, processes = 4;

    std::vector<int> d0 = {8, 1, 2, 2};
    localData.push_back(d0);

    int min, minX, minY;

    std::vector<std::vector<int>> localB = calculateBLocal(localData, max, arraySize, myRank, processes, &min, &minX, &minY);

    std::vector<std::vector<int>> controlB;

    std::vector<int> c0 = {12, 11, 10, 10};
    controlB.push_back(c0);

    CHECK(localB[0][0] == controlB[0][0]);
    CHECK(localB[0][1] == controlB[0][1]);
    CHECK(localB[0][2] == controlB[0][2]);
    CHECK(localB[0][3] == controlB[0][3]);

    CHECK(min == 10);
    CHECK(minX == 0);
    CHECK(minY == 2);
}

TEST_CASE("Calculate Local B Lines: Process 1, 4 Lines, 4 Processes", "[calculateBLocal]")
{
    std::vector<std::vector<int>> localData;
    int arraySize = 4, myRank = 1, max = 12, processes = 4;

    std::vector<int> d0 = {2, 12, 4, 1};
    localData.push_back(d0);

    int min, minX, minY;

    std::vector<std::vector<int>> localB = calculateBLocal(localData, max, arraySize, myRank, processes, &min, &minX, &minY);

    std::vector<std::vector<int>> controlB;

    std::vector<int> c0 = {10, 12, 8, 11};
    controlB.push_back(c0);

    CHECK(localB[0][0] == controlB[0][0]);
    CHECK(localB[0][1] == controlB[0][1]);
    CHECK(localB[0][2] == controlB[0][2]);
    CHECK(localB[0][3] == controlB[0][3]);

    CHECK(min == 8);
    CHECK(minX == 1);
    CHECK(minY == 2);
}
