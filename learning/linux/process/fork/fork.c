#include <func.h>
int global = 1;
int main()
{
    pid_t pid = fork();
    int stack = 2;
    int *pheap = (int*)malloc(sizeof(int));
    *pheap = 3;

    if (0 == pid) {
        printf("child! global = %d, stack = %d, heap = %d\n", global, stack, *pheap);
        ++global;
        ++stack;
        ++*pheap;
        printf("child! global = %d, stack = %d, heap = %d\n", global, stack, *pheap);
        exit(0);
    }
    else {
        printf("parent! global = %d, stack = %d, heap = %d\n", global, stack, *pheap);
        global += 2;
        stack += 2;
        *pheap += 2;
        printf("parent! global = %d, stack = %d, heap = %d\n", global, stack, *pheap);
        wait(NULL);
    }
    return 0;
}

