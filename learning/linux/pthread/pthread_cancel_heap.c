#include <func.h>
void *threadFunc(void *p);
int main() 
{
    pthread_t thid;
    int ret = pthread_create(&thid, NULL, threadFunc, NULL);
    THREAD_ERROR_CHECK(ret, "pthread_create");

    printf("I am main thread\n");

    ret = pthread_cancel(thid);
    THREAD_ERROR_CHECK(ret, "pthread_cancel");


    ret = pthread_join(thid, NULL);
    THREAD_ERROR_CHECK(ret, "pthread_join");

    return 0;
}

void *threadFunc(void *p) {
    char *p1= (char*)malloc(20);
    strcpy(p1, "hello");
    printf("p1 = %s\n", p1);
    
    free(p1);
    p1 = NULL;
    printf("free succeed\n");
    pthread_exit(NULL);
}
