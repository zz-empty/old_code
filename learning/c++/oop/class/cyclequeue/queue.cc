#include "queue.h"
#include <iostream>

using std::cout;
using std::endl;


Queue::Queue(int sz)
: _size(sz)
, _front(0)
, _rear(0)
, _data(new int[sz]())
{
    cout << "Queue(int = 10)" << endl;
}

Queue::~Queue()
{
    cout << "~Queue()" << endl;
    if (_data) {
        delete [] _data;
        _data = nullptr;
    }
}

bool Queue::empty() const
{
    return _front == _rear;
}

bool Queue::full() const
{
    return (_rear + 1) % _size == _front;
}

void Queue::enQueue(const int &value)
{
    if (!full()) {
        _data[_rear] = value;
        _rear = (_rear + 1) % _size;
    }
    else {
        cout << "The queue is full, cannot insert!" << endl;
    }
}

void Queue::deQueue()
{
    if (!empty()) {
        _front = (_front + 1) % _size;
    }
    else {
        cout << "The queue is empty, cannot remove!" << endl;
    }
}

int Queue::getFront() const
{
    return _front;
}

int Queue::getRear() const
{
    return _rear;
}

int Queue::front() const
{
    return _data[_front];
}

int Queue::rear() const
{
    return _data[(_rear - 1 + _size) % _size];
}

void Queue::print()
{
    int ptr = _front;

    while (_rear != ptr) {
        cout << _data[ptr] << " ";
        ptr = (ptr + 1) % _size;
    }
    cout << endl;
}
