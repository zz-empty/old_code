#include "list.h"
#include <stdio.h>

int main() 
{
    int arr[] = {3, 5, 7, 8, 9, 6};

    List_t L;

    printf("\n-------------test list_init-----------\n");
    /* list_init(&L); */
    list_init_arr(&L, &arr[0], &arr[5]);
    list_show(&L);
    printf("list_size: %d\n", list_size(&L));


    printf("\n-------------test list_headInsert-----------\n");
    list_headInsert(&L, 20);
    list_headInsert(&L, 20);
    list_headInsert(&L, 30);
    list_show(&L);
    printf("list_size: %d\n", list_size(&L));

    printf("\n-------------test list_tailInsert-----------\n");
    list_tailInsert(&L, 40);
    list_tailInsert(&L, 50);
    list_show(&L);
    printf("list_size: %d\n", list_size(&L));

    printf("\n-------------test list_sortInsert-----------\n");
    list_sortInsert(&L, 1);
    list_sortInsert(&L, 100);
    list_show(&L);
    printf("list_size: %d\n", list_size(&L));

    printf("\n-------------test list_erase_val-----------\n");
    list_erase_val(&L, 20);
    list_erase_val(&L, 200);
    list_show(&L);
    printf("list_size: %d\n", list_size(&L));

    printf("\n-------------test list_erase_pos-----------\n");
    list_erase_pos(&L, 1);
    list_erase_pos(&L, 100);
    list_show(&L);
    printf("list_size: %d\n", list_size(&L));

#if 0
    printf("\n-------------test list_modify_val-----------\n");
    list_modify_val(&L, 1, 88);
    list_modify_val(&L, 30, 99);
    list_modify_val(&L, 100, 99);
    list_show(&L);
    printf("list_size: %d\n", list_size(&L));

    printf("\n-------------test list_modify_pos-----------\n");
    list_modify_pos(&L, 1, 88);
    list_modify_pos(&L, 30, 99);
    list_modify_pos(&L, list_size(&L), 66);
    list_show(&L);
    printf("list_size: %d\n", list_size(&L));
#endif

    printf("\n");
    list_destroy(&L);
    /* list_show(&L); */
    return 0;
}
