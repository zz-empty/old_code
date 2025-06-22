#ifndef __STACK_HPP__
#define __STACK_HPP__

namespace myclass
{

class Stack
{
public:
    Stack(int sz = 10)
    :_size(sz)
    ,_pdata(new int[_size]())
    {}

    ~Stack()
    {
        if (_pdata) {
            delete [] _pdata;
            _pdata = nullptr;
        }
    }

    Stack(const Stack &rhs);
    Stack &operator=(const Stack &rhs);

    bool push(const int &val);
    bool pop();
    int top() const;
    bool empty() const { return -1 == _top; }
    bool full() const { return _top == _size - 1; }

private:
    int _size;
    int _top = -1;   //栈顶指针
    int *_pdata;
};

}//end of namespace myclass

#endif
