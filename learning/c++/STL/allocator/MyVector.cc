#include <iostream>
#include <functional>
#include <memory>
#include <algorithm>

using std::cout;
using std::endl;

template<typename T>
class Vector
{
public:
    using iterator = T *;
public:
    Vector();
    ~Vector();

    void push_back(const T &value);
    void pop_back();
    int size() const;
    int capacity() const;
    iterator begin();
    iterator end();
private:
    void reallocate();//重新申请空间
private:
    static std::allocator<T> _alloc;

    T *_start;
    T *_finish;
    T *_end_of_storage;
};

template<typename T>
T *Vector<T>::begin()
{
    return _start;
}
template<typename T>
T *Vector<T>::end()
{
    return _finish;
}

template<typename T>
std::allocator<T> Vector<T>::_alloc;

template<typename T>
Vector<T>::Vector()
:_start(nullptr)
,_finish(nullptr)
,_end_of_storage(nullptr)
{

}

template<typename T>
Vector<T>::~Vector()
{
    if (_start) {
        //销毁对象
        while (_finish != _start) {
            _alloc.destroy(--_finish);
        }
        //销毁空间
        _alloc.deallocate(_start, capacity());
    }

}

template<typename T>
void Vector<T>::push_back(const T &value)
{
    if (size() == capacity()) {
        reallocate();
    }
    if (size() < capacity()) {
        _alloc.construct(_finish++, value);
    }
}

template<typename T>
void Vector<T>::pop_back()
{
    if (size() > 0) {
        _alloc.destroy(--_finish);
    }
}
template<typename T>
int Vector<T>::size() const
{
    return _finish - _start;
}
template<typename T>
int Vector<T>::capacity() const
{
    return _end_of_storage - _start;
}

template<typename T>
void Vector<T>::reallocate() 
{
    int oldCapacity = capacity();
    int newCapacity = oldCapacity ? 2 * oldCapacity : 1;
    
    //申请新空间
    T * newStart = _alloc.allocate(newCapacity);
    //拷贝数据
    if (_start) {
        std::uninitialized_copy(_start, _finish, newStart);
        //销毁旧空间对象
        while (_finish != _start) {
            _alloc.destroy(--_finish);
        }
        //销毁旧空间
        _alloc.deallocate(_start, oldCapacity);
    }

    //重置数据成员，指向新的空间
    _start = newStart;
    _finish = _start + oldCapacity;
    _end_of_storage = _start + newCapacity;
}

void printCapcity(const Vector<int> &vec)
{
    cout << "vec.size() = " << vec.size() << endl
         << "vec.capacity() = " << vec.capacity() << endl;
}

void test()
{
    Vector<int> num;
    printCapcity(num);

    cout << endl;
    num.push_back(1);
    printCapcity(num);
    cout << endl;
    num.push_back(1);
    printCapcity(num);
    cout << endl;
    num.push_back(3);
    printCapcity(num);
    cout << endl;
    num.push_back(2);
    printCapcity(num);
    
    cout << endl;
    num.push_back(5);
    printCapcity(num);
    
    cout << endl;
    num.push_back(4);
    printCapcity(num);
    
    for (auto &elem : num) {
        cout << elem << " ";
    }
    cout << endl;
}

int main()
{
    test();
    return 0;
}

