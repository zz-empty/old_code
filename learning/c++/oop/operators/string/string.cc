#include "string.h"
#include <string.h>
#include <iostream>

using std::cout;
using std::endl;

String::String()
:_pstr(nullptr)
{
    /* cout << "Constructor()" << endl; */
}

String::String(int sz)
{
    /* cout << "Constructor(int)" << endl; */
    if (sz) {
        _pstr = new char[sz]();
    }
    else {
        _pstr = nullptr;
    }
}

String::String(const char *str)
:_pstr(new char[strlen(str) + 1]())
{
    /* cout << "Constructor()" << endl; */
    strcpy(_pstr, str);
}

String::String(const String &rhs)
{
    /* cout << "Constructor()" << endl; */
    if (rhs._pstr) {
        _pstr = new char[strlen(rhs._pstr) + 1]();
        strcpy(_pstr, rhs._pstr);
    }
}

String::~String()
{
    /* cout << "~Constructor()" << endl; */
    if (_pstr) {
        delete [] _pstr;
        _pstr = nullptr;
    }
}

String &String::operator=(const String &rhs)
{
    if (this != &rhs) {
        delete [] _pstr;
        _pstr = nullptr;

        _pstr = new char[strlen(rhs._pstr) + 1]();
        strcpy(_pstr, rhs._pstr);
    }    
    return *this;
}

String &String::operator=(const char *str)
{
    delete [] _pstr;
    _pstr = nullptr;

    _pstr = new char[strlen(str) + 1]();
    strcpy(_pstr, str);
    return *this;
}

String &String::operator+=(const String &rhs)
{
    //if rhr._pstr = nullptr
    //if this->_pstr = nullptr
    if (!rhs._pstr) {
        return *this;
    }
    
    size_t len = rhs.size() + 1;
    String tmp;

    if (_pstr) {
        len += size();
        tmp = *this;
        delete [] _pstr;
        _pstr = nullptr;
    }


    _pstr = new char[len]();
    if (tmp._pstr) {
        strcpy(_pstr, tmp._pstr);
    }
    strcat(_pstr, rhs._pstr);

    return *this;
}

String &String::operator+=(const char *str)
{
    //first str is nullptr
    //second this->_pstr is nullptr
    if (nullptr == str) {
        return *this;
    }

    String tmp;
    size_t len = strlen(str) + 1;

    if (_pstr) {
        len += size();
        tmp = *this;
        delete [] _pstr;
        _pstr = nullptr;
    }

    _pstr = new char[len]();
    if (tmp._pstr) {
        strcpy(_pstr, tmp._pstr);
    }
    strcat(_pstr, str);
    return *this;
}

char &String::operator[](size_t idx)
{
    if (idx < size()) {
        return _pstr[idx];
    }
    else {
        static char nullChar = '\0';
        return nullChar;
    }
}

const char &String::operator[](size_t idx) const
{
    if (idx < size()) {
        return _pstr[idx];
    }
    else {
        static char nullChar = '\0';
        return nullChar;
    }
}

size_t String::size() const
{
    if (_pstr) {
        size_t len = strlen(_pstr);
        return len;
    }
    else {
        return 0;
    }
}

const char *String::c_str() const
{
    char *str = new char[size() + 1]();
    strcpy(str, _pstr);
    return str;
}

char *&String::getStr()
{
    return _pstr;
}

#if 1
bool operator==(const String &lhs, const String &rhs)
{
    return !strcmp(lhs._pstr, rhs._pstr);
}

bool operator!=(const String &lhs, const String &rhs)
{
    return strcmp(lhs._pstr, rhs._pstr);
}

bool operator<(const String &lhs, const String &rhs)
{
    return (0 > strcmp(lhs._pstr, rhs._pstr));
}
bool operator>(const String &lhs, const String &rhs)
{
    return !(lhs < rhs);
}
bool operator<=(const String &lhs, const String &rhs)
{
    if (lhs < rhs || lhs == rhs) {
        return true;
    }
    else {
        return false;
    }
}
bool operator>=(const String &lhs, const String &rhs)
{
    if (lhs > rhs || lhs == rhs) {
        return true;
    }
    else {
        return false;
    }
}

std::ostream &operator<<(std::ostream &os, const String &rhs)
{
    if (rhs._pstr) {
        os << rhs._pstr;
    }
    return os;
}

std::istream &operator>>(std::istream &is, String &s)
{
    is >> s._pstr;
    return is;
}
#endif

String operator+(const String &lhs, const String &rhs)
{
    String tmp(lhs.size() + rhs.size());
    strcpy(tmp._pstr, lhs._pstr);
    strcat(tmp._pstr, rhs._pstr);
    return tmp;
}

String operator+(const String &rhs, const char *str)
{
    String tmp(strlen(str) + rhs.size());
    strcpy(tmp._pstr, rhs._pstr);
    strcat(tmp._pstr, str);
    return tmp;
}

String operator+(const char *str, const String &rhs)
{
    String tmp(strlen(str) + rhs.size());
    strcpy(tmp._pstr, str);
    strcat(tmp._pstr, rhs._pstr);
    return tmp;

}
