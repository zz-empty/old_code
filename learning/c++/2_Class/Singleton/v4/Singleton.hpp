#ifndef __SINGLETON_HPP__
#define __SINGLETON_HPP__

#include <pthread.h>

namespace wd
{

class Singleton
{
public:
    static Singleton* getInstance();
    static void destroy();

    static void init();

private:
    Singleton();
    ~Singleton();
    Singleton(const Singleton &) = delete;
    Singleton &operator=(const Singleton &) = delete;

private:
    static Singleton *_pOnly;
    static pthread_once_t _once;
};


}// end of namespace wd

#endif
