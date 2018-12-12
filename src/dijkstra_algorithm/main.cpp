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
    int edge;
    int from;
    int to;
    int mode;
    try {
        PathReader pathReader(argv);
        FileReader fileReader(pathReader.get());
        table.init(fileReader.get()).print();

        while (true) {
            std::cin >> mode;

            if (mode == 1) {
                std::cin >> edge;
                table.search(edge).print();
            }

            if (mode == 2) {
                std::cin >> from;
                std::cin >> to;
                table.path(from, to);
            }

            if (mode = 0) {
                break;
            }
        }

    } catch (std::exception &ex) {
        std::cerr << "[ERROR]: " << ex.what() << std::endl;
    }
}
