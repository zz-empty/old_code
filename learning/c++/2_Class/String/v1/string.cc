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
:_pstr(nullptr)
{}

String::~String()
{
    if (_pstr) {
        delete [] _pstr;
        _pstr = nullptr;
    }
}

String::String(const char *pstr)
:_pstr(new char[strlen(pstr) + 1]())
{
    strcpy(_pstr, pstr);
}

String::String(const String &rhs)
:_pstr(new char[strlen(rhs._pstr) + 1]())
{
    strcpy(_pstr, rhs._pstr);
}

String &String::operator=(const String &rhs)
{
    if (this != &rhs) {
        if (_pstr) {
            delete [] _pstr;
            _pstr = nullptr;
        }
        
        _pstr = new char[strlen(rhs._pstr) + 1]();
        strcpy(_pstr, rhs._pstr);
    }
    return *this;
}

String &String::operator=(const char *str)
{
    if (_pstr) {
        delete [] _pstr;
        _pstr = nullptr;
    }

    _pstr = new char[strlen(str) + 1]();
    strcpy(_pstr, str);
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
    String tmp = *this;
    if (_pstr) {
        delete [] _pstr;
        _pstr = nullptr;
    }

    _pstr = new char[strlen(tmp._pstr) + strlen(rhs._pstr) + 1]();
    strcpy(_pstr, tmp._pstr);
    strcat(_pstr, rhs._pstr);
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
        return _pstr[idx];
    }
    static char tmp = '\0';
    return tmp;
}

const char &String::operator[](size_t idx) const
{
    if (idx < size()) {
        return _pstr[idx];
    }
    static char tmp = '\0';
    return tmp;
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
        os << rhs._pstr << endl;
    }
    return os;
}

std::istream &operator>>(std::istream &is, String &rhs)
{
    //release *this
    if (rhs._pstr) {
        delete [] rhs._pstr;
        rhs._pstr = nullptr;
    }

    //use vector store istream_char
    vector<char> buf;    
    char ch;
    while ((ch = is.get()) != '\n') {
        buf.push_back(ch);
    }

    //rebuild string with vector
    rhs._pstr = new char[buf.size() + 1];
    memcpy(rhs._pstr, &buf[0], buf.size());

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
