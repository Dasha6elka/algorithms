#include <string.h>
#include <stdexcept>

#include "queue.h"

Queue *CreateQueue()
{
    auto *p_queue = new Queue();
    p_queue->items = static_cast<TQueueItem *>(calloc(QUEUE_SIZE, sizeof(TQueueItem)));
    p_queue->tail = &p_queue->items[0];
    p_queue->head = &p_queue->items[0];
    p_queue->size = 0;
    return p_queue;
}

void QueueDestroy(Queue *p_queue)
{
    delete[] p_queue->items;
    delete p_queue;
}

bool QueueIsEmpty(Queue *p_queue)
{
    return p_queue->size == 0;
}

void Enqueue(Queue *p_queue, TQueueItem element)
{
//    if (QueueIsEmpty(p_queue)) {
//        p_queue->items = static_cast<TQueueItem *>(malloc(sizeof(TQueueItem) * QUEUE_SIZE));
//    } else {
//        p_queue->items = (TQueueItem *) realloc(p_queue->items, sizeof(TQueueItem) * (p_queue->tail + 1));
//    }
//    if (p_queue->tail <= QUEUE_SIZE - 1) {
//        p_queue->items[p_queue->tail++] = element;
//    } else {
//        for (int i = 0; i < QUEUE_SIZE - 1; ++i) {
//            p_queue->items[i] = p_queue->items[i + 1];
//        }
//        p_queue->items[p_queue->tail - 1] = element;
//    };
//    if (QueueIsEmpty(p_queue)) {
//        p_queue->items = static_cast<TQueueItem *>(malloc(sizeof(TQueueItem) * QUEUE_SIZE));
//    } else {
//        p_queue->items = (TQueueItem *) realloc(p_queue->items, sizeof(TQueueItem) * (p_queue->tail + 1));
//    }
//    if (p_queue->tail < QUEUE_SIZE) {
//        p_queue->items[p_queue->tail++] = element;
//    } else {
//        throw "The queue is full";
//    }
    if (p_queue->size == QUEUE_SIZE) {
        throw std::overflow_error("The queue is full");
    }
    if (p_queue->size != 0) {
        p_queue->tail++;
    }
    *p_queue->tail = element;
    p_queue->size++;
}

TQueueItem Dequeue(Queue *p_queue)
{
//    if (QueueIsEmpty(p_queue)) {
//        throw "Cannot dequeue from empty queue";
//    }
//    auto first = p_queue->items[0];
//    for (int i = 0; i < QUEUE_SIZE - 1; ++i) {
//        p_queue->items[i] = p_queue->items[i + 1];
//    }
//    p_queue->items = (TQueueItem *) realloc(p_queue->items, sizeof(TQueueItem) * --p_queue->tail);
//    return first;
//    p_queue->head = std::stoi(p_queue->items[0]);
//    p_queue->head += 1;
//    p_queue->items = (TQueueItem *) realloc(p_queue->items, sizeof(TQueueItem) * p_queue->tail);
//    return reinterpret_cast<TQueueItem>(p_queue->head);
    if (QueueIsEmpty(p_queue)) {
        throw std::underflow_error("Cannot dequeue from empty queue");
    }
    auto first = *p_queue->head;
    *p_queue->head = nullptr;
    if (p_queue->tail != p_queue->head) {
        p_queue->head++;
    }
    p_queue->size--;
    return first;
}
