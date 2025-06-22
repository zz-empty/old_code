#include <func.h>
void *threadFunc(void *p) {
    pthread_detach(pthread_self());
    puts("This is thread");
    sleep(2);
    pthread_exit(NULL);
}

int main() 
{
    pthread_t thid;
    pthread_attr_t attr;
    int ret;

    pthread_attr_init(&attr);
    /* pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED); */

    ret = pthread_create(&thid, &attr, threadFunc, NULL);
    THREAD_ERROR_CHECK(ret, "pthread_create");

    printf("I am main thread\n");
    sleep(1);

    ret = pthread_join(thid, NULL);
    THREAD_ERROR_CHECK(ret, "pthread_join");
    ret = pthread_attr_destroy(&attr);
    THREAD_ERROR_CHECK(ret, "pthread_attr_destroy");
    return 0;
}

