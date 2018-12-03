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
    int startingPoint, endingPoint;
    bool go = true;
    std::string goOn;

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

    while (go) {
        std::cout << "Enter he starting point: " <<std::endl;
        std::cin >> startingPoint;

        while () {
            showTable(table);
            dijkstra(table);
        }

        std::cout << "Enter the ending point: " << std::endl;
        std::cin >> endingPoint;

        minimumPath(table, endingPoint);

        std::cout << "Continue?(Y - Yes,  N - No)" << std::endl;
        std::cin >> goOn;

        if (goOn == "N") {
            go = false;
        }
    }
}