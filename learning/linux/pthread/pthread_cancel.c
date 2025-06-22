#include <func.h>
void *threadFunc(void *p);
int main() 
{
    pthread_t thid;
    int ret = 0;

    ret = pthread_create(&thid, NULL, threadFunc, NULL);
    THREAD_ERROR_CHECK(ret, "pthread_create");

    printf("I am main thread\n");

    ret = pthread_cancel(thid);
    THREAD_ERROR_CHECK(ret, "pthread_cancel");

    ret = pthread_join(thid, NULL);
    THREAD_ERROR_CHECK(ret, "pthread_join");

    return 0;
}

void *threadFunc(void *p){
    while(1);
    sleep(1);
    printf("I am child thread\n");
    printf("hellomain\n");
    pthread_exit(NULL);
}
