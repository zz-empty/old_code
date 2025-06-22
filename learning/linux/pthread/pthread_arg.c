#include <func.h>
void *threadFunc(void *p);

int main() 
{
    pthread_t thid;
    pthread_t thid2;
    
    int ret;
    long num = 2;
    ret = pthread_create(&thid, NULL, threadFunc, (void*)num);
    THREAD_ERROR_CHECK(ret, "pthread_create");

    num += 2;
    ret = pthread_create(&thid2, NULL, threadFunc, (void*)num);

    printf("I am main thread\n");
    pthread_join(thid, NULL);
    return 0;
}

void *threadFunc(void *p){
    printf("I am child thread, num = %ld\n", (long)p);
    pthread_exit(NULL);
}
