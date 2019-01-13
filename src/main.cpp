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

struct minloc
{
    int value;
    int rank;
};

/**
 * @brief Returns the number of processes and the rank of the current process.
 * 
 * @param processesCount The address to which the number of the processes will be written.
 * @param rank The address to which the rank of the current process will be written.
 * 
 */
void GetMPIParams(int *processesCount, int *rank)
{
    MPI_Comm_rank(MPI_COMM_WORLD, rank);
    MPI_Comm_size(MPI_COMM_WORLD, processesCount);
}

int main(int argc, char **argv)
{
    // The number of processes the code is running on.
    int processes;

    // The rank of the current process.
    int myRank;

    int *dataArray;

    int *mxn = new int[2];

    // Initialize MPI.
    MPI_Init(&argc, &argv);

    // Get running processes number and current process rank.
    GetMPIParams(&processes, &myRank);

    // Scatter lines
    if (myRank == ROOT_PROCESS)
    {
        std::vector<std::vector<int>> data;

        // Read data from file.
        ReadData(&data, argc, argv);

        mxn[0] = data.size();
        mxn[1] = data[0].size();

        // Add indentification element (last element will be the line number)

        for (int i = 0; i < mxn[0]; i++)
        {
            data[i].push_back(i);
        }

        // Convert data vector to row-major order array
        dataArray = new int[mxn[0] * (mxn[1] + 1)];
        dataArray = array2DTo1DRowMajor(vector2DToArray2D(data), mxn[0], (mxn[1] + 1));
    }

    // Broadcast input dimmensions
    MPI_Bcast(mxn, 2, MPI_INT, 0, MPI_COMM_WORLD);

    int elements = (mxn[1] + 1) * processToLinesCount(myRank, mxn[0], processes);
    int *row = new int[elements];

    int *displs = new int[processes];
    int *scounts = new int[processes];

    int displsTemp = 0;
    for (int i = 0; i < ((processes > mxn[0]) ? mxn[0] : processes); i++)
    {
        displs[i] = i * (processToLinesCount(i, mxn[0], processes)) * (mxn[1] + 1);
        scounts[i] = (processToLinesCount(i, mxn[0], processes)) * (mxn[1] + 1);
        if ((processes < mxn[0]) && ((mxn[0] % processes) != 0))
        {
            displs[i] += displsTemp;
            displsTemp = (processToLinesCount(i, mxn[0], processes)) * (mxn[1] + 1);
        }
    }

    // if (myRank == 8)
    // {
    //     std::cout << "Process " << myRank << ": displs: ";
    //     for (int o = 0; o < processes; o++)
    //     {
    //         std::cout << displs[o] << " ";
    //     }
    //     std::cout << std::endl;
    //     std::cout << "Process " << myRank << ": scounts: ";
    //     for (int o = 0; o < processes; o++)
    //     {
    //         std::cout << scounts[o] << " ";
    //     }
    //     std::cout << std::endl;
    // }

    MPI_Scatterv(dataArray, scounts, displs, MPI_INT, row, *scounts, MPI_INT, 0, MPI_COMM_WORLD);

    delete[] displs;
    delete[] scounts;

    // MPI_Barrier(MPI_COMM_WORLD);

    std::vector<std::vector<int>> localLines = arrayRowMajorTo2DVector(row, processToLinesCount(myRank, mxn[0], processes), mxn[1] + 1);

    int result = 0;

    int maxLocal;

    // For each line:
    for (int i = 0; i < localLines.size(); i++)
    {
        // check if it meets the criteria
        int line = localLines[i][mxn[1]];
        int diagonalElement = localLines[i][line];

        if (i == 0)
        {
            maxLocal = diagonalElement;
        }
        else
        {
            maxLocal = (abs(diagonalElement) > maxLocal) ? diagonalElement : maxLocal;
        }

        // Calculate sum
        int sum = 0;
        for (int j = 0; j < mxn[1]; j++)
        {
            if (j != line)
            {
                sum += abs(localLines[i][j]);
            }
        }

        bool ok = diagonalElement >= sum;

        if (ok)
        {
            result += 1;
        }
    }

    int globalResult;
    MPI_Reduce(&result, &globalResult, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    bool abortP = false;
    // print whether it is strictly diagonally dominant to the screen
    if (myRank == ROOT_PROCESS)
    {
        if (globalResult == mxn[0])
        {
            abortP = false;
            std::cout << "yes" << std::endl;
            MPI_Bcast(&abortP, 1, MPI_CXX_BOOL, 0, MPI_COMM_WORLD);
        }
        else
        {
            std::cout << "no" << std::endl;
            abortP = true;
            MPI_Bcast(&abortP, 1, MPI_CXX_BOOL, 0, MPI_COMM_WORLD);
            MPI_Finalize();
            return 0;
        }
    }
    else
    {
        MPI_Bcast(&abortP, 1, MPI_CXX_BOOL, 0, MPI_COMM_WORLD);
        if (abortP)
        {
            MPI_Finalize();
            return 0;
        }
    }

    MPI_Barrier(MPI_COMM_WORLD);

    // Find diagonal max

    int maxGlobal;

    MPI_Allreduce(&maxLocal, &maxGlobal, 1, MPI_INT, MPI_MAX, MPI_COMM_WORLD);
    if (myRank == ROOT_PROCESS)
        std::cout << "max = " << maxGlobal << std::endl;

    // Calculate new matrix

    std::vector<int> linesToFind = processToLines(myRank, mxn[0], processes);
    std::vector<std::vector<int>> localB;

    int minLocal;
    int minI = -1, minJ = -1;

    for (int i = 0; i < linesToFind.size(); i++)
    {
        std::vector<int> line;

        for (int j = 0; j < mxn[1]; j++)
        {
            if (linesToFind[i] != j)
            {
                line.push_back(maxGlobal - abs(localLines[i][j]));
            }
            else
            {
                line.push_back(maxGlobal);
            }
            if ((i == 0) && (j == 0))
            {
                minLocal = line[0];
            }
            else
            {
                if (line[j] < minLocal)
                {
                    minLocal = line[j];
                    minI = linesToFind[i];
                    minJ = j;
                }
            }
        }

        localB.push_back(line);
    }

    // for (int i = 0; i < linesToFind.size(); i++)
    // {
    //     std::cout << "Line " << linesToFind[i] << ": ";

    //     for (int j = 0; j < mxn[1]; j++)
    //     {
    //         std::cout << localB[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }

    MPI_Barrier(MPI_COMM_WORLD);

    displs = new int[processes];
    scounts = new int[processes];

    for (int i = 0; i < ((processes > mxn[0]) ? mxn[0] : processes); i++)
    {
        displs[i] = i * (processToLinesCount(i, mxn[0], processes)) * (mxn[1]);
        scounts[i] = (processToLinesCount(i, mxn[0], processes)) * (mxn[1]);
        if ((processes < mxn[0]) && ((mxn[0] % processes) != 0))
        {
            displs[i] += displsTemp;
            displsTemp = (processToLinesCount(i, mxn[0], processes)) * (mxn[1]);
        }
    }
    int **tempArr2D = vector2DToArray2D(localB);
    int *localBRowMajor = array2DTo1DRowMajor(tempArr2D, linesToFind.size(), mxn[1]);

    int *b = new int[mxn[0] * mxn[1]];

    // MPI_Scatterv(dataArray, scounts, displs, MPI_INT, row, *scounts, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Gatherv(localBRowMajor, linesToFind.size() * mxn[0], MPI_INT, b, scounts, displs, MPI_INT, 0, MPI_COMM_WORLD);

    std::vector<std::vector<int>> vecB = arrayRowMajorTo2DVector(b, mxn[0], mxn[1]);

    if (myRank == ROOT_PROCESS)
    {
        std::cout << "B = [" << std::endl;
        for (int i = 0; i < mxn[0]; i++)
        {

            for (int j = 0; j < mxn[1]; j++)
            {
                std::cout << b[(i * mxn[0]) + j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "]" << std::endl;
    }

    MPI_Barrier(MPI_COMM_WORLD);

    // // Find min
    struct minloc minGlobal;
    int min;
    MPI_Reduce(&minLocal, &min, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);
    if (myRank == ROOT_PROCESS)
    {
        std::cout << "min = " << min << std::endl;
    }

    MPI_Barrier(MPI_COMM_WORLD);

    MPI_Allreduce(&minLocal, &minGlobal, 1, MPI_2INT, MPI_MINLOC, MPI_COMM_WORLD);

    if (myRank == ROOT_PROCESS)
    {
        std::cout << "min = " << minGlobal.value << " at process " << minGlobal.rank << std::endl;
    }

    MPI_Barrier(MPI_COMM_WORLD);

    if (myRank == minGlobal.rank)
    {

        std::cout << minGlobal.rank << std::endl;
        std::cout << "[" << minI << "][" << minJ << "]" << std::endl;
    }
    // processes continue to find the min of the new matrix

    // gather the new matrix
    // print min and it's position to the matrix

    MPI_Finalize();

    return 0;
}
