#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>
#include <limits>

#include "cpp-console-table/CppConsoleTable.h"
#include "Table.h"

static constexpr int INF = std::numeric_limits<int>::max();
using ConsoleTable = samilton::ConsoleTable;

Table &Table::init(const std::vector<std::string> &text)
{
    std::for_each(text.begin(), text.end(), [this](const auto &line) {
        this->mRows.push_back(line);
    });
    parse();
    return *this;
}

Table &Table::print()
{
    std::size_t indent = 1;
    ConsoleTable table(indent, indent);
    ConsoleTable::TableChars chars;
    chars.centreSeparation = '|';
    chars.leftRightSimple = '|';
    chars.topDownSimple = '-';
    chars.leftSeparation = '+';
    chars.rightSeparation = '+';
    chars.downSeparation = '+';
    chars.topSeparation = '+';
    chars.downLeft = '+';
    chars.downRight = '+';
    chars.topLeft = '+';
    chars.topRight = '+';
    table.setTableChars(chars);
    std::size_t tableSize = mAdjencyList.size();
    std::size_t index = 0;
    table[0][index] = " ";
    index++;
    for (std::size_t i = 0; i < tableSize; ++i) {
        table[0][i + 1] = i + 1;
    }
    std::for_each(mAdjencyList.begin(), mAdjencyList.end(),
                  [&table, &index](const std::pair<int, std::vector<std::pair<int, int>>> &list) {
                      table[index][0] = index;
                      auto row = list.first;
                      auto neighbours = list.second;
                      for (const std::pair<int, int> &neighbour : neighbours) {
                          auto col = neighbour.first;
                          auto value = neighbour.second;
                          table[row][col] = value;
                      }
                      index++;
                  });
    std::cout << table;
    return *this;
}

void Table::parse()
{
    std::for_each(mRows.begin(), mRows.end(), [this](const auto &row) {
        auto str = split(row, ' ');
        std::vector<int> nums{};
        for (const auto &ch : str) {
            nums.push_back(std::stoi(ch));
        }
        auto u = static_cast<unsigned long>(nums[0]);
        auto v = nums[1];
        auto wt = nums[2];
        mAdjencyList[u].push_back(std::pair(v, wt));
        mAdjencyList[v].push_back(std::pair(u, wt));
    });
}

std::vector<std::string> Table::split(const std::string &s, char delim)
{
    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> elems;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

Table &Table::search(int src)
{
    std::priority_queue<
        std::pair<int, int>,
        std::vector<std::pair<int, int>>,
        std::greater<>
    > pq;
    if (static_cast<std::size_t>(src) > mAdjencyList.size()) {
        return *this;
    }
    std::vector<int> dist(mAdjencyList.size() + 1, INF);
    pq.push(std::pair(0, src));
    dist[src] = 0;
    while (!pq.empty()) {
        auto u = static_cast<size_t>(pq.top().second);
        pq.pop();
        std::vector<std::pair<int, int>>::iterator it;
        for (it = mAdjencyList[u].begin(); it != mAdjencyList[u].end(); ++it) {
            auto v = static_cast<size_t>((*it).first);
            int weight = (*it).second;
            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                pq.push(std::pair(dist[v], v));
            }
        }
    }
    for (unsigned long i = 0; i <= mAdjencyList.size(); ++i) {
        if (dist[i] == INF || dist[i] == 0) {
            continue;
        }
        auto list = mAdjencyList[src];
        list.emplace_back(std::pair(i, dist[i]));
        mAdjencyList[src] = list;
    }
    return *this;
}
