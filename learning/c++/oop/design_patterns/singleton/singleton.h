#ifndef __SINGLETON_H__
#define __SINGLETON_H__

class Singleton
{
public:
    static Singleton *getInstance();
    static void destroy();

private:
    Singleton();
    ~Singleton();
    Singleton(const Singleton &rhs) = delete;
    Singleton &operator=(const Singleton &rhs) = delete;

    static Singleton * _pOnly;
};


#endif
