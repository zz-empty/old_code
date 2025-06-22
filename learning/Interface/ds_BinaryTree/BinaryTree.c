#include "BinaryTree.h"
#include <stdio.h>
#include <stdlib.h>


void build_binaryTree(pTreeNode_t *ppRoot, TYPENAME *begin, TYPENAME *end)
{
    //求出二叉树的节点个数
    TYPENAME *start = begin;
    int len = 0;
    while (start != end) {
        ++start;
        ++len;
    }

    //申请所有树节点所需空间
    pTreeNode_t pArr = (pTreeNode_t)calloc(len, sizeof(TreeNode_t));

    //根据传入的数据，给所有树节点赋值
    start = begin;
    for (int i = 0; i < len; ++i, ++start) {
        pArr[i]._data = *start;
    }

    //建树
    //i 用来遍历树节点
    //j 表示要修改指针域的树节点
    *ppRoot = pArr;
    for (int i = 1, j = 0; i < len; ++i) {
        if (NULL == pArr[j]._pLeft) {
            pArr[j]._pLeft = &pArr[i];  //放左孩子
        }
        else {
            pArr[j]._pRight = &pArr[i]; //放右孩子
            ++j;    //当前节点指针域已全部放完，换下一个节点
        }
    }

    return;
}

void insertTree_queue(pTreeNode_t *ppRoot, pQueue_t pQue, TYPENAME val)
{
    //新建树节点，新建队列节点然后将其加入辅助队列
    pTreeNode_t pT = (pTreeNode_t)calloc(1, sizeof(TreeNode_t));
    pT->_data = val;
    pQueueNode_t pQ = (pQueueNode_t)calloc(1, sizeof(QueueNode_t));
    pQ->_data = pT;

    //如果树为空，给根节点赋值, 队列节点入队
    if (NULL == *ppRoot) {
        *ppRoot = pT;
        pQue->_pHead = pQ;
        pQue->_pTail = pQ;
        return;
    }

    //树不为空
    //队列节点入队
    pQue->_pTail->_pNext = pQ;
    pQue->_pTail = pQ;

    //将新树节点地址，赋给队首指向的树节点的指针域
    pQueueNode_t pCur = pQue->_pHead;
    if (NULL == pCur->_data->_pLeft) {
        //放左孩子
        pCur->_data->_pLeft = pT;
    }
    else {
        //放右孩子
        pCur->_data->_pRight = pT;
        //队首指向的树节点的指针域全部放完，出队
        pQue->_pHead = pQue->_pHead->_pNext;
        //释放队首
        free(pCur);
        pCur = NULL;
    }
}

void preOrder(pTreeNode_t pRoot)
{
    if (pRoot) {
        printf("%c ", pRoot->_data);
        preOrder(pRoot->_pLeft);
        preOrder(pRoot->_pRight);
    }
}
void midOrder(pTreeNode_t pRoot)
{
    if (pRoot) {
        midOrder(pRoot->_pLeft);
        printf("%c ", pRoot->_data);
        midOrder(pRoot->_pRight);
    }
}
void postOrder(pTreeNode_t pRoot)
{
    if (pRoot) {
        postOrder(pRoot->_pLeft);
        postOrder(pRoot->_pRight);
        printf("%c ", pRoot->_data);
    }
}
