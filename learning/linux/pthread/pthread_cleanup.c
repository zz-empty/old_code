#include <func.h>
void cleanFunc(void *p);
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
    printf("over\n");
    return 0;
}

void cleanFunc(void *p){
    printf("cleanFunc\n");
    free(p);
    p = NULL;
}
void *threadFunc(void *p) {
    char *p1 = (char*)malloc(20);
    strcpy(p1, "hello");

    pthread_cleanup_push(cleanFunc, p1);

    printf("p1 = %s\n", p1);

    usleep(1);
    free(p1);
    p1 = NULL;
    printf("free succeed\n");

    pthread_cleanup_pop(1);
    pthread_exit(NULL);
}
