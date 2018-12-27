/**
 * @file main.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2018-12-25
 * 
 * @copyright Copyright (c) 2018
 * 
 */

#include <vector>

#include <iostream>

// #include "mpi.h"

#include "data.h"

int main(int argc, char const *argv[])
{
    std::vector<std::vector<int>> data;

    ReadData(&data, argc, argv);

    for (int i = 0; i < data.size(); i++)
    {
        for (int j = 0; j < data[0].size(); j++)
        {
            std::cout << data[i][j] << " ";
        }
        std::cout << std::endl;
    }

    // Get comm world info

    // Scatter lines

    // For each line:
    // check if it meets the criteria
    // send the results to 0

    // gather the results

    // print whether it is strictly diagonally dominant to the screen

    // if it is:
    // ask processes to find the max
    // gather the results
    // print the max

    // broadcast the max to the processes along with which line they should generate
    // gather the lines and print the lines

    // processes continue to find the min of the new matrix

    // gather the results
    // print min and it's position to the matrix

    return 0;
}
