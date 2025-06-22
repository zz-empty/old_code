#include <string.h>
#include "string.h"
#include <iostream>

using std::cout;
using std::endl;

String::String()
    : _pstr(nullptr)
{
    cout << "String()" << endl;
}

String::~String()
{
    cout << "~String()" << endl;
}

String::String(const char *pstr)
:_pstr(new char[strlen(pstr) + 1]())
{
    cout << "String(const char *)" << endl;
    strcpy(_pstr, pstr);
}

void String::print()
{
    if (_pstr) {
        cout << "_pstr = " << _pstr << endl;
    }
}

String::String(const String &rhs)
{
    cout << "String(const String &)" << endl;
    if (rhs._pstr) {
        _pstr = new char[strlen(rhs._pstr) + 1]();
    }
    strcpy(_pstr, rhs._pstr);
}

String & String::operator=(const String &rhs)
{
    cout << "String& operator=(const String &)" << endl;
    if (this != &rhs) {
        delete [] _pstr;
        _pstr = nullptr;

        if (rhs._pstr) {
            _pstr = new char[strlen(rhs._pstr) + 1]();
        }
        strcpy(_pstr, rhs._pstr);
    }
    return *this;
}
