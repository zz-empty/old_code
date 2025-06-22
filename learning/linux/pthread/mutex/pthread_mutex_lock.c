#include <func.h>

int main() 
{
    pthread_mutex_t mutex;
    int ret;

    ret = pthread_mutex_init(&mutex, NULL);
    THREAD_ERROR_CHECK(ret, "init_mutex");

    ret = pthread_mutex_lock(&mutex);
    THREAD_ERROR_CHECK(ret, "lock_mutex");
    puts("first lock_mutex");
    /* ret = pthread_mutex_lock(&mutex); */
    /* THREAD_ERROR_CHECK(ret, "lock_mutex"); */
    /* puts("second lock_mutex"); */

    ret = pthread_mutex_unlock(&mutex);
    THREAD_ERROR_CHECK(ret, "unlock_mutex");
    puts("unlock_mutex success!");

    ret = pthread_mutex_unlock(&mutex);
    THREAD_ERROR_CHECK(ret, "unlock_mutex");
    puts("unlock_mutex success!");
    ret = pthread_mutex_lock(&mutex);
    THREAD_ERROR_CHECK(ret, "lock_mutex");
    puts("second lock_mutex");

    /* ret = pthread_mutex_lock(&mutex); */
    /* THREAD_ERROR_CHECK(ret, "lock_mutex"); */
    /* puts("third lock_mutex"); */

    ret = pthread_mutex_destroy(&mutex);
    THREAD_ERROR_CHECK(ret, "destory_mutex");
    return 0;
}

