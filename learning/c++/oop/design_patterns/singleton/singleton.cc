#include "singleton.h"
#include <iostream>

using std::cout;
using std::endl;

Singleton *Singleton::getInstance()
{
    if (_pOnly == nullptr) {
        _pOnly = new Singleton();
    } 
    return _pOnly;
}

Singleton::Singleton()
{
    cout << "Singleton()" << endl;
}

Singleton::~Singleton()
{
    cout << "~Singleton()" << endl;
}

void Singleton::destroy()
{
    if (_pOnly) {
        delete _pOnly;
        _pOnly = nullptr;
    }
}

Singleton * Singleton::_pOnly = nullptr;
