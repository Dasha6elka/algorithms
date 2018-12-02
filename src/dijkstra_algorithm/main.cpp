/*
19. Реализовать алгоритм поиска кратчайших путей Дейктры и
проиллюстрировать по  шагам этапы его выполнения. (10)
Щеглова Дарья ПС-23
CLion 2018.3
*/

#include "dijkstra_algorithm.h"

int main(int argc, char *argv[])
{
    int table[SIZE][SIZE];

    try {
        auto path = readPath(argv);
        auto text = readFile(path);
        std::queue<std::string> queue;
        for (auto &line : text) {
            queue.push(line);
        }
        initialTable(queue, table);
    } catch (std::exception &ex) {
        std::cerr << ex.what() << std::endl;
    }
}