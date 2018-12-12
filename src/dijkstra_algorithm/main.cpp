/*
19. Реализовать алгоритм поиска кратчайших путей Дейктры и
проиллюстрировать по  шагам этапы его выполнения. (10)
Щеглова Дарья ПС-23
CLion 2018.3
*/

#include <iostream>

#include "Table.h"
#include "FileReader.h"
#include "PathReader.h"

int main(int argc, char *argv[])
{
    Table table;
    int vertex;
    int from;
    int to;
    int mode;
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

            if (mode == 1) {
                std::cout << "Enter vertex: " << std::endl;
                std::cin >> vertex;
                from = vertex;
                table.search(vertex);
            }

            if (mode == 2) {
                std::cout << "Enter vertex: " << std::endl;
                std::cin >> to;
                table.path(from, to);
            }

            if (mode == 0) {
                return EXIT_SUCCESS;
            }
        }

    } catch (std::exception &ex) {
        std::cerr << "[ERROR]: " << ex.what() << std::endl;
    }
}
