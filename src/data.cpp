/**
 * @file data.cpp
 * @author Konstantinos Kamaropoulos (kamaropoulos@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2018-12-27
 * 
 * @copyright Copyright (c) 2018
 * 
 */

#define DEFAULT_FILENAME "matrix.in"

#include <vector>
#include <string>

#include <stdexcept>

#include <sys/stat.h>

#include <sstream>
#include <fstream>

#include <iostream>

#include "networking.h"

/**
 * @brief Check if a file with the given name exists
 * 
 * @param name [in] The name of the file to check
 * @return true The file exists
 * @return false The file doesn't exist
 */
inline bool fileExists(const std::string &name)
{
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}

/**
 * @brief Decide which filename should be used to read the data from
 * 
 * @param argc [in] The number of command line arguments
 * @param argv [in] The command line arguments
 * @return std::string The filename to use for reading the data
 */
std::string inputFileName(int argc, char **argv)
{
    std::string filename;
    // Check if file name was passed
    switch (argc)
    {
    case 1:
        // No parameter passed, fallback to default filename
        return DEFAULT_FILENAME;
        break;

    case 2:
        // We got one parameter, check if it's an existing file
        filename = argv[1];
        if (fileExists(filename))
        {
            return filename;
        }
        else
        {
            throw std::runtime_error("Could not open file \"" + filename + "\"");
        }

    default:
        throw std::runtime_error("Incorrect command usage!");
        break;
    }
}

/**
 * @brief Determines the source to read from, reads and writes the data to a 2D vector
 * 
 * @param data [out] A pointer to an <std::vector<std::vector<int>> collection to write the data to
 * @param argc [in] The number of command line arguments
 * @param argv [in] The command line arguments
 */
void ReadData(std::vector<std::vector<int>> *data, int *arraySize, int argc, char **argv)
{
    std::string filename;

    try
    {
        filename = inputFileName(argc, argv);
    }
    catch (std::exception &e)
    {
        std::cout << "\033[1;31m"
                  << "Error: " << e.what() << "\033[0m"
                  << std::endl;
    }

    // An input file stream used to read data from config.txt.
    std::ifstream inputFile(filename);

    // If the file is opened sucessfully
    if (inputFile.is_open())
    {
        // A temporary variable to store numbers from the input file.
        int tmpNumber;

        std::string line;

        // While inputFile still has lines, put them on line.
        while (std::getline(inputFile, line))
        {
            std::istringstream iss(line);
            std::vector<int> tempv;

            while (iss >> tmpNumber)
            {
                tempv.push_back(tmpNumber);
            }

            data->push_back(tempv);
        }

        // We are at the end of the file, close it as we won't need it anymore.
        inputFile.close();
    }

    *arraySize = data->size();
}

/**
 * @brief Returns a 2D Array with the data of the passed 2D Vector
 * 
 * @param v2d [in] The 2D Vector to get the data from
 * @return int** A pointer to the 2D array with the data from the vector
 */
int **vector2DToArray2D(std::vector<std::vector<int>> v2d)
{
    // Create a pointer for a 2D array
    int **arr2d = new int *[v2d.size()];

    // For each line in the vector:
    for (int i = 0; i < v2d.size(); i++)
    {
        arr2d[i] = new int[v2d[i].size()];

        for (int j = 0; j < v2d[i].size(); j++)
        {
            arr2d[i][j] = v2d[i][j];
        }
    }

    return arr2d;
}

/**
 * @brief Converts a 2D array into an 1D array in row-major order
 * 
 * @param arr2d [in] A 2D array
 * @param m [in] The number of lines in the 2D array
 * @param n [in] The number of columns in the 2D array
 * @return int* A pointer to an array with the data of the passed
 *              2D array in row-major order
 */
int *array2DTo1DRowMajor(int **arr2d, int m, int n)
{
    // Create a pointer for an array
    int *arr = new int[m * n];

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            arr[i * n + j] = arr2d[i][j];
        }
    }

    return arr;
}

/**
 * @brief Converts an array in row-major order to a 2D vector
 * 
 * @param arr [in] A pointer to an array
 * @param m [in] The number of lines in the array
 * @param n [in] The number of columns in the array
 * @return std::vector<std::vector<int>> A vector with the row-major order data 
 *                                       from the passed array
 */
std::vector<std::vector<int>> arrayRowMajorTo2DVector(int *arr, int m, int n)
{
    std::vector<std::vector<int>> vec;

    int index = 0;
    for (int i = 0; i < m; i++)
    {
        std::vector<int> vecLine;

        for (int j = 0; j < n; j++)
        {
            vecLine.push_back(arr[index++]);
        }

        vec.push_back(vecLine);
    }

    return vec;
}

/**
 * @brief Convert data in 2D vector to an 1D array with the data of the original
 *        vector in row-major order for use with MPI communication methods
 * 
 * @param data [in] A 2D vector
 * @param dataArray [in] A pointer to an array with the size of the data already allocated
 */
void prepareData(std::vector<std::vector<int>> data, int *&dataArray)
{
    int **arr2D = vector2DToArray2D(data);
    dataArray = array2DTo1DRowMajor(arr2D, data.size(), data[0].size());
}

/**
 * @brief Check if the lines present in a process meet the strictly diagonally
 *        dominant criteria
 * 
 * @param localData [in] A 2D vector holding the lines the process has
 * @param arraySize [in] The total number of lines in all processes
 * @param myRank [in] The rank of the process
 * @param processes [in] The total number of processes
 * @param maxLocal [out] The local max found in the local lines
 * @return int 0 if the local lines meet the criteria;
 *             1 if the local lines do not meet the criteria 
 */
int checkCriteriaLocal(std::vector<std::vector<int>> localData, int arraySize, int myRank, int processes, int *maxLocal)
{

    int result = 0;

    int maxLocalTemp;

    std::vector<int> lines = processToLines(myRank, arraySize, processes);

    // For each line:
    for (int i = 0; i < localData.size(); i++)
    {

        int line = lines[i];
        int diagonalElement = localData[i][line];

        if (i == 0)
        {
            maxLocalTemp = diagonalElement;
        }
        else
        {
            maxLocalTemp = (abs(diagonalElement) > maxLocalTemp) ? diagonalElement : maxLocalTemp;
        }

        // Calculate sum
        int sum = 0;
        for (int j = 0; j < arraySize; j++)
        {
            if (j != line)
            {
                sum += abs(localData[i][j]);
            }
        }

        bool ok = diagonalElement >= sum;

        if (ok)
        {
            result += 1;
        }
    }

    *maxLocal = maxLocalTemp;

    if (result == lines.size())
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief Calculate the value of a cell of the B matrix
 * 
 * @param a [in] The element of matrix A in the same position for which we want to
 *          calculate the value of B
 * @param max [in] The max element of the A matrix
 * @param x [in] The line we want to find an element for
 * @param y [in] The column we want to find an element for
 * @return int The calculated value of the requested cell
 */
int calculateBCell(int a, int max, int x, int y)
{
    if (x == y)
        return max;
    return max - abs(a);
}

/**
 * @brief Calculate the lines of B assigned to a process
 * 
 * @param localData [in] The local lines of matrix A
 * @param max [in] The max value found on matrix A
 * @param arraySize [in] The total number of lines in all processes
 * @param myRank [in] The rank of the process
 * @param processes [in] The total number of processes
 * @param min [out] The min item found on all lines calculated by the current process
 * @param minX [out] The X coordinate of the min item on all lines calculated by the current process
 * @param minY [out] The Y coordinate of the min item on all lines calculated by the current process
 * @return std::vector<std::vector<int>> A 2D vector holding the lines calculated by the current process
 */
std::vector<std::vector<int>> calculateBLocal(std::vector<std::vector<int>> localData, int max, int arraySize, int myRank, int processes, int *min, int *minX, int *minY)
{
    std::vector<std::vector<int>> localB;
    std::vector<int> lines = processToLines(myRank, arraySize, processes);

    *minX = -1;
    *minY = -1;

    for (int i = 0; i < lines.size(); i++)
    {
        std::vector<int> line;

        for (int j = 0; j < arraySize; j++)
        {

            line.push_back(calculateBCell(localData[i][j], max, lines[i], j));

            if ((i == 0) && (j == 0))
            {
                *min = line[0];
                *minX = 0;
                *minY = 0;
            }
            else
            {
                if (line[j] < *min)
                {
                    *min = line[j];
                    *minX = lines[i];
                    *minY = j;
                }
            }
        }
        localB.push_back(line);
    }

    return localB;
}

/**
 * @brief Prints matrix B
 * 
 * @param b [in] A pointer to an array in row-major order
 * @param arraySize [in] The total number of lines in all processes
 */
void printB(int *b, int arraySize)
{
    for (int i = 0; i < arraySize; i++)
    {
        for (int j = 0; j < arraySize; j++)
        {

            std::cout << b[(i * arraySize) + j] << " ";
        }
        std::cout << std::endl;
    }
}