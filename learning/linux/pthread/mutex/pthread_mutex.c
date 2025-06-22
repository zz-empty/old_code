#include <func.h>

int main() 
{
    pthread_mutex_t mutex;
    int ret;

    ret = pthread_mutex_init(&mutex, NULL);
    THREAD_ERROR_CHECK(ret, "init_mutex");

    ret = pthread_mutex_destroy(&mutex);
    THREAD_ERROR_CHECK(ret, "destory_mutex");
    return 0;
}

