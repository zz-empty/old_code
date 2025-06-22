#include <func.h>
void *threadFunc(void *p);
typedef struct {
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int goods_amount;
}Data_t;

/*
   main produce
   thread cunsume
   */

int main() 
{
    pthread_t thid;
    pthread_t thid2;
    Data_t data;
    int ret;

    //init data
    pthread_mutex_init(&data.mutex, NULL);
    pthread_cond_init(&data.cond, NULL);
    data.goods_amount = 0;
    //create thread
    ret = pthread_create(&thid, NULL, threadFunc, &data);
    THREAD_ERROR_CHECK(ret, "pthread_create1");
    ret = pthread_create(&thid2, NULL, threadFunc, &data);
    THREAD_ERROR_CHECK(ret, "pthread_create2");
    sleep(1);

    //produce
    pthread_mutex_lock(&data.mutex);
    data.goods_amount++;
    pthread_cond_broadcast(&data.cond);
    puts("来酒啦");
    printf("main nums = %d\n", data.goods_amount);
    pthread_mutex_unlock(&data.mutex);

    //release resource
    ret = pthread_join(thid, NULL);
    THREAD_ERROR_CHECK(ret, "pthread_join");
    ret = pthread_join(thid2, NULL);
    THREAD_ERROR_CHECK(ret, "pthread_join2");
    ret = pthread_mutex_destroy(&data.mutex);
    THREAD_ERROR_CHECK(ret, "mutex_destory");
    ret = pthread_cond_destroy(&data.cond);
    THREAD_ERROR_CHECK(ret, "cond_destory");
    return 0;
}

void *threadFunc(void *p) {
    Data_t *pData = (Data_t*)p;
    int ret = 0;

    //consume
    pthread_mutex_lock(&pData->mutex);
    printf("before wait, num = %d\n", pData->goods_amount);
    ret = pthread_cond_wait(&pData->cond, &pData->mutex);
    THREAD_ERROR_CHECK(ret, "pthread_cond_timedwait");
    printf("after wait, num = %d\n", pData->goods_amount);
    pData->goods_amount--;
    puts("买到了");
    pthread_mutex_unlock(&pData->mutex);

    pthread_exit(NULL); 
}
