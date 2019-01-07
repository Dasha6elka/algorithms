/*
22. Составить   программу   удаления  записи   из    сильно
ветвящегося Б-дерева порядка N (13).
Щеглова Дарья ПС - 23
CLion 2018.3
*/

#include "BTree.h"

int main(int argc, char *argv[])
{
    std::vector<std::pair<std::string, std::string>> dictionary;
    std::vector<int> keys;
    int degree = 3;
    int mode;
    std::string item;

    try {
        auto path = readPath(argv);
        auto text = readFile(path);

        fill(text, dictionary);

        BTree tree(degree);

        for (const auto &di : dictionary) {
            tree.insert(std::stoi(di.first));
        }

        while (true) {
            try {
                std::cout << "Tree: " << std::endl;
                tree.traverse();
                std::cout << std::endl;

                std::cout << "Modes:" << std::endl;
                std::cout << "1. View node information" << std::endl;
                std::cout << "2. Delete node" << std::endl;
                std::cout << "3. Exit" << std::endl;

                std::cout << "Enter mode: ";
                std::cin >> mode;

                if (mode == 1) {
                    std::cout << "Enter node: ";
                    std::cin >> item;
                    tree.search(std::stoi(item));
                    auto result = find(item, dictionary);
                    if (result.empty()) {
                        throw std::runtime_error("Not found");
                    }
                    std::cout << "Information: " << result << std::endl;
                } else if (mode == 2) {
                    std::cout << "Enter node: ";
                    std::cin >> item;
                    tree.remove(std::stoi(item));
                    remove(item, dictionary);
                    sync("b_tree.txt", dictionary);
                } else if (mode == 3) {
                    return EXIT_SUCCESS;
                }
            } catch (std::exception &ex) {
                std::cerr << "[ERROR]: " << ex.what() << std::endl;
            } catch (...) {
                std::cerr << "[ERROR]: "
                          << "Internal error!" << std::endl;
            }
            std::cout << std::endl;
        }

    } catch (std::exception &ex) {
        std::cerr << "[ERROR]: " << ex.what() << std::endl;
    }
}
