/**
 * @file networking.cpp
 * @author Konstantinos Kamaropoulos (kamaropoulos@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2019-01-05
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "networking.h"
#include "data.h"
#include "mpi.h"

#define ROOT_PROCESS 0
#include "utils.h"

#include <algorithm>

#include <iostream>

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

/**
 * @brief Returns the number of the process a line of the array will be assigned to.
 * 
 * @param line The number of the line of the array to assign. (base 0)
 * @param totalLines The total number of lines in the array.
 * @param processes The total number of processes. (including the root process)
 * @return int The number of the process the passed line of the array will be assigned to.
 */
int lineToProcess(int line, int totalLines, int processes)
{
    // Create a vector holding the number of the process each line will be assigned to.
    // The index will be the line number and the data the process number;
    std::vector<int> lineAssignments;

    // What we want to do here is assign each line to a process based on how many
    // there are and then sort the array so all the lines of a process are continuous
    // for easier manipulation.

    // Fill the vector with the assignments based on the modulo of the line.
    for (int _line = 0; _line < totalLines; _line++)
        lineAssignments.push_back(_lineToProcess(_line, totalLines, processes));

    // Sort the vector so all the process occurances are together.
    std::sort(lineAssignments.begin(), lineAssignments.end());

    return lineAssignments[line];
}

/**
 * @brief [Internal] Line to process assignments based on the modulo of the line.
 * 
 * @param line The number of the line of the array to assign. (base 0)
 * @param totalLines The total number of lines in the array.
 * @param processes The total number of processes. (including the root process)
 * @return int The number of the process the passed line of the array will be 
 *             assigned to based on the modulo of the line.
 */
int _lineToProcess(int line, int totalLines, int processes)
{
    return ((line % (processes)));
}

/**
 * @brief Returns a vector with the numbers (base 0) of the lines a process will be assigned.
 * 
 * @param process The number of the process we want to get the lines it will be assigned.
 * @param totalLines The total number of lines in the array.
 * @param processes The total number of processes. (including the root process)
 * @return std::vector<int> An std::vector<int> object containing the numbers (base 0)
 *                          of the lines the passed process will be assigned.
 */
std::vector<int> processToLines(int process, int totalLines, int processes)
{
    std::vector<int> lines;

    for (int line = 0; line < totalLines; line++)
    {
        if (lineToProcess(line, totalLines, processes) == process)
        {
            lines.push_back(line);
        }
    }

    return lines;
}

/**
 * @brief The number of lines that will be assigned to a process.
 * 
 * @param process The number of the process
 * @param totalLines The total number of lines in the array.
 * @param processes The total number of processes. (including the root process)
 * @return int The number of lines the passed process will be assigned.
 */
int processToLinesCount(int process, int totalLines, int processes)
{
    int linesCount = 0;

    for (int i = 0; i < totalLines; i++)
        if (_lineToProcess(i, totalLines, processes) == process)
            linesCount++;

    return linesCount;
}

void broadcastArraySize(int *arraySize)
{
    MPI_Bcast(arraySize, 1, MPI_INT, 0, MPI_COMM_WORLD);
}

void calculateDisplsScounts(int *&displs, int *&scounts, int arraySize, int processes, int myRank)
{
    displs = new int[processes];
    scounts = new int[processes];

    displs[0] = 0;
    scounts[0] = (arraySize * processToLinesCount(0, arraySize, processes));

    for (int i = 1; i < processes; i++)
    {
        if (processToLinesCount(i, arraySize, processes) > 0)
        {
            displs[i] = displs[i - 1] + scounts[i - 1];
            scounts[i] = (arraySize * processToLinesCount(i, arraySize, processes));
        }
        else
        {
            displs[i] = 0;
            scounts[i] = 0;
        }
    }
}

std::vector<std::vector<int>> scatterData(std::vector<std::vector<int>> data, int arraySize, int myRank, int processes)
{

    // An array to hold the array in row major form
    int *dataArray;

    // Convert data vector to row-major order array
    ifRoot({
        dataArray = new int[data.size() * arraySize];
        prepareData(data, dataArray);
    });

    int *displs, *scounts;
    calculateDisplsScounts(displs, scounts, arraySize, processes, myRank);

    int elements = (arraySize)*processToLinesCount(myRank, arraySize, processes);
    int *dataOut = new int[elements];

    MPI_Barrier(MPI_COMM_WORLD);

    MPI_Scatterv(dataArray, scounts, displs, MPI_INT, dataOut, *scounts, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Barrier(MPI_COMM_WORLD);

    delete[] displs;
    delete[] scounts;

    std::vector<std::vector<int>> localData = arrayRowMajorTo2DVector(dataOut, processToLinesCount(myRank, arraySize, processes), arraySize);

    return localData;
}

int calculateMax(int maxLocal)
{
    int max;
    MPI_Allreduce(&maxLocal, &max, 1, MPI_INT, MPI_MAX, MPI_COMM_WORLD);
    return max;
}

bool checkCriteria(std::vector<std::vector<int>> localData, int arraySize, int myRank, int processes, int *max)
{
    int maxLocal;
    int resultLocal = checkCriteriaLocal(localData, arraySize, myRank, processes, &maxLocal);

    int globalResult;

    MPI_Reduce(&resultLocal, &globalResult, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    bool abortP = false;

    ifRoot({
        if (globalResult == processes)
        {
            abortP = false;
            std::cout << "yes" << std::endl;
        }
        else
        {
            abortP = true;
            std::cout << "no" << std::endl;
        }
    })

        MPI_Barrier(MPI_COMM_WORLD);

    MPI_Bcast(&abortP, 1, MPI_CXX_BOOL, 0, MPI_COMM_WORLD);

    if (abortP)
    {
        return false;
    }
    else
    {
        *max = calculateMax(maxLocal);
        ifRoot({ std::cout << "max = " << *max << std::endl; });
        return true;
    }
}

void calculateB(std::vector<std::vector<int>> localData, int arraySize, int max, int myRank, int processes, int *minLocal, int *minXLocal, int *minYLocal)
{
    std::vector<std::vector<int>> localBLines = calculateBLocal(localData, max, arraySize, myRank, processes, minLocal, minXLocal, minYLocal);

    MPI_Barrier(MPI_COMM_WORLD);

    int *localBLinesArr = new int[localBLines.size() * arraySize];
    prepareData(localBLines, localBLinesArr);

    int *displs, *scounts;
    calculateDisplsScounts(displs, scounts, arraySize, processes, myRank);

    int *b;
    ifRoot({
        b = new int[arraySize * arraySize];
    });

    MPI_Gatherv(localBLinesArr, processToLinesCount(myRank, arraySize, processes) * arraySize, MPI_INT, b, scounts, displs, MPI_INT, 0, MPI_COMM_WORLD);

    delete[] displs;
    delete[] scounts;

    delete[] localBLinesArr;

    ifRoot({
        printB(b, arraySize);
    });

    delete[] b;
}

void findMin(int minLocal, int minXLocal, int minYLocal, int *min, int *minX, int *minY, int myRank)
{
    MPI_Allreduce(&minLocal, min, 1, MPI_INT, MPI_MIN, MPI_COMM_WORLD);
}