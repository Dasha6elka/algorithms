#ifndef ALGORITHMS_DIJKSTRA_ALGORITHM_H
#define ALGORITHMS_DIJKSTRA_ALGORITHM_H

#include <string>
#include <vector>
#include <map>
#include <sstream>

class Table
{
public:
    Table &init(const std::vector<std::string> &text);

    Table &print();

    Table &search(int src);

    Table &path(int from, int to);

private:
    std::map<int, std::vector<std::pair<int, int>>> mAdjencyList;
    std::vector<std::string> mRows{};

    void parse();

    std::vector<std::string> split(const std::string &s, char delim);

    int findMinPath(std::pair<int, std::vector<std::pair<int, int>>> target, int from, int totalWeight,
                    std::vector<int> &path, std::vector<bool> &visited);
};

#endif //ALGORITHMS_DIJKSTRA_ALGORITHM_H
