#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <fci.h>

#include "calculator.h"

std::string read_path(char *argv[])
{
    return argv[1];
}

std::vector<std::string> read_file(const std::string &path)
{
    std::vector<std::string> result{};
    std::string line;
    std::ifstream input;
    input.open(path);
    if (!input.is_open()) {
        throw "Cannot open file " + path;
    }
    while (std::getline(input, line)) {
        result.push_back(line);
        line.clear();
    }
    return result;
}

bool is_operation(char operation)
{
    if (operation == '+') {
        return true;
    }
    if (operation == '-') {
        return true;
    }
    if (operation == '*') {
        return true;
    }
    if (operation == '/') {
        return true;
    }
    return false;
}

int calculate(int left_operand, int right_operand, char operation)
{
    int result = 0;
    if (operation == '+') {
        result = left_operand + right_operand;
    }
    if (operation == '-') {
        result = left_operand - right_operand;
    }
    if (operation == '*') {
        result = left_operand * right_operand;
    }
    if (operation == '/') {
        result = left_operand / right_operand;
    }
    return result;
}

std::string text_15(std::vector<std::string> &text)
{
    std::string left_operand;
    std::string right_operand;
    char operation = '\0';
    std::string output;
    int max_number = INT_MIN;
    bool pre_clear = false;
    // Итерация по строкам
    for (const auto &line : text) {
        int result = 0;
        if (!line[0]) {
            continue;
        }
        // Лямбда-функция установки результата вывода
        auto get_output = [&]() {
            result = calculate(std::stoi(left_operand), std::stoi(right_operand), operation);
            if (result > max_number) {
                max_number = result;
                output = line;
            }
        };
        // Лямбда-функция отчистики значений переменных !
        auto clear = [&]() {
            right_operand.clear();
            left_operand.clear();
            operation = '\0';
        };
        // Итерация по символам строк
        for (const auto &letter : line) {
            char next_letter = *(&letter + 1); // Следующая буква после текущей
            // Расчёт операции если она не последняя
            if (!right_operand.empty() &&
                !isdigit(letter) &&
                (isdigit(next_letter) || is_operation(next_letter))) {
                get_output();
                // Отчистка значений переменных
                clear();
            }
            // Отчистка операндов после найденного разрыва
            if (pre_clear && (isdigit(next_letter) || is_operation(next_letter))) {
                // В зависимости от того, найден ли оператор, отчистка левого или правого операнда
                if (!operation) {
                    left_operand.clear();
                } else {
                    right_operand.clear();
                }
                pre_clear = false;
            }
            // Если найден разрыв, установка флага отчистки на следующих ходах
            if (!isdigit(letter) && !is_operation(letter)) {
                pre_clear = true;
            }
            // Заполнение левого операнда
            if (isdigit(letter) && !operation) {
                // Отчистка левого операнда если не зашли в условие отчистки
                if (pre_clear) {
                    left_operand.clear();
                }
                left_operand += letter;
                pre_clear = false;
            }
            // Установка знака оператора !
            if (!left_operand.empty() && is_operation(letter)) {
                operation = letter;
            }
                // Если левый операнд пуст, и встретился знак '-', то он относится к левому операнду !
            else if (letter == '-' && left_operand.empty()) {
                left_operand = letter;
            }
            // Заполнение правого операнда !
            if (isdigit(letter) && operation) {
                // Отчистка правого операнда если не было захода в условие отчистки операндов
                if (pre_clear) {
                    right_operand.clear();
                }
                right_operand += letter;
            }
        }
        // Расчёт последней операции в строке
        if (!left_operand.empty() && !right_operand.empty() && operation) {
            get_output();
        }
        // Отчистка значений переменных
        clear();
    }
    if (max_number == INT_MIN) {
        throw "Cannot get output";
    }
    return output + "\n" + std::to_string(max_number);
}