#ifndef __STACK_H__
#define __STACK_H__

class Stack
{
public:
    Stack(int sz = 10);
    ~Stack();

    bool empty();
    bool full();
    void push(const int &value);
    void pop();
    int top();
private:
    int _size;
    int _top;
    int *_data;
};

#endif
