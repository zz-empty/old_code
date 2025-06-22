#include "BinaryTree.h"

#include <stdio.h>
#include <string.h>

void test0()
{
    pTreeNode_t pRoot = NULL;

    char arr[] = "abcdefghi";
    TYPENAME *begin = arr; //第一个元素的地址
    TYPENAME *end = arr + strlen(arr) - 1;  //最后一个元素的地址

    build_binaryTree(&pRoot, begin, end);
    
    printf("--------------test print_tree--------------\n");
    preOrder(pRoot);
    printf("\n");

    midOrder(pRoot);
    printf("\n");

    postOrder(pRoot);
    printf("\n");
}

void test1()
{
    pTreeNode_t pRoot = NULL;
    Queue_t que;


    char val;
    while (scanf("%c", &val)) {
        if ('\n' == val) {
            break;
        }
        insertTree_queue(&pRoot, &que, val);
    }

    
    printf("--------------test print_tree--------------\n");
    preOrder(pRoot);
    printf("\n");

    midOrder(pRoot);
    printf("\n");

    postOrder(pRoot);
    printf("\n");

}

int main()
{
    /* test0(); */
    test1();

    return 0;
}
