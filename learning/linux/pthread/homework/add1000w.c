#include <func.h>
typedef struct {
    int num;
    pthread_mutex_t mutex;
}Data_t;
void *threadFunc(void *p);
void cleanFunc(void *p);

int main() 
{
    pthread_t thid1;
    pthread_t thid2;
    int ret = 0;
    Data_t data;

    data.num = 0;
    pthread_mutex_init(&data.mutex, NULL);

    ret = pthread_create(&thid1, NULL, threadFunc, &data);
    THREAD_ERROR_CHECK(ret, "create1");
    ret = pthread_create(&thid2, NULL, threadFunc, &data);

    /* pthread_cancel(thid1); */
    /* pthread_cancel(thid2); */

    ret = pthread_join(thid1, NULL);
    THREAD_ERROR_CHECK(ret, "join1");
    ret = pthread_join(thid2, NULL);
    THREAD_ERROR_CHECK(ret, "join2");

    printf("I am main thread!, total = %d\n", data.num);
    pthread_mutex_lock(&data.mutex);
    pthread_mutex_unlock(&data.mutex);

    ret = pthread_mutex_destroy(&data.mutex);
    THREAD_ERROR_CHECK(ret, "pthread_mutex_destroy");

    return 0;
}

void *threadFunc(void *p) {
    Data_t *pData = (Data_t*)p;
    int i = 0;
    for (i = 0; i < 10000000; ++i) {
        pthread_mutex_lock(&pData->mutex);
        pData->num++;
        pthread_cleanup_push(cleanFunc, &pData->mutex);
        pthread_mutex_unlock(&pData->mutex);
        pthread_cleanup_pop(0);
    }
    pthread_exit(NULL);
}
void cleanFunc(void *p) {
    printf("cleanFunc\n");
    pthread_mutex_t *mutex = (pthread_mutex_t*)p;
    pthread_mutex_unlock(mutex);
}
