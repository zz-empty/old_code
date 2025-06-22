#include "SeqStack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void stack_init(pStack_t pSt, int size)
{
    pSt->_pdata = (TYPENAME*)calloc(size, sizeof(TYPENAME));
    pSt->_capaticy = size;
    pSt->_top = -1;
}

void stack_destroy(pStack_t pSt) 
{
    if (!stack_empty(pSt)) {
        free(pSt->_pdata);
        pSt->_pdata = NULL;
        memset(pSt, 0, sizeof(Stack_t));
    }
}

int stack_empty(pStack_t pSt)
{
    return -1 == pSt->_top;
}

int stack_full(pStack_t pSt)
{
    return pSt->_top + 1 == pSt->_capaticy;
}

int stack_push(pStack_t pSt, TYPENAME val)
{
    if (!stack_full(pSt)) {
        pSt->_pdata[++pSt->_top] = val;
        return 0;
    }

    printf("Stack is full, cannot push!\n");
    return -1;
}

int stack_pop(pStack_t pSt)
{
    if (!stack_empty(pSt)) {
        --pSt->_top;
        return 0;
    }

    printf("Stack is empty, cannot pop!\n");
    return -1;
}

//使用前需判断有无元素
TYPENAME stack_top(pStack_t pSt)
{
    return pSt->_pdata[pSt->_top];
}
