#ifndef __BST_H__
#define __BST_H__

#define MAX(a,b) {(a)>(b)?(a):(b)}

typedef struct TreeNode {
    int _data;
    struct TreeNode *_pLeft;
    struct TreeNode *_pRight;
}TreeNode_t, *pTreeNode_t;

pTreeNode_t insert(pTreeNode_t pRoot, int data);
void print_tree_midOrder(pTreeNode_t pRoot);

#endif
