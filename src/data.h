/**
 * @file data.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2018-12-27
 * 
 * @copyright Copyright (c) 2018
 * 
 */

#include <vector>

void ReadData(std::vector<std::vector<int>> *, int*, int, char **);

int **vector2DToArray2D(std::vector<std::vector<int>>);

int *array2DTo1DRowMajor(int **arr2d, int m, int n);

std::vector<std::vector<int>> arrayRowMajorTo2DVector(int *arr, int m, int n);

void prepareData(std::vector<std::vector<int>> data, int *&dataArray);

int checkCriteriaLocal(std::vector<std::vector<int>> localData, int arraySize, int myRank, int processes, int *maxLocal);

std::vector<std::vector<int>> calculateBLocal(std::vector<std::vector<int>> localData, int max, int arraySize, int myRank, int processes, int *min, int *minX, int *minY);

void printB(int *b, int arraySize);
