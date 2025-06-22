#include <func.h>
void *threadFunc(void *p);

int main() 
{
    pthread_t thread;
    int ret = 0;
    ret = pthread_create(&thread, NULL, threadFunc, NULL);
    
    printf("I am main pthread\n");
    usleep(1);    
    return 0;
}

void *threadFunc(void *p){
    printf("I am child pthread\n");
    pthread_exit(NULL);
}
