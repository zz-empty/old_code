#include "string.hpp"
#include <string.h>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

namespace wd
{
String::String()
:_pstr(new char[5]() + 4)
{
    initRefCount(); 
}

String::~String()
{
    release();
}

int String::getRefCount() const
{
    return *(int*)(_pstr - 4);
}
void String::initRefCount()
{
    *(int*)(_pstr - 4) = 1;
}
void String::increaseRefCount()
{
    ++*(int*)(_pstr - 4);
}
void String::decreaseRefCount()
{
    --*(int*)(_pstr - 4);
}
void String::release()
{
    if (getRefCount()) {
        decreaseRefCount();
    }
    else {
        delete [] (_pstr - 4);
    }
}

String::String(const char *pstr)
:_pstr(new char[strlen(pstr) + 5]() + 4)
{
    strcpy(_pstr, pstr);
    initRefCount();
}

String::String(const String &rhs)
:_pstr(rhs._pstr)
{
    cout << "String(const String &)" << endl;
    increaseRefCount();
}

String &String::operator=(const String &rhs)
{
    cout << "String &operator=(const String &)" << endl;
    if (this != &rhs) {
        release();
        _pstr = rhs._pstr;
        increaseRefCount();
    }
    return *this;
}

String &String::operator=(const char *str)
{
    *this = String(str);
    return *this;
}

std::size_t String::size() const
{
    if (_pstr) {
        return strlen(_pstr);
    }
    return 0;
}

std::size_t  String::length() const
{
    if (_pstr) {
        return strlen(_pstr);
    }
    return 0;
}

const char *String::c_str() const
{
    if (_pstr) {
        char *str = new char[size() + 1]();
        strcpy(str, _pstr);
        return str;
    }
    return nullptr;
}

String &String::operator+=(const String &rhs)
{
    if (rhs.getRefCount()) {
        String tmp = *this;
        release();

        _pstr = new char[strlen(tmp._pstr) + strlen(rhs._pstr) + 5]() + 4;
        strcpy(_pstr, tmp._pstr);
        strcat(_pstr, rhs._pstr);
        initRefCount();
    }
    return *this;
}

String &String::operator+=(const char *str)
{
    *this += String(str);
    return *this;
}

char &String::operator[](size_t idx)
{
    if (idx < size()) {

        //版本一，如果引用计数不唯一，则新建空间
        if (1 == getRefCount()) {
            return _pstr[idx];
        }

        char *ptmp = new char[strlen(_pstr) + 5]() + 4;
        strcpy(ptmp, _pstr);
        decreaseRefCount();

        _pstr = ptmp;
        initRefCount();
        return _pstr[idx];
    }
    else {
        static char tmp = '\0';
        return tmp;
    }
}


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
    return strcmp(lhs._pstr, rhs._pstr) < 0;
}
bool operator>(const String &lhs, const String &rhs)
{
    return strcmp(lhs._pstr, rhs._pstr) > 0;
}
bool operator<=(const String &lhs, const String &rhs)
{
    return strcmp(lhs._pstr, rhs._pstr) <= 0;
}
bool operator>=(const String &lhs, const String &rhs)
{
    return strcmp(lhs._pstr, rhs._pstr) >= 0;
}

std::ostream &operator<<(std::ostream &os, const String &rhs)
{
    if (rhs.size()) {
        os << rhs._pstr;
    }
    return os;
}

std::istream &operator>>(std::istream &is, String &rhs)
{
    //release *this
    rhs.release();

    //use vector store istream_char
    vector<char> buf;    
    char ch;
    while ((ch = is.get()) != '\n') {
        buf.push_back(ch);
    }

    //rebuild string with vector
    rhs._pstr = new char[buf.size() + 5]() + 4;
    memcpy(rhs._pstr, &buf[0], buf.size());
    rhs.initRefCount();

    return is;
}

String operator+(const String &lhs, const String &rhs)
{
    String tmp(lhs);
    tmp += rhs;
    return tmp;
}
String operator+(const String &lhs, const char *str)
{
    String tmp(lhs);
    tmp += str;
    return tmp;
}
String operator+(const char *str, const String &rhs)
{
    String tmp(str);
    tmp += rhs;
    return tmp;
}

}//end of namespace wd
