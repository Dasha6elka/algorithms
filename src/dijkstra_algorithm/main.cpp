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
    try {
        PathReader pathReader(argv);
        FileReader fileReader(pathReader.get());
        table.init(fileReader.get()).print();
    } catch (std::exception &ex) {
        std::cerr << ex.what() << std::endl;
    }
}
