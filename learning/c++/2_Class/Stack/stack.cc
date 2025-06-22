#include "stack.hpp"
#include <iostream>

namespace myclass
{

Stack::Stack(const Stack &rhs)
:_size(rhs._size)
,_top(rhs._top)
,_pdata(new int[_size]())
{
    _pdata = rhs._pdata;
}

Stack & Stack::operator=(const Stack &rhs)
{
    if (this != &rhs) {
        if (_pdata) {
            delete [] _pdata;
            _pdata = nullptr;
        }

        _size = rhs._size;
        _top = rhs._top;
        _pdata = new int[_size]();
        _pdata = rhs._pdata;
    }
    return *this;
}

bool Stack::push(const int &val)
{
    if (!full()) {
        _pdata[++_top] = val;
        return true;
    }
    return false;
}

bool Stack::pop()
{
    if (!empty()) {
        --_top;
        return true;
    }
    return false;
}

int Stack::top() const
{
    if (!empty()) {
        return _pdata[_top];
    }
    return -1;
}

}//end of namespace myclass
