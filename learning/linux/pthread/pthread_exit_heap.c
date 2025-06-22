#include <func.h>
void *threadFunc(void *p) {
    char *p1 = (char*)malloc(20);
    strcpy(p1, "hello");
    pthread_exit(p1);
}
int main() {
    pthread_t thid;
    int ret;
    ret = pthread_create(&thid, NULL, threadFunc, NULL);
    THREAD_ERROR_CHECK(ret, "pthread_create");

    char *retVal = NULL;
    ret = pthread_join(thid, (void**)&retVal);
    printf("retVal = %s\n", retVal);
    free(retVal);
    retVal = NULL;
    return 0;
}
