#ifndef ALGORITHMS_DIJKSTRA_ALGORITHM_H
#define ALGORITHMS_DIJKSTRA_ALGORITHM_H

#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <functional>

using TAdjencentNeighbour = std::pair<int, int>;
using TAdjencentNeighbours = std::vector<TAdjencentNeighbour>;
using TMap = std::map<int, TAdjencentNeighbours>;
using TMapItem = std::pair<int, TAdjencentNeighbours>;

class Table
{
public:
    Table &init(const std::vector<std::string> &text);

    Table &print();

    Table &search(int src);

    Table &path(int from, int to);

private:
    TMap mAdjencyList;
    std::vector<std::string> mRows{};

    void parse();

    std::vector<std::string> split(const std::string &s, char delim);

    int findMinPath(TMapItem target, int from, int totalWeight, std::vector<int> &path, std::vector<bool> &visited);

    void traverse(std::function<void(const TMapItem &list)> callback);
};

#endif //ALGORITHMS_DIJKSTRA_ALGORITHM_H
