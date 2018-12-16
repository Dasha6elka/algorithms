/*
19. Реализовать алгоритм поиска кратчайших путей Дейктры и
проиллюстрировать по  шагам этапы его выполнения. (10)
Щеглова Дарья ПС-23
CLion 2018.3
*/

#include <iostream>
#include <limits>

#include "Table.h"
#include "FileReader.h"
#include "PathReader.h"
#include "EWorkingMode.h"

int main(int argc, char *argv[])
{
    Table table;
    int vertex = std::numeric_limits<int>::min();
    int from = std::numeric_limits<int>::min();
    int to = std::numeric_limits<int>::min();
    std::string mode;
    try {
        PathReader pathReader(argv);
        FileReader fileReader(pathReader.get());
        table.init(fileReader.get()).print();
        while (true) {
            std::cout << "Choose working mode" << std::endl;
            std::cout << "0. Exit" << std::endl;
            std::cout << "1. Choose vertex to find shortest paths" << std::endl;
            std::cout << "2. Enter destination vertex: " << std::endl;
            std::cin >> mode;
            try {
                if (mode == std::string({EWorkingMode::SHORTEST_PATHS})) {
                    std::cout << "Enter vertex: " << std::endl;
                    std::cin >> vertex;
                    from = vertex;
                    table.search(vertex);
                } else if (mode == std::string({EWorkingMode::MIN_PATH})) {
                    std::cout << "Enter vertex: " << std::endl;
                    std::cin >> to;
                    table.path(from, to);
                } else if (mode == std::string({EWorkingMode::EXIT})) {
                    return EXIT_SUCCESS;
                } else {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    throw std::runtime_error("No \"" + mode + "\" mode found!");
                }
            } catch (std::exception &ex) {
                std::cerr << "[ERROR]: " << ex.what() << std::endl;
            }
        }
    } catch (std::exception &ex) {
        std::cerr << "[ERROR]: " << ex.what() << std::endl;
    }
}
