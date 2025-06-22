#include <func.h>
typedef struct {
    int num;
    pthread_mutex_t mutex;
}Data_t;
void *threadFunc(void *p);

int main() 
{
    pthread_t thid1;
    pthread_t thid2;
    int ret;
    Data_t data;

    data.num = 100;
    pthread_mutex_init(&data.mutex, NULL);

    ret = pthread_create(&thid1, NULL, threadFunc, &data);
    THREAD_ERROR_CHECK(ret, "pthread_create1");
    ret = pthread_create(&thid2, NULL, threadFunc, &data);
    THREAD_ERROR_CHECK(ret, "pthread_create2");

    ret = pthread_join(thid1, NULL);
    THREAD_ERROR_CHECK(ret, "pthread_join1");
    ret = pthread_join(thid2, NULL);
    THREAD_ERROR_CHECK(ret, "pthread_join2");
    return 0;
}

void *threadFunc(void *p) {
    Data_t *pData = (Data_t*)p;

    int count = 0;
    while (pData->num > 0) {
        pthread_mutex_lock(&pData->mutex);
        if (0 < pData->num) {
            pData->num--;
            count++;
        }
        pthread_mutex_unlock(&pData->mutex);
    }
    printf("thread count = %d\n", count);
    
    pthread_exit(NULL);
}
