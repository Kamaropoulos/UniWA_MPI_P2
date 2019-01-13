/**
 * @file data.cpp
 * @author your name (you@domain.com)
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

/**
 * @brief Check if a file with the given name exists
 * 
 * @param name The name of the file to check
 * @return true The file exists
 * @return false The file doesn't exist
 */
inline bool fileExists(const std::string &name)
{
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}

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
 * @param data A pointer to an <std::vector<std::vector<int>> collection to write the data to
 * @param argc 
 * @param argv 
 */
void ReadData(std::vector<std::vector<int>> *data, int argc, char **argv)
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
}

/**
 * @brief Returns a 2D Array with the data of the passed 2D Vector
 * 
 * @tparam T 
 * @param v2d The input 2D Vector
 * @return T** The 2D array with the data from the vector
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

std::vector<std::vector<int>> arrayRowMajorTo2DVector(int* arr, int m, int n){
    std::vector<std::vector<int>> vec;
    
    int index = 0;
    for(int i = 0; i < m; i++)
    {
        std::vector<int> vecLine;
        
        for(int j = 0; j < n; j++)
        {
            vecLine.push_back(arr[index++]);
        }

        vec.push_back(vecLine);        
    }

    return vec;    
}