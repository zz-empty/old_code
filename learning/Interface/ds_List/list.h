#ifndef __LIST_H__
#define __LIST_H__

//将数据类型提取出来，方便修改
#define TYPENAME int

//链表结点
typedef struct Node {
    TYPENAME _data;
    struct Node *_pNext;
}Node_t, *pNode_t;

//链表
typedef struct List {
    pNode_t _pHead;
    pNode_t _pTail;
    int _size;
}List_t, *pList_t;

//初始化
void list_init(pList_t pL);
int list_init_arr(pList_t pL, TYPENAME *begin, TYPENAME *end);
//判空
int list_empty(pList_t pL);
//销毁
void list_destroy(pList_t pL);
//插入
void list_headInsert(pList_t pL, TYPENAME val);
void list_tailInsert(pList_t pL, TYPENAME val);
void list_sortInsert(pList_t pL, TYPENAME val);
//删除
int list_erase_val(pList_t pL, TYPENAME val);
int list_erase_pos(pList_t pL, int pos);
//查找
pNode_t list_find_val(pList_t pL, TYPENAME val);
pNode_t list_find_pos(pList_t pL, int pos);
//修改
int list_modify_val(pList_t pL, TYPENAME oldval, TYPENAME newval);
int list_modify_pos(pList_t pL, int pos, TYPENAME newval);
//展示链表
void list_show(pList_t pL);
//得到链表长度
int list_size(pList_t pL);

#endif
