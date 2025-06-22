#include <func.h>
void cleanFunc(void *p);
void cleanFunc2(void *p);
void *threadFunc(void *p);
int main() 
{
    pthread_t thid;
    int ret = pthread_create(&thid, NULL, threadFunc, NULL);
    THREAD_ERROR_CHECK(ret, "pthread_create");

    printf("I am main thread\n");

    /* ret = pthread_cancel(thid); */
    /* THREAD_ERROR_CHECK(ret, "pthread_cancel"); */

    ret = pthread_join(thid, NULL);
    THREAD_ERROR_CHECK(ret, "pthread_join");
    printf("over\n");
    return 0;
}

void cleanFunc(void *p){
    printf("cleanFunc\n");
}
void cleanFunc2(void *p){
    printf("cleanFunc2\n");
}
void *threadFunc(void *p) {
    printf("I am child thread\n");
    pthread_cleanup_push(cleanFunc, NULL);

    pthread_cleanup_push(cleanFunc2, NULL);

    pthread_exit(NULL);
    pthread_cleanup_pop(0);
    pthread_cleanup_pop(0);
}
