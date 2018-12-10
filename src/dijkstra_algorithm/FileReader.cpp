#include <fstream>

#include "FileReader.h"

FileReader::FileReader(const std::string &path) : mPath(path)
{
    init();
}

void FileReader::init()
{
    std::string line;
    std::ifstream input;
    input.open(mPath);
    if (!input.is_open()) {
        throw "Cannot open file " + mPath;
    }
    while (std::getline(input, line)) {
        mTextLines.push_back(line);
        line.clear();
    }
}

const std::vector<std::string> &FileReader::get()
{
    return mTextLines;
}
