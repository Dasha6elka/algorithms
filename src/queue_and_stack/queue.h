#ifndef ALGORITHMS_QUEUE_H
#define ALGORITHMS_QUEUE_H

#include <string>

typedef char *TQueueItem;

const size_t QUEUE_SIZE = 4; // Размер очереди

typedef struct
{
    TQueueItem *items; // Массив
    TQueueItem *tail; // Указывает на последний элемент
    TQueueItem *head; // Начало очереди
    std::size_t size;
} Queue;

Queue *CreateQueue(); // Создание очереди

void QueueDestroy(Queue *p_queue); // Удаление очереди

bool QueueIsEmpty(Queue *p_queue); // Проверка на пустоту очереди

void Enqueue(Queue *p_queue, TQueueItem element); // Добавление элемента в очередь

TQueueItem Dequeue(Queue *p_queue); // Извлечение элемента из очереди

#endif //ALGORITHMS_QUEUE_H
