#include "rectangle.h"
#include <iostream>

using std::cout;
using std::endl;


Rectangle::Rectangle(float len, float wide)
{
    if (len > 0) {
        _len = len;
    }
    else {
        cout << "ERROR! len is illegal!" << endl;
        _len = 1;
    }

    if (0 < wide) {
        _wide = wide;
    }
    else {
        cout << "ERROR! wide is illegal!" << endl;
        _wide = 1;
    }
}
Rectangle::~Rectangle()
{

}

bool Rectangle::setLen(float len)
{
    if (0 >= len) {
        cout << "ERROR! len is illegal!" << endl;
        return false;
    }
    _len = len;
    return true;
}
bool Rectangle::setWide(float wide)
{
    if (0 >= wide) {
        cout << "ERROR! wide is illegal!" << endl;
        return false;
    }
    _wide = wide;
    return true;
}

float Rectangle::perimeter()
{
    return (_len + _wide) * 2;
}
float Rectangle::area()
{
    return _len * _wide;
}
