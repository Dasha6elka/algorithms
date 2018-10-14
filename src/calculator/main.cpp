/*
15. В некоторых строках текстового файла имеются выражения,
состоящие   из   двух   целых   чисел,   разделенных    знаком
арифметической   операции ('+','-','*','/'). Первое  из  чисел
может быть отрицательным. В строке может содержаться несколько
выражений. Перед  выражением  и  после него  могут  находиться
произвольные символы. Требуется  выделить  строку,  в  которой
значение выражения максимально. Вывести найденное максимальное
значение (7).

Щеглова Дарья ПС-23
CLion 2018.2.3
 */

#include <string>
#include <iostream>

#include "calculator.h"

int main(int argc, char *argv[])
{
    try {
        auto path = read_path(argv);
        auto text = read_file(path);
        auto result = text_15(text);
        std::cout << result << std::endl;
    } catch (const char *message) {
        std::cerr << message << std::endl;
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}
