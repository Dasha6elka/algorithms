#ifndef ALGORITHMS_CALCULATOR_H
#define ALGORITHMS_CALCULATOR_H

#include <vector>
#include <string>

std::string read_path(char *argv[]);

std::vector<std::string> read_file(const std::string &path);

bool is_operation(char operation);

int calculate(int left_operand, int right_operand, char operation);

std::string text_15(std::vector<std::string> &text);

#endif //ALGORITHMS_CALCULATOR_H
