#ifndef __MYVECTOR_HPP__
#define __MYVECTOR_HPP__

#include <memory>

namespace myclass
{

template<typename T>
class MyVector
{
public:
    MyVector();
    ~MyVector();
    
    void push_back(const T &); 
    void pop_back();    
    int size() const;
    int capacity() const;

    T *begin() const;
    T *end() const;
    bool empty() const;
private:
    void reallocate();//重新分配内存,动态扩容要用的
private:    
    static std::allocator<T> _alloc;
    
    T *_start;                 //指向数组中的第一个元素
    T *_finish;                //指向最后一个实际元素之后的那个元素
    T *_end_of_storage;        //指向数组本身之后的位置
};

template<typename T>
T *MyVector<T>::begin() const
{
    return _start;
}

template<typename T>
T *MyVector<T>::end() const
{
    return _finish;
}

template<typename T>
bool MyVector<T>::empty() const
{
    return _start == _finish;
}

template<typename T>
std::allocator<T> MyVector<T>::_alloc;

template<typename T>
MyVector<T>::MyVector()
:_start(nullptr)
,_finish(nullptr)
,_end_of_storage(nullptr)
{}

template<typename T>
MyVector<T>::~MyVector()
{
    //清除数据成员
    if (_start) {
        while (_finish != _start) {
            _alloc.destroy(--_finish);
        }
    }
    //回收空间
    _alloc.deallocate(_start, capacity());
}

template<typename T>
void MyVector<T>::push_back(const T &val)
{
    if (size() == capacity()) {
        //扩容
        reallocate();
    }

    _alloc.construct(_finish++, val);
}

template<typename T>
void MyVector<T>::pop_back()
{
    _alloc.destroy(--_finish);
}

template<typename T>
int MyVector<T>::size() const
{
    return _finish - _start;
}

template<typename T>
int MyVector<T>::capacity() const
{
    return _end_of_storage - _start;
}

template<typename T>
void MyVector<T>::reallocate()
{
    //新空间大小
    int old_capacity = capacity();
    int new_capacity = old_capacity > 0 ? 2 * old_capacity : 1;

    //申请新空间
    T *pTmp = _alloc.allocate(new_capacity);
    if (_start) {
        //拷贝数据
        std::uninitialized_copy(_start, _finish, pTmp);
        //销毁旧空间
        while (_finish != _start) {
            _alloc.destroy(--_finish);
        }
        _alloc.deallocate(_start, old_capacity);
    }

    //更新迭代器
    _start = pTmp;
    _finish = _start + old_capacity;
    _end_of_storage = _start + new_capacity;
}


}//end of namespace myclass

#endif
