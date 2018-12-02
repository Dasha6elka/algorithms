#include <fstream>
#include "dijkstra_algorithm.h"

std::string readPath(char *argv[])
{
    return argv[1];
}

std::vector<std::string> readFile(const std::string &path)
{
    std::vector<std::string> result{};
    std::string line;
    std::ifstream input;
    input.open(path);
    if (!input.is_open()) {
        throw "Cannot open file " + path;
    }
    while (std::getline(input, line)) {
        result.push_back(line);
        line.clear();
    }
    return result;
}

void initialTable(std::queue<std::string> &file, int table[SIZE][SIZE])
{
    while (!file.empty()){
        auto line = file.front();
        file.pop();
        line = line.data();
        for (const int item : line.data()) {
            for (int i = item; i <= SIZE; i++) {
                for (int j = item + 1; j <= SIZE; j++){
                    for (int len = item + 1; len <= SIZE; len++){
                        table[i][j] = len;
                    }
                }
            }
        }
    }
}