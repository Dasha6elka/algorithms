#ifndef ALGORITHMS_PATHREADER_H
#define ALGORITHMS_PATHREADER_H

#include <string>

#include "Reader.h"

class PathReader : public Reader<std::string>
{
private:
    std::string mPath;
public:
    explicit PathReader(char *argv[]);

    const std::string &get() override;
};


#endif //ALGORITHMS_PATHREADER_H
