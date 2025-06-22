#include <func.h>
typedef struct {
    int num;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
}Data_t;

void* saleWindow1(void* p)
{
    Data_t *pData = (Data_t*)p;
    while(1){
        pthread_mutex_lock(&pData->mutex);
        if(0 != pData->num){
            pData->num--;
            printf("win1 sale a ticket\n");
            if(0 == pData->num){
                pthread_cond_signal(&pData->cond);
            }
        }
        //如果票是被另一个窗口卖光的也通知放票窗口放票
        else{
            pthread_cond_signal(&pData->cond);
        }
        pthread_mutex_unlock(&pData->mutex);
        /* sleep(1); */
    }
    pthread_exit(NULL);
}
void* saleWindow2(void* p)
{
    Data_t *pData = (Data_t*)p;
    while(1){
        pthread_mutex_lock(&pData->mutex);
        if(0 != pData->num){
            pData->num--;
            printf("win2 sale a ticket\n");
            if(0 == pData->num){
                pthread_cond_signal(&pData->cond);
            }
        }
        //如果票是被另一个窗口卖光的也通知放票窗口放票
        else{
            pthread_cond_signal(&pData->cond);
        }
        pthread_mutex_unlock(&pData->mutex);
        sleep(1);
    }
    pthread_exit(NULL);
}

void* setTickets(void* p)
{
    Data_t *pData = (Data_t*)p;
    pthread_mutex_lock(&pData->mutex);
    if(0 != pData->num){
        pthread_cond_wait(&pData->cond, &pData->mutex);
    }
    pData->num = 10;
    printf("setTickets\n");
    pthread_mutex_unlock(&pData->mutex);
    pthread_exit(NULL);
}
int main(int argc, char** argv)
{
    pthread_t thid1, thid2, thid3;
    Data_t data;
    data.num = 10;
    int ret = 0;
    pthread_mutex_init(&data.mutex, NULL);
    pthread_cond_init(&data.cond, NULL);
    ret = pthread_create(&thid1, NULL, saleWindow1, &data);
    THREAD_ERROR_CHECK(ret, "pthread_create1");
    ret = pthread_create(&thid2, NULL, saleWindow2, &data);
    THREAD_ERROR_CHECK(ret, "pthread_create2");
    ret = pthread_create(&thid3, NULL, setTickets, &data);
    THREAD_ERROR_CHECK(ret, "pthread_creater3");

    pthread_join(thid1, NULL);
    pthread_join(thid2, NULL);
    pthread_join(thid3, NULL);

    pthread_mutex_destroy(&data.mutex);
    pthread_cond_destroy(&data.cond);
    return 0;
}
