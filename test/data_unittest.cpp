/**
 * @file data_unittest.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2019-01-05
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "../lib/catch.hpp"

#include "../src/data.h"

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