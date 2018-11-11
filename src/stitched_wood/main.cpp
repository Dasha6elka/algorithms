/*
16. Задано бинарное  дерево.  Построить  прошитое   дерево,
соответствующее обходу сверху вниз. Составить программу удале-
ния поддерева с  корнем  в  заданной  вершине  без  повторного
построения дерева. Конечное дерево должно оставаться прошитым.
Выдать информацию о нитях исходного и конечного деревьев (12).
Щеглова Дарья ПС-23
CLion 2018.2.5
*/

#include <algorithm>
#include <queue>
#include <string>
#include <iostream>

#include "stitched_wood.h"

int main(int argc, char *argv[])
{
    TreeNode *root = nullptr;
    TreeNode *referenceRoot = nullptr;
    std::string item;

    try {
        auto path = readPath(argv);
        auto text = readFile(path);
        std::queue<std::string> queue;
        for (auto &line : text) {
            queue.push(line);
        }
        root = addNode(root, nullptr, queue);
        for (auto &line : text) {
            queue.push(line);
        };
        referenceRoot = addNode(referenceRoot, nullptr, queue);
        for (auto &line : text) {
            queue.push(line);
        }
        root = stitch(root);
    } catch (std::exception &ex) {
        std::cerr << ex.what() << std::endl;
    }

    while (true) {
        std::cout << std::endl;
        showTree(root, referenceRoot);
        std::cout << std::endl;
        showThreads(root);
        std::cout << std::endl;
        std::cin >> item;

        if (item == "-1") {
            break;
        }

        try {
            root = deleteNodeByValue(root, item.data());
        } catch (std::exception &ex) {
            std::cerr << ex.what() << std::endl;
        }
    }

    deleteNode(root);
    free(root);
}
