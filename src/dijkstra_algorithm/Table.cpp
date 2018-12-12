#include <utility>

#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>
#include <limits>
#include <set>

#include "Table.h"
#include "ConsoleTable.h"

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
    ConsoleTable consoleTable;
    consoleTable.header(" ", mAdjencyList.size());
    std::size_t index = 0;
    index++;
    traverse([&consoleTable, &index](const TMapItem &list) {
        consoleTable.get()[index][0] = index;
        auto row = list.first;
        auto neighbours = list.second;
        for (const TAdjencentNeighbour &neighbour : neighbours) {
            auto col = neighbour.first;
            auto value = neighbour.second;
            consoleTable.get()[row][col] = value;
        }
        index++;
    });
    std::cout << consoleTable.get();
    return *this;
}

void Table::parse()
{
    std::for_each(mRows.begin(), mRows.end(), [this](const auto &row) {
        auto str = split(row, ' ');
        std::vector<int> nums{};
        for (const auto &ch : str) {
            try {
                nums.push_back(std::stoi(ch));
            } catch (...) {
                throw std::runtime_error("\"" + ch + "\" is not a digit!");
            }
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
        TAdjencentNeighbour,
        TAdjencentNeighbours,
        std::greater<>
    > pq;
    if (static_cast<std::size_t>(src) > mAdjencyList.size()) {
        return *this;
    }
    std::vector<int> dist(mAdjencyList.size() + 1, std::numeric_limits<int>::max());
    pq.push(std::pair(0, src));
    dist[src] = 0;
    while (!pq.empty()) {
        auto u = static_cast<size_t>(pq.top().second);
        pq.pop();
        TAdjencentNeighbours::iterator it;
        for (it = mAdjencyList[u].begin(); it != mAdjencyList[u].end(); ++it) {
            auto v = static_cast<size_t>((*it).first);
            int weight = (*it).second;
            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                pq.push(std::pair(dist[v], v));
            }
        }
    }
    {
        ConsoleTable consoleTable;
        consoleTable.header(" ", mAdjencyList.size());
        std::cout << consoleTable.get();
    }
    std::cout << "-------------------- INITIAL --------------------" << std::endl;
    {
        ConsoleTable consoleTable;
        auto neighbours = mAdjencyList[src];
        for (std::size_t i = 0; i < mAdjencyList.size() + 1; ++i) {
            consoleTable.get()[0][i] = " ";
        }
        consoleTable.get()[0][0] = src;
        for (const auto &neighbour : neighbours) {
            consoleTable.get()[0][neighbour.first] = neighbour.second;
        }
        std::cout << consoleTable.get() << std::endl;
    }
    std::cout << "-------------------------------------------------" << std::endl;
    std::set<int> prevPath;
    std::set<int> nextPath;
    for (std::size_t i = 0; i <= mAdjencyList.size(); ++i) {
        if (dist[i] == std::numeric_limits<int>::max() || dist[i] == 0) {
            continue;
        }
        ConsoleTable consoleTable;
        {
            auto neighbours = mAdjencyList[src];
            for (std::size_t j = 0; j < mAdjencyList.size() + 1; ++j) {
                consoleTable.get()[0][j] = " ";
            }
            consoleTable.get()[0][0] = src;
            for (const auto &neighbour : neighbours) {
                consoleTable.get()[0][neighbour.first] = neighbour.second;
            }
        }
        auto list = mAdjencyList[src];
        list.emplace_back(std::pair(i, dist[i]));
        mAdjencyList[src] = list;
        for (const auto &neighbour : list) {
            consoleTable.get()[0][neighbour.first] = neighbour.second;
        }
        for (const auto &neighbour : list) {
            nextPath.insert(neighbour.first);
        }
        auto vertex = std::to_string(i);
        std::cout << "-------------------- FIX VERTEX " + vertex + " --------------------" << std::endl;
        std::cout << consoleTable.get() << std::endl;
        std::cout << "--------------------------------" + std::string(vertex.size(), '-') + "---------------------"
                  << std::endl;
        prevPath.clear();
        prevPath = nextPath;
        nextPath.clear();
    }
    return *this;
}

Table &Table::path(int from, int to)
{
    std::vector<int> path;
    std::vector<bool> visited(mAdjencyList.size() + 1, false);
    auto target = mAdjencyList[to];
    auto source = mAdjencyList[from];
    int totalWeight = 0;
    for (const auto &neighbour : source) {
        if (neighbour.first == to) {
            totalWeight = neighbour.second;
        }
    }
    path.push_back(to);
    auto found = findMinPath(std::pair(to, target), from, totalWeight, path, visited);
    if (found != std::numeric_limits<int>::min()) {
        path.push_back(found);
    }
    if (path.size() <= 1) {
        return *this;
    }
    std::size_t index = 0;
    std::reverse(path.begin(), path.end());
    std::cout << "Min path from \""
              << std::to_string(from)
              << "\" to \""
              << std::to_string(to)
              << "\" is : ";
    for (const auto &segment : path) {
        if (segment == std::numeric_limits<int>::min()) {
            break;
        }
        std::cout << segment;
        if (index != path.size() - 1) {
            std::cout << " -> ";
        }
        index++;
    }
    std::cout << std::endl;
    return *this;
}

int Table::findMinPath(TMapItem target, int from, int totalWeight, std::vector<int> &path, std::vector<bool> &visited)
{
    for (const auto &neighbour : target.second) {
        if (visited[neighbour.first]) {
            return std::numeric_limits<int>::min();
        }
        visited[neighbour.first] = true;
        int nextTotalWeight = totalWeight - neighbour.second;
        if (nextTotalWeight == 0 && neighbour.first == from) {
            return neighbour.first;
        }
        auto nextTarget = mAdjencyList[neighbour.first];
        auto found = findMinPath(std::pair(neighbour.first, nextTarget), from, nextTotalWeight, path, visited);
        if (found == std::numeric_limits<int>::min()) {
            visited[neighbour.first] = false;
            continue;
        }
        path.push_back(neighbour.first);
        path.push_back(found);
    }
    return std::numeric_limits<int>::min();
}

void Table::traverse(std::function<void(const TMapItem &list)> callback)
{
    std::for_each(mAdjencyList.begin(), mAdjencyList.end(), std::move(callback));
}
