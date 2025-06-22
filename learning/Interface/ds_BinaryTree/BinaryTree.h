#ifndef __BINARYTREE_H__
#define __BINARYTREE_H__

#define TYPENAME char

//二叉树节点
typedef struct TreeNode {
    //数据域
    TYPENAME _data;
    //指针域
    struct TreeNode *_pLeft;
    struct TreeNode *_pRight;
}TreeNode_t, *pTreeNode_t;

//静态建树，已知树节点个数
void build_binaryTree(pTreeNode_t *ppRoot, TYPENAME *begin, TYPENAME *end);

//队列节点
typedef struct QueueNode {
    pTreeNode_t _data;  //树节点地址
    struct QueueNode *_pNext;
}QueueNode_t, *pQueueNode_t;

//队列
typedef struct Queue {
    pQueueNode_t _pHead;    //队头
    pQueueNode_t _pTail;    //队尾
}Queue_t, *pQueue_t;

//动态建树，不清楚节点个数，通过辅助队列
//辅助队列中，是所有没放完指针域的树节点
void insertTree_queue(pTreeNode_t *ppRoot, pQueue_t pQue, TYPENAME val);

//遍历
void preOrder(pTreeNode_t pRoot);   //先序遍历
void midOrder(pTreeNode_t pRoot);   //中序遍历
void postOrder(pTreeNode_t pRoot);  //后序遍历


#endif
