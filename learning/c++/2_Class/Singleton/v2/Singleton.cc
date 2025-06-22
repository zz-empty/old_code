#include "Singleton.hpp"
#include <iostream>

using std::cout;
using std::endl;

namespace wd
{

Singleton *Singleton::_pOnly = nullptr;
Singleton::AutoRelease Singleton::_auto;

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

Singleton::AutoRelease::~AutoRelease()
{
    cout << "~AutoRelease" << endl;
    if (_pOnly) {
        delete _pOnly;
        _pOnly = nullptr;
    }
}

Singleton::AutoRelease::AutoRelease()
{
    cout << "AutoRelease()" << endl;
}

}//end of namespace wd
