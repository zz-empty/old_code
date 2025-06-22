#include "Singleton.hpp"
#include <stdlib.h>
#include <iostream>

using std::cout;
using std::endl;

namespace wd
{

Singleton *Singleton::_pOnly = nullptr;

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
    if (!_pOnly) {
        _pOnly = new Singleton();
        atexit(destroy);
    } 
    return _pOnly;
}

void Singleton::destroy()
{
    if (_pOnly) {
        delete _pOnly;
        _pOnly = nullptr;
    }
}


}//end of namespace wd
