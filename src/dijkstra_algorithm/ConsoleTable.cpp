#include <cpp-console-table/CppConsoleTable.h>
#include "ConsoleTable.h"

ConsoleTable::ConsoleTable()
{
    TConsoleTable::TableChars chars;
    chars.centreSeparation = '|';
    chars.leftRightSimple = '|';
    chars.topDownSimple = '-';
    chars.leftSeparation = '+';
    chars.rightSeparation = '+';
    chars.downSeparation = '+';
    chars.topSeparation = '+';
    chars.downLeft = '+';
    chars.downRight = '+';
    chars.topLeft = '+';
    chars.topRight = '+';
    mTable.setTableChars(chars);
}

TConsoleTable &ConsoleTable::get()
{
    return mTable;
}

void ConsoleTable::header(const std::string &zero, std::size_t size)
{
    mTable[0][0] = zero;
    for (std::size_t j = 0; j < size; ++j) {
        mTable[0][j + 1] = j + 1;
    }
}
