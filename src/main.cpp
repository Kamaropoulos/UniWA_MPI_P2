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

#include "mpi.h"

int main(int argc, char const *argv[])
{
    // Read matrix from the 'matrix.in' file

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
