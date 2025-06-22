#include "Singleton.hpp"
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

AutoRelease::~AutoRelease()
{
    if (Singleton::getInstance()) {
        Singleton::destroy();
    }
}

}//end of namespace wd
