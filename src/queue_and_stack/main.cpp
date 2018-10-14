/*
12. Имеется кольцевая очередь, заданная массивом, и стек,
заданный с помощью указателей. Информационная часть элементов
обеих структур идентична. Обеспечить операции включения,
удаления, выдачи элементов стека и очереди. По требованию
пользователя исключить из стека элементы, имеющиеся в очереди
(7).
Щеглова Дарья ПС-23
CLion 2018.2.4
*/

#include <iostream>
#include <cstring>
#include <algorithm>

#include "stack.h"
#include "queue.h"

int main(int argc, char *argv[])
{
    int mode;
    std::string item;
    Stack *p_stack = CreateStack();
    Queue *p_queue = CreateQueue();

    bool isRunning = true;

    while (isRunning) {
        std::cout << "Choose working mode:" << std::endl;
        std::cout << "1. Push to stack" << std::endl;
        std::cout << "2. Pop from stack" << std::endl;
        std::cout << "3. Enqueue" << std::endl;
        std::cout << "4. Dequeue" << std::endl;
        std::cout << "5. Remove from stack elements in queue" << std::endl;
        std::cout << "6. Exit" << std::endl;
        std::cin >> mode;

        switch (mode) {
            case 1: {
                std::cout << "Enter element: " << std::endl;
                std::cin >> item;
                StackPush(p_stack, strdup(item.data()));
                break;
            }
            case 2:
                try {
                    StackPop(p_stack);
                } catch (std::exception &ex) {
                    std::cerr << ex.what() << std::endl;
                }
                break;
            case 3: {
                try {
                    std::cout << "Enter element: " << std::endl;
                    std::cin >> item;
                    Enqueue(p_queue, strdup(item.data()));
                } catch (std::exception &ex) {
                    std::cerr << ex.what() << std::endl;
                }
                break;
            }
            case 4:
                try {
                    Dequeue(p_queue);
                } catch (std::exception &ex) {
                    std::cerr << ex.what() << std::endl;
                }
                break;
            case 5:
                for (int i = 0; i < p_queue->size; ++i) {
                    auto positions = StackFind(p_stack, p_queue->items[i]);
                    if (positions.empty()) {
                        continue;
                    }
                    RemoveElement(p_stack, positions);
                }
                break;
            case 6:
                std::cout << "End of work" << std::endl;
                isRunning = false;
                break;
            default:
                std::cerr << "Mode not found" << std::endl;
        }

        std::cout << "\nStack items:" << std::endl;
        std::cout << '[';
        for (int i = 0; i < p_stack->size; ++i) {
            std::cout << p_stack->items[i];
            if (i != p_stack->size - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "]\n\n";

        std::cout << "\nQueue items:" << std::endl;
        std::cout << '[';
        auto diff = std::abs(p_queue->tail - p_queue->head);
        if (p_queue->tail == p_queue->head && *p_queue->head != nullptr) {
            std::cout << p_queue->head[0];
        } else {
            for (int j = 0; j <= diff; ++j) {
                if (p_queue->head[j] == nullptr) continue;
                std::cout << p_queue->head[j];
                if (j != p_queue->size - 1) {
                    std::cout << ", ";
                }
            }
        }
        std::cout << "]\n\n";
    }

    StackDestroy(p_stack);
    QueueDestroy(p_queue);
}
