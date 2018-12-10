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

private:
    std::map<int, std::vector<std::pair<int, int>>> mAdjencyList;
    std::vector<std::string> mRows{};

    void parse();

    std::vector<std::string> split(const std::string &s, char delim);
};

#endif //ALGORITHMS_DIJKSTRA_ALGORITHM_H
