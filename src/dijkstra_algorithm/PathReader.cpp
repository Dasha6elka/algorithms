#include <utility>

#include "PathReader.h"

const std::string &PathReader::get()
{
    return mPath;
}

PathReader::PathReader(char *argv[])
{
    mPath = argv[1];
}
