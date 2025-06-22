#include <func.h>
typedef struct {
    int num;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
}Data_t;
void *saleWindow1(void *p);
void *saleWindow2(void *p);
void *setTickets(void *p);

int main() 
{
    pthread_t thid1;
    pthread_t thid2;
    pthread_t thid3;
    Data_t data;
    int ret;

    data.num = 10;
    ret = pthread_mutex_init(&data.mutex, NULL);
    THREAD_ERROR_CHECK(ret, "pthread_mutex_init");
    ret = pthread_cond_init(&data.cond, NULL);
    THREAD_ERROR_CHECK(ret, "pthread_cond_init");

    ret = pthread_create(&thid1, NULL, saleWindow1, &data);
    THREAD_ERROR_CHECK(ret, "pthread_create1");
    ret = pthread_create(&thid2, NULL, saleWindow2, &data);
    THREAD_ERROR_CHECK(ret, "pthread_create2");
    ret = pthread_create(&thid3, NULL, setTickets, &data);
    THREAD_ERROR_CHECK(ret, "pthread_create3");

    ret = pthread_join(thid1, NULL);
    THREAD_ERROR_CHECK(ret, "pthread_join1");
    ret = pthread_join(thid2, NULL);
    THREAD_ERROR_CHECK(ret, "pthread_join2");
    ret = pthread_join(thid3, NULL);
    THREAD_ERROR_CHECK(ret, "pthread_join3");

    ret = pthread_mutex_destroy(&data.mutex);
    THREAD_ERROR_CHECK(ret, "pthread_mutex_destroy");
    ret = pthread_cond_destroy(&data.cond);
    THREAD_ERROR_CHECK(ret, "pthread_cond_destroy");
    return 0;
}

void *saleWindow1(void *p) {
    Data_t *pData = (Data_t*)p;
    while(1) {

        pthread_mutex_lock(&pData->mutex);
        if (0 != pData->num) {
            pData->num--;
            printf("win1 sale a ticket! the rest tikets:%d\n", pData->num);
            if (0 == pData->num) {
                //本窗口卖完最后一张票，通知放票
                pthread_cond_signal(&pData->cond);
            }
        }
        else {
            //票被另一个窗口卖光
            pthread_cond_signal(&pData->cond);
        }
        pthread_mutex_unlock(&pData->mutex);
    }
    pthread_exit(NULL);
}
void *saleWindow2(void *p) {
    Data_t *pData = (Data_t*)p;
    while(1) {

        pthread_mutex_lock(&pData->mutex);
        if (0 != pData->num) {
            pData->num--;
            printf("win2 sale a ticket! the rest tikets:%d\n", pData->num);
            if (0 == pData->num) {
                pthread_cond_signal(&pData->cond);
            }
        }
        else {
            pthread_cond_signal(&pData->cond);
        }
        pthread_mutex_unlock(&pData->mutex);

    }
    pthread_exit(NULL);
}
void *setTickets(void *p) {
    Data_t *pData = (Data_t*)p;

    int i = 0;
    for (i = 0; i < 5; ++i) {
        pthread_mutex_lock(&pData->mutex);
        if (0 != pData->num) {
            //等待放票
            pthread_cond_wait(&pData->cond, &pData->mutex);
            printf("empty, num = %d\n", pData->num);
        }
        pData->num = 10;
        printf("setTickets, total:%d, th:%d\n", pData->num, i+1);
        pthread_mutex_unlock(&pData->mutex);
    }
    pthread_exit(NULL);
}
