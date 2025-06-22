#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//初始化
void list_init(pList_t pL)
{
    pL->_pHead = pL->_pTail = NULL;
    pL->_size = 0;
}

int list_init_arr(pList_t pL, TYPENAME *begin, TYPENAME *end)
{
    if (!begin || !end || begin > end) {
        return -1;
    }

    list_init(pL);
    TYPENAME *start = begin;

    for (; start <= end; ++start) {
        list_sortInsert(pL, *start);
    }

    return 0;
}
//判空
int list_empty(pList_t pL)
{
    return 0 == pL->_size;
    /* return NULL == pL->_pHead; */
}

//销毁
void list_destroy(pList_t pL)
{
    if (list_empty(pL)) {
        return;
    }

    //释放每一个结点
    int len = pL->_size;
    for (int i = 0; i < len; ++i) {
        list_erase_pos(pL, 1);
    }
    return;
}

//插入
void list_headInsert(pList_t pL, TYPENAME val)
{
    pNode_t pNew = (pNode_t)calloc(1, sizeof(Node_t));
    pNew->_data = val;

    if (list_empty(pL)) {
        pL->_pHead = pL->_pTail = pNew;
        pL->_size++;
        return;
    }

    //插在头部，修改头指针
    pNew->_pNext = pL->_pHead;
    pL->_pHead = pNew;
    pL->_size++;
    return;
}
void list_tailInsert(pList_t pL, TYPENAME val)
{
    pNode_t pNew = (pNode_t)calloc(1, sizeof(Node_t));
    pNew->_data = val;

    if (list_empty(pL)) {
        pL->_pHead = pL->_pTail = pNew;
        pL->_size++;
        return;
    }

    //插在尾部，修改尾指针
    pL->_pTail->_pNext = pNew;
    pL->_pTail = pNew;
    pL->_size++;
    return;
}
void list_sortInsert(pList_t pL, TYPENAME val)
{
    pNode_t pNew = (pNode_t)calloc(1, sizeof(Node_t));
    pNew->_data = val;

    if (list_empty(pL)) {
        pL->_pHead = pL->_pTail = pNew;
        pL->_size++;
        return;
    }

    //插入值最小，头插，修改头指针
    if (val < pL->_pHead->_data) {
        pNew->_pNext = pL->_pHead;
        pL->_pHead = pNew;
        pL->_size++;
        return;
    }

    //插入值不是最小的，找第一个比它大的元素，插在其前面
    pNode_t pPre = pL->_pHead;
    pNode_t pCur = pPre->_pNext;

    for (; pCur; pPre = pCur, pCur = pCur->_pNext) {
        if (val < pCur->_data) {
            pPre->_pNext = pNew;
            pNew->_pNext = pCur;
            break;
        }
    }

    //没找到比插入值大的, 尾插
    if (NULL == pCur) {
        pL->_pTail->_pNext = pNew;
        pL->_pTail = pNew;
    }

    pL->_size++;
    return;
}

//删除
int list_erase_val(pList_t pL, TYPENAME val)
{
    if (list_empty(pL)) {
        fprintf(stderr, "List is empty, cannot erase!\n");
        return -1;
    }

    pNode_t pCur = NULL;
    if (val == pL->_pHead->_data) {
        //删除值是第一个，修改头指针
        pCur = pL->_pHead;
        pL->_pHead = pL->_pHead->_pNext;
        if (1 == pL->_size) {
            pL->_pTail = NULL;
        }
    }
    else {
        //删除值不在首位, 遍历链表查找是否存在
        pNode_t pPre = pL->_pHead;
        pCur = pPre->_pNext;

        for (; pCur; pPre = pCur, pCur = pCur->_pNext) {
            if (val == pCur->_data) {
                pPre->_pNext = pCur->_pNext;
                break;
            }
        }

        //删除值是最后一个，修改尾指针  
        if (pCur == pL->_pTail) {
            pL->_pTail = pPre;
        }
    }

    if (NULL != pCur) {
        //删除值存在
        free(pCur);
        pCur = NULL;
        --pL->_size;
        return 0;
    }
    else {
        fprintf(stderr, "Not found delete!\n");
        return -1;
    }
}

int list_erase_pos(pList_t pL, int pos)
{
    if (list_empty(pL)) {
        fprintf(stderr, "List is empty, cannot delete!\n");
        return -1;
    }

    if (pos < 0 || pos > pL->_size) {
        fprintf(stderr, "Delete_pos is illegal!\n");
        return -1;
    }
    
    //位置合法，找到删除
    pNode_t pCur = pL->_pHead;
    if (1 == pos) {
        //是第一个
        pL->_pHead = pCur->_pNext;
        if (pCur == pL->_pTail) {
            //链表只有一个元素
            pL->_pTail = pL->_pHead;
        }
    }
    else {
        //不是第一个，遍历链表查找
        pNode_t pPre = pCur;
        pCur = pCur->_pNext;

        int i = 2;
        for (; pCur; pPre = pCur, pCur = pCur->_pNext) {
            if (i == pos) {
                pPre->_pNext = pCur->_pNext;
                break;
            }
            ++i;
        }

        //删除的是尾节点
        if (pCur == pL->_pTail) {
            pL->_pTail = pPre;
        }
    }

    free(pCur);
    pCur = NULL;
    --pL->_size;

    return 0;
}

//查找
pNode_t list_find_val(pList_t pL, TYPENAME val)
{
    if (list_empty(pL)) {
        fprintf(stderr, "List is empty, cannot find!\n");
        return NULL;
    }

    for (pNode_t pCur = pL->_pHead; pCur; pCur = pCur->_pNext) {
        if (val == pCur->_data) {
            return pCur;
        }
    }

    fprintf(stderr, "Not found!\n");
    return NULL;
}

pNode_t list_find_pos(pList_t pL, int pos)
{
    if (list_empty(pL)) {
        fprintf(stderr, "List is empty, cannot find!\n");
        return NULL;
    }

    if (pos < 0 || pos > pL->_size) {
        fprintf(stderr, "Find_pos is illegal!\n");
        return NULL;
    }

    int i = 1;
    pNode_t pCur = pL->_pHead;
    for (; pCur; pCur = pCur->_pNext) {
        if (i == pos) {
            break;
        }
        ++i;
    }

    return pCur;
}

//修改
int list_modify_val(pList_t pL, TYPENAME oldval, TYPENAME newval)
{
    pNode_t ret = list_find_val(pL, oldval);
    if (NULL == ret) {
        return -1;
    }

    ret->_data = newval;
    return 0;
}

int list_modify_pos(pList_t pL, int pos, TYPENAME newval)
{
    pNode_t ret = list_find_pos(pL, pos);
    if (NULL == ret) {
        return -1;
    }

    ret->_data = newval;
    return 0;
}

//展示链表
void list_show(pList_t pL)
{
    if (list_empty(pL)) {
        fprintf(stderr, "List is empty, cannot show!\n");
        return;
    }
    
    for (pNode_t pCur = pL->_pHead; pCur; pCur = pCur->_pNext) {
        printf("%d ", pCur->_data);
    }
    printf("\n");
    return;
}
//得到链表长度
int list_size(pList_t pL)
{
    if (pL) {
        return pL->_size;
    }
    else {
        return 0;
    }
}
