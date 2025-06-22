#include <func.h>

int main() 
{
    pthread_mutex_t mutex;
    pthread_mutexattr_t mutexattr;
    int ret;
    pthread_mutexattr_init(&mutexattr);
    /* pthread_mutexattr_settype(&mutexattr, PTHREAD_MUTEX_RECURSIVE); */
    pthread_mutexattr_settype(&mutexattr, PTHREAD_MUTEX_ERRORCHECK);
    /* ret = pthread_mutex_init(&mutex, &mutexattr); */
    ret = pthread_mutex_init(&mutex, NULL);
    THREAD_ERROR_CHECK(ret, "init");

    ret = pthread_mutex_lock(&mutex);
    THREAD_ERROR_CHECK(ret, "lock");
    puts("1 lock");
    
    ret = pthread_mutex_lock(&mutex);
    THREAD_ERROR_CHECK(ret, "lock");
    puts("2 lock");

    ret = pthread_mutex_unlock(&mutex);
    THREAD_ERROR_CHECK(ret, "unlock");
    puts("2 unlock");

    ret = pthread_mutex_unlock(&mutex);
    THREAD_ERROR_CHECK(ret, "unlock");
    puts("1 unlock");
    
    ret = pthread_mutex_destroy(&mutex);
    THREAD_ERROR_CHECK(ret, "destroy");
    return 0;
}

