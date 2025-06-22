#include "LinkStack.h"
#include <stdio.h>

void test0()
{
    Stack_t st;
    stack_init(&st);

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
    printf("st.size = %d\n", st._size);
    stack_show(&st);

    
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
    printf("st.size = %d\n", st._size);
    stack_show(&st);

    stack_destroy(&st);
}

int main()
{
    test0();
    return 0;
}
