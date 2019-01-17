/**
 * @file main.cpp
 * @author Konstantinos Kamaropoulos (kamaropoulos@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2018-12-25
 * 
 * @copyright Copyright (c) 2018
 * 
 */

#include <vector>

#include <iostream>

#include "mpi.h"

#include "data.h"
#include "networking.h"

#define ROOT_PROCESS 0

#include "utils.h"

int main(int argc, char **argv)
{    
    // The number of processes the code is running on.
    int processes;
    // The rank of the current process.
    int myRank;
    std::vector<std::vector<int>> data;
    std::vector<std::vector<int>> localData;
    // The size of the original array
    int arraySize = 0;
    int max;

    int *displs, *scounts;

    // Initialize MPI.
    MPI_Init(&argc, &argv);

    // Get running processes number and current process rank.
    GetMPIParams(&processes, &myRank);

    // Read data
    ifRoot(ReadData(&data, &arraySize, argc, argv));

    // Broadcast array dimmensions
    broadcastArraySize(&arraySize);

    // Scatter data and get the lines assigned to the current process
    localData = scatterData(data, arraySize, myRank, processes);

    // Check if the matrix meets the criteria
    bool result = checkCriteria(localData, arraySize, myRank, processes, &max);

    // If it doesn't, abort
    if (result == false)
    {
        MPI_Finalize();
        return 0;
    }

    MPI_Barrier(MPI_COMM_WORLD);

    // Calculate the B matrix
    int minLocal, minXLocal, minYLocal;
    calculateB(localData, arraySize, max, myRank, processes, &minLocal, &minXLocal, &minYLocal);

    // Find the min element of B
    int min, minX, minY;
    findMin(minLocal, minXLocal, minYLocal, &min);

    // Print min
    ifRoot({
        std::cout << "min = " << min << std::endl;
    })

    // Exit
    MPI_Finalize();
    return 0;
}
