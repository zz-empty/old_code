#include <func.h>
void *threadFunc(void *p) {
    long ret = 3;
    pthread_exit((void*)ret);
}
int main() {
    pthread_t thid;
    int ret;
    ret = pthread_create(&thid, NULL, threadFunc, NULL);
    THREAD_ERROR_CHECK(ret, "pthread_create");

    long retVal = 0;
    ret = pthread_join(thid, (void**)&retVal);
    printf("retVal = %ld\n", retVal);
    return 0;
}
