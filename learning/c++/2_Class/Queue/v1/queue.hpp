#ifndef __QUEUE_HPP__
#define __QUEUE_HPP__

namespace wd
{

class Queue
{
public:
    Queue(int sz = 10)
    :_front(0)
    ,_rear(0)
    ,_size(sz)
    ,_pdata(new int[_size]())
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
    int size() const    {   return _size;   }
    
    int front() const   {   return _pdata[_front];  }
    int back() const    {   return _pdata[(_rear - 1 + _size) % _size]; }

    bool pop();
    bool push(int);
private:
    int _front;
    int _rear;
    int _size;
    int *_pdata;
};

}//end of namespace wd

#endif
