#include "string.h"
#include <iostream>

using std::cout;
using std::endl;


class String
{
public:
    String(const char *str)
    :_pstr(new char[strlen(str) + 1]())
    {
        strcpy(_pstr, str);
    }
    String(const String &rhs)
    :_pstr(new char[strlen(rhs._pstr) + 1]())
    {
        strcpy(_pstr, rhs._pstr);
    }
    String &operator=(const String &rhs)
    {
        if (this != &rhs) {
            delete [] _pstr;
            _pstr = nullptr;
            _pstr = new char[strlen(rhs._pstr) + 1]();
            strcpy(_pstr, rhs._pstr);
        }
        return *this;
    }

    String(String &&rhs) 
    :_pstr(rhs._pstr)
    {
        cout << "String(const String &&)" << endl;
        rhs._pstr = nullptr;
    }

    String &operator=(String &&rhs)
    {
        cout << "String &operator=(String &&)" << endl;
        if (this != &rhs) {
            delete [] _pstr;
            _pstr = nullptr;

            _pstr = rhs._pstr;
            rhs._pstr = nullptr;
        }
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &os, const String &rhs);
private:
    char *_pstr;
};

std::ostream &operator<<(std::ostream &os, const String &rhs)
{
    if (rhs._pstr) {
        os << rhs._pstr;
    }
    return os;
}

int main()
{
    String s1("hello");
    cout << "s1 = " << s1 << endl;
    String s2(s1);
    cout << "s2 = " << s2 << endl;
    s1 = s2;
    cout << "s1 = " << s1 << endl;

    cout << endl;
    String s3(std::move(s2));
    cout << "s3 = " << s3 << endl;
    cout << "s2 = " << s2 << endl;
    s3 = std::move(s1);
    cout << "s3 = " << s3 << endl;
    cout << "s1 = " << s1 << endl;
    return 0;
}

