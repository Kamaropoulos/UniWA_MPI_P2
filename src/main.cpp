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

#include "mpi.h"

#include "data.h"
#include "networking.h"

#define ROOT_PROCESS 0

#include "utils.h"

struct minloc
{
    double value;
    int rank;
};

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

    localData = scatterData(data, arraySize, myRank, processes);

    MPI_Barrier(MPI_COMM_WORLD);

    bool result = checkCriteria(localData, arraySize, myRank, processes, &max);

    if (result == false)
    {
        MPI_Finalize();
        return 0;
    }

    MPI_Barrier(MPI_COMM_WORLD);

    // ------ ^ OK ------
    int minLocal, minXLocal, minYLocal;
    calculateB(localData, arraySize, max, myRank, processes, &minLocal, &minXLocal, &minYLocal);
    
    // std::vector<int> linesToFind = processToLines(myRank, arraySize, processes);
    // std::vector<std::vector<int>> localB;

    // int minLocal;
    // int minI = -1, minJ = -1;

    // for (int i = 0; i < linesToFind.size(); i++)
    // {
    //     std::vector<int> line;

    //     for (int j = 0; j < arraySize; j++)
    //     {
    //         if (linesToFind[i] != j)
    //         {
    //             line.push_back(max - abs(localData[i][j]));
    //         }
    //         else
    //         {
    //             line.push_back(max);
    //         }
    //         if ((i == 0) && (j == 0))
    //         {
    //             minLocal = line[0];
    //         }
    //         else
    //         {
    //             if (line[j] < minLocal)
    //             {
    //                 minLocal = line[j];
    //                 minI = linesToFind[i];
    //                 minJ = j;
    //             }
    //         }
    //     }

    //     localB.push_back(line);
    // }

    // for (int i = 0; i < linesToFind.size(); i++)
    // {
    //     std::cout << "Line " << linesToFind[i] << ": ";

    //     for (int j = 0; j < arraySize; j++)
    //     {
    //         std::cout << localB[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }










    // MPI_Barrier(MPI_COMM_WORLD);

    // displs = new int[processes];
    // scounts = new int[processes];

    // int displsTemp = 0;
    // for (int i = 0; i < ((processes > arraySize) ? arraySize : processes); i++)
    // {
    //     displs[i] = i * (processToLinesCount(i, arraySize, processes)) * (arraySize);
    //     scounts[i] = (processToLinesCount(i, arraySize, processes)) * (arraySize);
    //     if ((processes < arraySize) && ((arraySize % processes) != 0))
    //     {
    //         displs[i] += displsTemp;
    //         displsTemp = (processToLinesCount(i, arraySize, processes)) * (arraySize);
    //     }
    // }
    // int **tempArr2D = vector2DToArray2D(localB);
    // int *localBRowMajor = array2DTo1DRowMajor(tempArr2D, linesToFind.size(), arraySize);

    // int *b = new int[arraySize * arraySize];

    // // MPI_Scatterv(dataArray, scounts, displs, MPI_INT, row, *scounts, MPI_INT, 0, MPI_COMM_WORLD);
    // MPI_Gatherv(localBRowMajor, linesToFind.size() * arraySize, MPI_INT, b, scounts, displs, MPI_INT, 0, MPI_COMM_WORLD);

    // std::vector<std::vector<int>> vecB = arrayRowMajorTo2DVector(b, arraySize, arraySize);

    // if (myRank == ROOT_PROCESS)
    // {
    //     std::cout << "B = [" << std::endl;
    //     for (int i = 0; i < arraySize; i++)
    //     {

    //         for (int j = 0; j < arraySize; j++)
    //         {
    //             std::cout << b[(i * arraySize) + j] << " ";
    //         }
    //         std::cout << std::endl;
    //     }
    //     std::cout << "]" << std::endl;
    // }

    // MPI_Barrier(MPI_COMM_WORLD);

    int min, minX, minY;
    findMin(minLocal, minXLocal, minYLocal, &min, &minX, &minY, myRank);

    ifRoot({
        std::cout << "min = " << min << std::endl;
    })

    // // // Find min
    // struct minloc minGlobal;
    // int min;

    // // MPI_Reduce(&minLocal, &min, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);
    // MPI_Allreduce(&minLocal, &minGlobal, 1, MPI_DOUBLE_INT, MPI_MINLOC, MPI_COMM_WORLD);

    // // if (myRank == ROOT_PROCESS)
    // // {
    // //     std::cout << minGlobal.rank << std::endl;
    // // }

    // MPI_Barrier(MPI_COMM_WORLD);

    // if (myRank == minGlobal.rank - 1)
    // {
    //     std::cout << "min = B[" << minI << "][" << minJ << "] = " << minLocal << std::endl;
    // }
    // // processes continue to find the min of the new matrix

    // gather the new matrix
    // print min and it's position to the matrix

    MPI_Finalize();

    return 0;
}
