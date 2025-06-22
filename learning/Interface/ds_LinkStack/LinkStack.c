#include "LinkStack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void stack_init(pStack_t pSt)
{
    pSt->_pHead = NULL;
    pSt->_size = 0;
}

void stack_show(pStack_t pSt)
{
    if (!stack_empty(pSt)) {
        pNode_t pCur = pSt->_pHead;
        for (; pCur; pCur = pCur->_pNext) {
            printf("%d ", pCur->_data);
        }
        printf("\n");
    }
}

void stack_destroy(pStack_t pSt) 
{
    if (!stack_empty(pSt)) {

        for (pNode_t pCur = pSt->_pHead; pCur; pCur = pCur->_pNext)
        {
            pNode_t pDel = pCur;
            free(pDel);
            pDel = NULL;
        }

        memset(pSt, 0, sizeof(Stack_t));
    }
}

int stack_empty(pStack_t pSt)
{
    return 0 == pSt->_size;
}


int stack_push(pStack_t pSt, TYPENAME val)
{
    pNode_t pNew = (pNode_t)calloc(1, sizeof(Node_t));
    pNew->_data = val;
    pNew->_pNext = NULL;

    pNew->_pNext = pSt->_pHead;
    pSt->_pHead = pNew;
    ++pSt->_size;
    return 0;
}

int stack_pop(pStack_t pSt)
{
    if (!stack_empty(pSt)) {
        pNode_t pDel = pSt->_pHead;
        pSt->_pHead = pDel->_pNext;

        free(pDel);
        pDel = NULL;
        --pSt->_size;
        return 0;
    }

    printf("Stack is empty, cannot pop!\n");
    return -1;
}

//使用前需判断有无元素
TYPENAME stack_top(pStack_t pSt)
{
    return pSt->_pHead->_data;
}
