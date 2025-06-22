#ifndef __STRING_HPP__
#define __STRING_HPP__

#include <iostream>

namespace wd
{

class String
{
public:
    String();
    ~String();

    String(const char *pstr);
    String(const String &rhs);
    String &operator=(const String &rhs);
    String &operator=(const char *str);

    String &operator+=(const String &rhs);
    String &operator+=(const char *str);

    char &operator[](size_t idx);
    const char &operator[](size_t idx) const;

    std::size_t size() const;
    std::size_t  length() const;
    const char *c_str() const;

    friend bool operator==(const String &lhs, const String &rhs);
    friend bool operator!=(const String &lhs, const String &rhs);

    friend bool operator<(const String &lhs, const String &rhs);
    friend bool operator>(const String &lhs, const String &rhs);
    friend bool operator<=(const String &lhs, const String &rhs);
    friend bool operator>=(const String &lhs, const String &rhs);

    friend std::ostream &operator<<(std::ostream &os, const String &rhs);
    friend std::istream &operator>>(std::istream &is, String &s);

private:
    char *_pstr;
};

String operator+(const String &, const String &);
String operator+(const String &, const char *);
String operator+(const char *, const String &);

}//end of namespace wd

#endif
