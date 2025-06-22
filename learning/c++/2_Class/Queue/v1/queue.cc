#include "queue.hpp"
#include <iostream>

using std::cout;
using std::endl;

namespace wd
{
bool Queue::pop()
{
    if (!empty()) {
        _front = (_front + 1) % _size;
        return true;
    }
    return false;
}

bool Queue::push(int val)
{
    if (!full()) {
        _pdata[_rear] = val;
        _rear = (_rear + 1) % _size;
        return true;
    }
    return false;
}

}//end of namespace wd
