#ifndef __QUEUE_HPP__
#define __QUEUE_HPP__

#include <iostream>

namespace wd
{

template<typename T, size_t KSize = 10>
class Queue
{
public:
    Queue()
    :_front(0)
    ,_rear(0)
    ,_size(KSize)
    ,_pdata(new T[_size]())
    {}

    ~Queue()
    {
        if (_pdata) {
            delete [] _pdata;
            _pdata = nullptr;
        }
    }

    bool empty() const  {   return _front == _rear;     }
    bool full() const   {   return (_rear + 1) % _size == _front;   }
    size_t size() const    {   return _size;   }
    
    T front() const   {   return _pdata[_front];  }
    T back() const    {   return _pdata[(_rear - 1 + _size) % _size]; }

    bool pop();
    bool push(const T &);
private:
    int _front;
    int _rear;
    size_t _size;
    T *_pdata;
};

template<typename T, size_t KSize>
bool Queue<T, KSize>::pop()
{
    if (!empty()) {
        _front = (_front + 1) % _size;
        return true;
    }
    return false;
}

template<typename T, size_t KSize>
bool Queue<T, KSize>::push(const T &val)
{
    if (!full()) {
        _pdata[_rear] = val;
        _rear = (_rear + 1) % _size;
        return true;
    }
    return false;
}

}//end of namespace wd


#endif
