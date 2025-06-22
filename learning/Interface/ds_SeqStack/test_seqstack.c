#include "SeqStack.h"
#include <stdio.h>

void test0()
{
    Stack_t st;
    stack_init(&st, 6);
    stack_top(&st);

    printf("\n-----------test stack_push------------\n");
    stack_push(&st, 4);
    stack_push(&st, 5);
    stack_push(&st, 3);
    stack_push(&st, 9);
    stack_push(&st, 4);
    stack_push(&st, 5);
    stack_push(&st, 3);
    stack_push(&st, 9);

    if (!stack_empty(&st)) {
        printf("st.top = %d\n", stack_top(&st));
    }
    printf("st.size = %d, st.capacity = %d\n", st._top + 1, st._capaticy);

    
    printf("\n-----------test stack_push------------\n");
    stack_pop(&st);
    stack_pop(&st);
    stack_pop(&st);
    stack_pop(&st);
    stack_pop(&st);
    stack_pop(&st);
    stack_pop(&st);
    stack_pop(&st);
    stack_pop(&st);

    if (!stack_empty(&st)) {
        printf("st.top = %d\n", stack_top(&st));
    }
    printf("st.size = %d, st.capacity = %d\n", st._top + 1, st._capaticy);

    /* stack_destroy(&st); */
}

int main()
{
    test0();
    return 0;
}
