#ifndef ALGORITHMS_FILEREADER_H
#define ALGORITHMS_FILEREADER_H

#include <string>
#include <vector>

#include "Reader.h"

class FileReader : public Reader<std::vector<std::string>>
{
private:
    std::vector<std::string> mTextLines{};
    std::string mPath;

    void init();

public:
    explicit FileReader(const std::string &path);

    const std::vector<std::string> &get() override;
};


#endif //ALGORITHMS_FILEREADER_H
