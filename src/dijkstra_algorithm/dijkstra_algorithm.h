#ifndef ALGORITHMS_DIJKSTRA_ALGORITHM_H
#define ALGORITHMS_DIJKSTRA_ALGORITHM_H

#include <queue>
#include <iostream>
#include <string>
#include <vector>

const int SIZE = 6;

std::string readPath(char *argv[]);

std::vector<std::string> readFile(const std::string &path);

void initialTable(std::queue<std::string> &file, int table[SIZE][SIZE]);

#endif //ALGORITHMS_DIJKSTRA_ALGORITHM_H
