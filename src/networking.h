/**
 * @file networking.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2019-01-05
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include <vector>

void GetMPIParams(int *processesCount, int *rank);

int _lineToProcess(int line, int totalLines, int processes);

int lineToProcess(int line, int totalLines, int processes);

std::vector<int> processToLines(int process, int totalLines, int processes);

int processToLinesCount(int process, int totalLines, int processes);

void broadcastArraySize(int *arraySize);

void scatterData(std::vector<std::vector<int>> data);

void calculateDisplsScounts(int *&, int *&, int, int, int);

std::vector<std::vector<int>> scatterData(std::vector<std::vector<int>> data, int arraySize, int myRank, int processes);

bool checkCriteria(std::vector<std::vector<int>> localData, int arraySize, int myRank, int processes, int *maxLocal);

void calculateB(std::vector<std::vector<int>> localData, int arraySize, int max, int myRank, int processes, int *minLocal, int *minXLocal, int *minYLocal);

void findMin(int minLocal, int minXLocal, int minYLocal, int *min, int *minX, int *minY, int myRank);