#include "stack.h"
#include <iostream>

using std::cout;
using std::endl;

Stack::Stack(int sz)
: _size(sz)
, _top(-1)
, _data(new int[_size]())
{
    cout << "Stack(int = 10)" << endl;
}

Stack::~Stack()
{
    cout << "~Stack()" << endl;
    if (_data) {
        delete [] _data;
    }
}

bool Stack::empty()
{
    return -1 == _top;
}

bool Stack::full()
{
    return _top == (_size - 1);//都是下标
}

void Stack::push(const int &value)
{
    if (!full()) {
        _data[++_top] = value;
    }
    else {
        cout << "Stack is already full! cannot push!" << endl;
    }
}

void Stack::pop()
{
    if (!empty()) {
        --_top;
    }
    else {
        cout << "Stack is empty！cannot pop!" << endl;
    }
}

int Stack::top()
{
    return _data[_top];
}
