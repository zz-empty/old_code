#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

pTreeNode_t insert(pTreeNode_t pRoot, int data) 
{
    if (NULL == pRoot) {
        pRoot = (pTreeNode_t)calloc(1, sizeof(TreeNode_t));
        pRoot->_data = data;
    }
    else if (data > pRoot->_data) {
        pRoot->_pRight = insert(pRoot->_pRight, data);
    }
    else if (data < pRoot->_data) {
        pRoot->_pLeft = insert(pRoot->_pLeft, data);
    }

    return pRoot;
}

void print_tree_midOrder(pTreeNode_t pRoot)
{
    if (pRoot) {
        print_tree_midOrder(pRoot->_pLeft);
        printf("%d ", pRoot->_data);
        print_tree_midOrder(pRoot->_pRight);
    }
}
