#ifndef ALGORITHMS_CONSOLETABLE_H
#define ALGORITHMS_CONSOLETABLE_H

#include "cpp-console-table/CppConsoleTable.h"

using TConsoleTable = samilton::ConsoleTable;
constexpr static std::size_t INDENT = 1;

class ConsoleTable
{
private:
    TConsoleTable mTable{INDENT, INDENT};
public:
    ConsoleTable();

    TConsoleTable &get();

    void header(const std::string &zero, std::size_t size);
};


#endif //ALGORITHMS_CONSOLETABLE_H
