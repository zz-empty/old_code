#include "bst.h"
#include <stdio.h>

void test0()
{
    pTreeNode_t root = NULL;  
  
    root = insert(root, 50);  
    insert(root, 30);  
    insert(root, 20);  
    insert(root, 40);  
    insert(root, 70);  
    insert(root, 60);  
    insert(root, 80);  
  
    printf("Inorder traversal of binary search tree:\n");  
    print_tree_midOrder(root);
    printf("\n");
}

int main()
{
    test0();
    return 0;
}
