#include "Singleton.hpp"
#include <stdlib.h>
#include <pthread.h>
#include <iostream>

using std::cout;
using std::endl;

namespace wd
{

Singleton *Singleton::_pOnly = Singleton::getInstance();
pthread_once_t Singleton::_once = PTHREAD_ONCE_INIT;

Singleton::Singleton()
{
    cout << "Singleton()" << endl;
}

Singleton::~Singleton()
{
    cout << "~Singleton()" << endl;
}

Singleton* Singleton::getInstance()
{
    pthread_once(&_once, init);
    return _pOnly;
}

void Singleton::init()
{
    _pOnly = new Singleton();
    atexit(destroy);
}

void Singleton::destroy()
{
    if (_pOnly) {
        delete _pOnly;
        _pOnly = nullptr;
    }
}


}//end of namespace wd
