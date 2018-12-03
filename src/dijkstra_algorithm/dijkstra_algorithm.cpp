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
        for (const int item : line) {
            for (int i = item; i <= SIZE; i++) {
                table[i][i] = 0;
                for (int j = item + 1; j <= SIZE; j++){
                    for (int len = item + 1; len <= SIZE; len++){
                        table[i][j] = len;
                    }
                }
            }
        }
    }
}

void showTable(int (*table)[6])
{
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            std::cout << table[i][j];
        }
        std::cout << "\n";
        visited[i] = false;
        distance[i] = 10000;
    }
    distance[0] = 0;
}

void dijkstra(int (*table)[6])
{
    do {
        minindex = 10000;
        min = 10000;
        for (int i = 0; i < SIZE; ++i) {
            if ((!visited[i]) && (distance[i] < min)) {
                min = distance[i];
                minindex = i;
            }
        }
        if (minindex != 1000) {
            for (int i = 0; i < SIZE; ++i) {
                if (table[minindex][i] > 0) {
                    temp = min + table[minindex][i];
                    if (temp < distance[i]) {
                        distance[i] = temp;
                    }
                }
            }
            visited[minindex] = true;
        }
    } while (minindex < 10000);
}

void minimumPath(int (*table)[6], int endingPoint)
{
    int arr[SIZE]; //массив посещённых вершин
    int end = endingPoint - 1; //индекс конечной вершины
    arr[0] = end + 1; // начальный элемент - конечная вершина
    int k = 1; //индекс предыдущей вершины
    int weight = distance[end]; // век конечной вершины

    while (end > 0) {
        for (int i = 0; i < SIZE; ++i) {
            if (table[end][i] != 0) {
                int temp = weight - table[end][i];
                if (temp == distance[i]) {
                    weight = temp;
                    end = i;
                    arr[k] = i + 1;
                    k++;
                }
            }
        }
    }

    for (int j = k - 1; j >= 0; j--) {
        std::cout << arr[j];
    }
}