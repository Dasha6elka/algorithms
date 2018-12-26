#include "BTree.h"

/*
22. Составить   программу   удаления  записи   из    сильно
ветвящегося Б-дерева порядка N (13).
Щеглова Дарья ПС - 23
childNumbersLion 2018.3
*/

#include <iostream>
#include <limits>
#include <string>

#include "BTree.h"
#include "cxxopts/cxxopts.h"

    int main(int argc, char* argv[])
    {
        int del = std::numeric_limits<int>::max();
        int degree = std::numeric_limits<int>::max();
        int order = std::numeric_limits<int>::max();
        std::string mode;

        bool debug = true;

        try {
            cxxopts::Options options("Key", "Info");
            options.add_options()("order", "B-tree maximum order (default = 4)", cxxopts::value<int>()->default_value("4"))("debug", "Specify if want to run in debug mode", cxxopts::value<bool>()->default_value("false"));
            auto result = options.parse(argc, argv);
            debug = result["debug"].as<bool>();
            order = result["order"].as<int>();
            degree = (degree + 1) / 2;

            BTree tree(degree);

            while (true) {
                try {
                    std::cout << "Traversal of the B-tree(" << std::to_string(order) << ")"
                              << " is " << std::endl;
                    tree.traverse();
                    std::cout << std::endl;

                    std::cout << "Working mode (delete, exit): ";
                    std::cin >> mode;

                    if (mode == "delete") {
                        std::cout << "Delete node: ";
                        std::cin >> del;
                        tree.remove(del);
                    } else if (mode == "exit") {
                        return EXIT_SUCCESS;
                    }
                } catch (std::exception& ex) {
                    std::cerr << "[ERROR]: " << ex.what() << std::endl;
                } catch (...) {
                    std::cerr << "[ERROR]: "
                              << "Internal error!" << std::endl;
                }
            }

        } catch (std::exception& ex) {
            std::cerr << "[ERROR]: " << ex.what() << std::endl;
        }
    }
