#ifndef ALGORITHMS_DIJKSTRA_ALGORITHM_H
#define ALGORITHMS_DIJKSTRA_ALGORITHM_H

#include <queue>
#include <iostream>
#include <string>
#include <vector>

const int SIZE = 6;
int distance[SIZE]; // минимальное расстояние
bool visited[SIZE]; // посещённые вершины
int minindex, min;
int temp;

std::string readPath(char *argv[]);

std::vector<std::string> readFile(const std::string &path);

void initialTable(std::queue<std::string> &file, int table[SIZE][SIZE]);

void showTable(int table[SIZE][SIZE]);

void dijkstra(int table[SIZE][SIZE]);

void minimumPath(int table[SIZE][SIZE], int endingPoint);

#endif //ALGORITHMS_DIJKSTRA_ALGORITHM_H
