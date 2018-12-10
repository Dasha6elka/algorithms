#include <cstring>
#include <algorithm>

#include "Table.h"

Table &Table::init(const std::vector<std::string> &text)
{
    std::for_each(text.begin(), text.end(), [this](const auto &line) {
        this->mRows.push_back(line);
    });
    parse();
    return *this;
}

Table &Table::print()
{
    return *this;
}

void Table::parse()
{
    std::for_each(mRows.begin(), mRows.end(), [this](const auto &row) {
        auto str = split(row, ' ');
        std::vector<int> nums{};
        for (const auto &ch : str) {
            nums.push_back(std::stoi(ch));
        }
        auto u = static_cast<unsigned long>(nums[0]);
        auto v = nums[1];
        auto wt = nums[2];
        mAdjencyList[u].push_back(std::pair(v, wt));
        mAdjencyList[v].push_back(std::pair(u, wt));
    });
}

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
