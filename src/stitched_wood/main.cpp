/*
16. Задано бинарное  дерево.  Построить  прошитое   дерево,
соответствующее обходу сверху вниз. Составить программу удале-
ния поддерева с  корнем  в  заданной  вершине  без  повторного
построения дерева. Конечное дерево должно оставаться прошитым.
Выдать информацию о нитях исходного и конечного деревьев (12).
Щеглова Дарья ПС-23
CLion 2018.2.5
*/

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
        if (root == nullptr) {
            break;
        }

        std::cout << "Tree:" << std::endl;
        showTree(root, referenceRoot);
        std::cout << "Threads:" << std::endl;
        showThreads(root);
        std::cout << "Enter vertex to delete or enter '-1' for complete" << std::endl;
        std::cin >> item;

        if (item == "-1") {
            std::cout << "Tree:" << std::endl;
            showTree(root, referenceRoot);
            std::cout << "Current threads:" << std::endl;
            showThreads(root);
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
