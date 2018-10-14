#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest.h>
#include "queue_and_stack/stack.h"
#include "queue_and_stack/queue.h"

TEST_CASE ("stack init")
{
    Stack *p_stack = CreateStack();
            CHECK(p_stack->items == nullptr);
            CHECK(p_stack->top == nullptr);
            CHECK(p_stack->size == 0);
    StackDestroy(p_stack);
}

TEST_CASE ("stack is empty")
{
    Stack *p_stack = CreateStack();
            CHECK(StackIsEmpty(p_stack));
    std::string element = "100";
    StackPush(p_stack, element.data());
            CHECK(sizeof(p_stack->items) == p_stack->size * sizeof(TStackItem));
            CHECK(!StackIsEmpty(p_stack));
            CHECK(strcmp(StackPop(p_stack), "100") == 0);
            CHECK(p_stack->size == 0);
    StackDestroy(p_stack);
}

TEST_CASE ("stack pop")
{
    Stack *p_stack = CreateStack();
            CHECK_THROWS(StackPop(p_stack));
    StackDestroy(p_stack);
}

TEST_CASE ("stack destroy")
{
    Stack *p_stack = CreateStack();
    std::string element = "100";
    StackPush(p_stack, element.data());
            CHECK_NOTHROW(StackDestroy(p_stack));
}

//TEST_CASE ("queue init")
//{
//    Queue *p_queue = CreateQueue();
//            CHECK(p_queue->items == nullptr);
//            CHECK(p_queue->tail == 0);
//    QueueDestroy(p_queue);
//}

TEST_CASE ("enqueue")
{
    Queue *p_queue = CreateQueue();
    std::string element_1 = "100";
    Enqueue(p_queue, element_1.data());
            CHECK(strcmp(*p_queue->tail, element_1.data()) == 0);
            CHECK(strcmp(*p_queue->head, element_1.data()) == 0);
            CHECK(strcmp(p_queue->items[p_queue->size - 1], element_1.data()) == 0);
    std::string element_2 = "250";
    Enqueue(p_queue, element_2.data());
            CHECK(strcmp(*p_queue->head, element_1.data()) == 0);
            CHECK(strcmp(*p_queue->tail, element_2.data()) == 0);
            CHECK(strcmp(p_queue->items[p_queue->size - 1], element_2.data()) == 0);
        std::string element_3 = "500";
    Enqueue(p_queue, element_3.data());
            CHECK(strcmp(*p_queue->head, element_1.data()) == 0);
            CHECK(strcmp(*p_queue->tail, element_3.data()) == 0);
            CHECK(strcmp(p_queue->items[p_queue->size - 1], element_3.data()) == 0);
    std::string element_4 = "1000";
    Enqueue(p_queue, element_4.data());
            CHECK(strcmp(*p_queue->head, element_1.data()) == 0);
            CHECK(strcmp(*p_queue->tail, element_4.data()) == 0);
            CHECK(strcmp(p_queue->items[p_queue->size - 1], element_4.data()) == 0);
    std::string element_5 = "5000";
    CHECK_THROWS(Enqueue(p_queue, element_5.data()));
            CHECK(strcmp(*p_queue->tail, element_4.data()) == 0);
            CHECK(strcmp(p_queue->items[0], "100") == 0);
            CHECK(strcmp(p_queue->items[1], "250") == 0);
            CHECK(strcmp(p_queue->items[2], "500") == 0);
            CHECK(strcmp(p_queue->items[3], "1000") == 0);
    QueueDestroy(p_queue);
}

TEST_CASE ("dequeue")
{
    Queue *p_queue = CreateQueue();
    std::string element_1 = "100";
    Enqueue(p_queue, element_1.data());
    std::string element_2 = "250";
    Enqueue(p_queue, element_2.data());
    std::string element_3 = "500";
    Enqueue(p_queue, element_3.data());
    std::string element_4 = "1000";
    Enqueue(p_queue, element_4.data());
            CHECK(strcmp(Dequeue(p_queue), "100") == 0);
            CHECK(strcmp(*p_queue->tail, "1000") == 0);
            CHECK(strcmp(Dequeue(p_queue), "250") == 0);
            CHECK(strcmp(*p_queue->tail, "1000") == 0);
            CHECK(strcmp(Dequeue(p_queue), "500") == 0);
            CHECK(strcmp(*p_queue->tail, "1000") == 0);
            CHECK(strcmp(Dequeue(p_queue), "1000") == 0);
            CHECK(*p_queue->tail == nullptr);
            CHECK_THROWS(Dequeue(p_queue));
    QueueDestroy(p_queue);
}