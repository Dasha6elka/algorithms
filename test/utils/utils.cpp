#include <string>
#include <fstream>

#include "utils.h"

void create_file(std::string path, std::string sample) {
    std::ofstream output(path);
    output << sample << std::endl;
    output.close();
}