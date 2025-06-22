#include "LinkQueue.h"
#include <stdio.h>

void test0()
{
    Queue_t que;
    queue_init(&que);

    printf("\n----------test push------------\n");
    for (int i = 3; i < 500; i *= 2) {
        queue_push(&que, i);
    }
    printf("front: %d, back: %d, size: %d\n", queue_front(&que), queue_back(&que), queue_len(&que));
    queue_show(&que);

    printf("\n----------test pop------------\n");
    queue_pop(&que);
    queue_pop(&que);
    queue_pop(&que);
    queue_pop(&que);
    printf("front: %d, back: %d, size: %d\n", queue_front(&que), queue_back(&que), queue_len(&que));
    queue_show(&que);

    printf("\n---------4push 2pop-----------\n");
    queue_push(&que, 4);
    queue_push(&que, 5);
    queue_push(&que, 6);
    queue_push(&que, 7);
    queue_pop(&que);
    queue_pop(&que);
    printf("front: %d, back: %d, size: %d\n", queue_front(&que), queue_back(&que), queue_len(&que));
    queue_show(&que);
    
}

int main()
{
    test0();
}
