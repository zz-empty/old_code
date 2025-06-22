#ifndef __STRING_H__
#define __STRING_H__

#include <iostream>

class String
{
public:
    String();//ok
    String(int sz);
    String(const char *str);//ok
    String(const String &rhs);//ok
    ~String();//ok

    String &operator=(const String &rhs);//ok
    String &operator=(const char *str);//ok

    String &operator+=(const String &rhs);//ok
    String &operator+=(const char *);//ok

    char &operator[](size_t idx);//ok
    const char &operator[](size_t idx) const;//ok

    size_t size() const;//ok
    const char *c_str() const;//ok
    char *&getStr();

    friend bool operator==(const String &lhs, const String &rhs);//ok
    friend bool operator!=(const String &lhs, const String &rhs);//ok

    friend bool operator<(const String &lhs, const String &rhs);//ok
    friend bool operator>(const String &lhs, const String &rhs);//ok
    friend bool operator<=(const String &lhs, const String &rhs);//ok
    friend bool operator>=(const String &lhs, const String &rhs);//ok

    friend std::ostream &operator<<(std::ostream &os, const String &rhs);//ok
    friend std::istream &operator>>(std::istream &is, String &s);

    friend String operator+(const String &, const String &);
    friend String operator+(const String &, const char *);
    friend String operator+(const char *, const String &);
private:
    char *_pstr;
};


#endif
