/**
 * @file networking.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2019-01-05
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include <vector>
#include <algorithm>

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
    return ((line % (processes - 1)) + 1);
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