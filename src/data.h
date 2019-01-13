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

void ReadData(std::vector<std::vector<int>> *, int, char **);

int **vector2DToArray2D(std::vector<std::vector<int>>);

int *array2DTo1DRowMajor(int **arr2d, int m, int n);

std::vector<std::vector<int>> arrayRowMajorTo2DVector(int* arr, int m, int n);