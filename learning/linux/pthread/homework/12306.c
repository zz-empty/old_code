#include <func.h>
typedef struct {
    int num;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
}Data_t;
void *setTickets(void *p);
void *sellWin1(void *p);
void *sellWin2(void *p);

int main() 
{
    pthread_t thid; //set tickets
    pthread_t win1; //sell win1
    pthread_t win2;
    int ret;
    Data_t data;

    data.num = 0;
    pthread_mutex_init(&data.mutex, NULL);
    pthread_cond_init(&data.cond, NULL);

    ret = pthread_create(&thid, NULL, setTickets, &data);
    THREAD_ERROR_CHECK(ret, "pthread_create_set");
    
    ret = pthread_create(&win1, NULL, sellWin1, &data);
    THREAD_ERROR_CHECK(ret, "pthread_create_win1");
    ret = pthread_create(&win2, NULL, sellWin2, &data);
    THREAD_ERROR_CHECK(ret, "pthread_create_win2");

    ret = pthread_join(win1, NULL);
    THREAD_ERROR_CHECK(ret, "join_win1");
    ret = pthread_join(win2, NULL);
    THREAD_ERROR_CHECK(ret, "join_win2");
    ret = pthread_join(thid, NULL);
    THREAD_ERROR_CHECK(ret, "join_set");

    return 0;
}

void *setTickets(void *p) {
    Data_t *pData = (Data_t*)p;
    int i = 0;
    for (i = 0; i < 5; ++i) {
        pthread_mutex_lock(&pData->mutex);
        if (0 < pData->num) {
            pthread_cond_wait(&pData->cond, &pData->mutex);
        }
        pData->num = 10;
        printf("放票啦, tickets:%d\n", pData->num);
        pthread_mutex_unlock(&pData->mutex);
    }
    pthread_exit(NULL);
}
void *sellWin1(void *p) {
    Data_t *pData = (Data_t*)p;
    while(1) {
        pthread_mutex_lock(&pData->mutex);
        if (0 != pData->num) {
            pData->num--;
            printf("win1 sale a ticket!, rest:%d\n", pData->num);
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
void *sellWin2(void *p) {
    Data_t *pData = (Data_t*)p;
    while(1) {
        pthread_mutex_lock(&pData->mutex);
        if (0 != pData->num) {
            pData->num--;
            printf("win2 sale a ticket!, rest:%d\n", pData->num);
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
