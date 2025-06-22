#ifndef __SEQSTACK_H__
#define __SEQSTACK_H__

#define TYPENAME int

typedef struct Stack {
    TYPENAME *_pdata;	//栈内元素
    int _capaticy;		//栈的上限
    int _top;		//栈顶，末尾元素的下标
}Stack_t, *pStack_t;

void stack_init(pStack_t pSt, int size);
void stack_destroy(pStack_t pSt);
int stack_empty(pStack_t pSt);
int stack_full(pStack_t pSt);
int stack_push(pStack_t pSt, TYPENAME val);
int stack_pop(pStack_t pSt);

//使用前需判断有无元素
TYPENAME stack_top(pStack_t pSt);
#endif
