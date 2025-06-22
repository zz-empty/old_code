#ifndef __SINGLETON_HPP__
#define __SINGLETON_HPP__

#include <stdlib.h>

namespace wd
{

template<typename T>
class Singleton
{
public:
    template<typename ...Args>
    static T* getInstance(Args ...args);
    static void destroy();

private:
    Singleton() = default;
    ~Singleton() = default;
    Singleton(const Singleton &) = delete;
    Singleton &operator=(const Singleton &) = delete;

private:
    static T *_pOnly;
    T *_pT;
};

template<typename T>
T *Singleton<T>::_pOnly = nullptr;


template<typename T>
template<typename ...Args>
T* Singleton<T>::getInstance(Args... args)
{
    if (nullptr == _pOnly) {
        atexit(destroy);
        _pOnly = new T(args...);
    } 
    return _pOnly;
}

template<typename T>
void Singleton<T>::destroy()
{
    if (_pOnly) {
        delete _pOnly;
        _pOnly = nullptr;
    }
}
}// end of namespace wd

#endif
