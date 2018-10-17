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
