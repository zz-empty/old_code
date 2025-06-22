#ifndef __SEQSTACK_HPP
#define __SEQSTACK_HPP

#define TYPENAME int

//链栈结点
typedef struct Node {
    TYPENAME _data;
    struct Node *_pNext;
}Node_t, *pNode_t;

//链栈
typedef struct Stack {
    pNode_t _pHead; //栈顶指针
    int _size;      //栈大小
}Stack_t, *pStack_t;

void stack_init(pStack_t pSt);
void stack_destroy(pStack_t pSt);
int stack_empty(pStack_t pSt);
int stack_push(pStack_t pSt, TYPENAME val);
int stack_pop(pStack_t pSt);
void stack_show(pStack_t pSt);

//使用前需判断有无元素
TYPENAME stack_top(pStack_t pSt);

#endif
