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

/**
 * @brief Returns the number of the process a line of the array will be assigned to.
 * 
 * @param line The number of the array to assign. (base 0)
 * @param totalLines The total number of lines in the array.
 * @param processes The total number of processes. (including the root process)
 * @return int The number of the process the passed line of the array will be assigned to.
 */
int lineToProcess(int line, int totalLines, int processes)
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