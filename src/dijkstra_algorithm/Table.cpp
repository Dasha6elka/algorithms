#include <utility>

#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>
#include <limits>
#include <set>

#include "Table.h"
#include "ConsoleTable.h"

// Инициализация
Table &Table::init(const std::vector<std::string> &text)
{
    std::for_each(text.begin(), text.end(), [this](const auto &line) {
        mRows.push_back(line);
    });
    parse();
    return *this;
}

// Разбиение входных данных для работы в таблице
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
        mAllVertices[u].push_back(std::pair(v, wt));
        mAllVertices[v].push_back(std::pair(u, wt));
    });
}

// Разбиение строки на пробелы
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
// Печать таблицы
Table &Table::print()
{
    ConsoleTable consoleTable;
    consoleTable.header(" ", mAllVertices.size()); // Шапка таблицы
    std::size_t index = 0;
    index++;
    traverse([&consoleTable, &index, this](const TMapItem &list) {
        consoleTable.get()[index][0] = index;
        auto uniqueAdjencyVertex = mAdjencyList.find(list.first);
        // Выход из цикла, если вершина не найдена
        if (uniqueAdjencyVertex == mAdjencyList.end()) {
            index++;
            return;
        }
        auto row = (*uniqueAdjencyVertex).first;
        auto neighbours = (*uniqueAdjencyVertex).second;
        for (const TAdjencentNeighbour &neighbour : neighbours) {
            auto col = neighbour.first;
            auto value = neighbour.second;
            consoleTable.get()[row][col] = value; // Запись в таблицу значения
        }
        index++;
    });
    std::cout << consoleTable.get();
    return *this;
}

// Создание прототипа
void Table::traverse(std::function<void(const TMapItem &list)> callback)
{
    std::for_each(mAllVertices.begin(), mAllVertices.end(), std::move(callback));
}


// Нахождение минимальных путей до каждой из вершин
Table &Table::search(int src)
{
    std::priority_queue<
        TAdjencentNeighbour,
        TAdjencentNeighbours,
        std::greater<>
    > pq; // Использование приоритетной очереди
    // Вывод ошибки, если вершина не найдена
    if (mAllVertices.find(src) == mAllVertices.end()) {
        throw std::runtime_error("Vertex \"" + std::to_string(src) + "\" not found!");
    }
    std::vector<int> dist(mAllVertices.size(), std::numeric_limits<int>::max());
    pq.push(std::pair(0, src));
    dist[src] = 0;
    while (!pq.empty()) {
        auto u = static_cast<size_t>(pq.top().second);
        pq.pop();
        TAdjencentNeighbours::iterator it;
        // Выход из цикла, если вершина не найдена
        if (mAdjencyList.find(u) == mAdjencyList.end()) {
            continue;
        }
        for (it = mAdjencyList[u].begin(); it != mAdjencyList[u].end(); ++it) {
            auto v = static_cast<size_t>((*it).first);
            // Выход из цикла, если размер превышает существующий
            if (v >= dist.size()) {
                continue;
            }
            int weight = (*it).second; // Инициализация веса
            // ????????????????????????????????????????????????????????????????????????????
            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                pq.push(std::pair(dist[v], v));
            }
        }
    }
    {
        ConsoleTable consoleTable;
        auto neighbours = mAdjencyList[src];
        consoleTable.header(" ", static_cast<std::size_t >(mAllVertices.size())); // Шапка таблицы
        std::cout << consoleTable.get();
    }
    std::cout << "-------------------- INITIAL --------------------" << std::endl;
    {
        ConsoleTable consoleTable;
        auto neighbours = mAdjencyList[src];
        for (std::size_t i = 0; i < mAllVertices.size() + 1; ++i) {
            consoleTable.get()[0][i] = " "; // Заполнение ячеек пробелом
        }
        consoleTable.get()[0][0] = src; // Значение вершины в самом левом столбце
        for (const auto &neighbour : neighbours) {
            consoleTable.get()[0][neighbour.first] = neighbour.second; // Добавление первоначальных путей
        }
        std::cout << consoleTable.get() << std::endl;
    }
    std::cout << "-------------------------------------------------" << std::endl;
    std::set<int> prevPath;
    std::set<int> nextPath;
    for (std::size_t i = 0; i <= mAdjencyList.size() + 1; ++i) {
        // Прерыванеи цикла при слишком большом или нулевом значении дистанции
        if (dist[i] == std::numeric_limits<int>::max() || dist[i] == 0) {
            continue;
        }
        ConsoleTable consoleTable; // Как мы можем просто так писать {}?
        {
            auto neighbours = mAdjencyList[src];
            for (std::size_t j = 0; j < mAllVertices.size() + 1; ++j) {
                consoleTable.get()[0][j] = " ";
            }
            consoleTable.get()[0][0] = src;
            for (const auto &neighbour : neighbours) {
                consoleTable.get()[0][neighbour.first] = neighbour.second;
            }
        }
        if (mAdjencyList.find(src) == mAdjencyList.end()) {
            continue;
        }
        if (i >= dist.size()) {
            continue;
        }
        auto list = mAdjencyList[src];
        list.emplace_back(std::pair(i, dist[i])); // Добавление в вектор вершину и её вес
        mAdjencyList[src] = list;
        for (const auto &neighbour : list) {
            consoleTable.get()[0][neighbour.first] = neighbour.second;
        }
        for (const auto &neighbour : list) {
            nextPath.insert(neighbour.first); // Вставка вершин-соседей в следующий цикл
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

// Нахождение пути
Table &Table::path(int from, int to)
{
    if (from == std::numeric_limits<int>::min()) {
        throw std::runtime_error("No source vertex is set yet!");
    }
    if (from == to) {
        throw std::runtime_error("Source vertex is same as destination!");
    }
    std::vector<bool> visited(mAdjencyList.size(), false); // Посещаемость вершины
    std::vector<int> path(mAdjencyList.size(), std::numeric_limits<int>::min());
    std::priority_queue<
        std::pair<int, std::vector<int>>,
        std::vector<std::pair<int, std::vector<int>>>,
        std::greater<>> paths;
    int index = 0;
    findMinPath(from, to, visited, path, index, paths);
    if (paths.empty()) {
        throw std::runtime_error(
            "No paths found from \"" + std::to_string(from) + "\" to \"" + std::to_string(to) + "\"");
    }
    auto minFoundPath = paths.top().second; // Взятие найденного минимального значения пути
    // Вектор с удаленными значениями, удовлетворяющими условие
    auto iter = std::remove_if(minFoundPath.begin(), minFoundPath.end(),
                   [](const auto &item) -> bool { return item == std::numeric_limits<int>::min(); });
    // Определение нового размера вектора
    minFoundPath.resize(static_cast<unsigned long>(iter - minFoundPath.begin()));
    std::size_t i = 0;
    // Печать минимального пути
    for (const auto &item : minFoundPath) {
        std::cout << item;
        if (i < minFoundPath.size() - 1) {
            std::cout << " -> ";
        }
        i++;
    }
    std::cout << std::endl;
    return *this;
}

// Нахождение минимального пути
void Table::findMinPath(int from,
                        int to, std::vector<bool> &visited,
                        std::vector<int> &path, int index,
                        std::priority_queue<
                            std::pair<int, std::vector<int>>,
                            std::vector<std::pair<int, std::vector<int>>>,
                            std::greater<>> &paths)
{
    visited[from] = true;
    path[index] = from;
    index++;
    if (from == to) {
        std::size_t i = 0;
        int weight = 0;
        // Ссумирование веса, если найдена вершина минимального пути
        for (auto it = path.begin(); it != path.end(); ++it) {
            if (i == path.size()) {
                break;
            }
            if (mAdjencyList.find(*it) == mAdjencyList.end()) {
                continue;
            }
            auto node = mAdjencyList[*it];
            TAdjencentNeighbour neighbour;
            bool isNeighbourFound = false;
            for (const auto &item : node) {
                if (item.first != *(it + 1)) {
                    continue;
                }
                isNeighbourFound = true;
                neighbour = item;
            }
            if (!isNeighbourFound) {
                continue;
            }
            auto wt = neighbour.second;
            weight += wt;
        }
        paths.push(std::pair(weight, path));
    } else {
        for (auto &it : mAdjencyList[from]) {
            if (!visited[it.first]) {
                findMinPath(it.first, to, visited, path, index, paths);
            }
        }
    }
    index--;
    path[index] = std::numeric_limits<int>::min();
    visited[from] = false;
}
