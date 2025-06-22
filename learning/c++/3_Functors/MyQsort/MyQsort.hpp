#ifndef __MYQSORT_HPP__
#define __MYQSORT_HPP__

#include <iostream>
#include <vector>

namespace mysort
{

template<typename T, typename Compare = std::less<T>>
class MyQsort
{
public:
    MyQsort(T *arr, size_t size, Compare com);//录入元素，并排序

    void quick(int left, int right, Compare &com);//排序操作
    int partition(int left, int right, Compare &com);//对数组划分
    void print();
private:
    std::vector<T> _vec;
};

template<typename T, typename Compare>
MyQsort<T, Compare>::MyQsort(T *arr, size_t size, Compare com)
{
    size_t idx = 0;
    for (idx = 0; idx < size; ++idx) {
        _vec.push_back(arr[idx]);
    }

    quick(0, _vec.size() - 1, com);
}

template<typename T, typename Compare>
void MyQsort<T, Compare>::quick(int left, int right, Compare &com)
{
    if (left < right) {
        int pos = partition(left, right, com);
        quick(left, pos - 1, com);
        quick(pos + 1, right, com);
    }
}

template<typename T, typename Compare>
int MyQsort<T, Compare>::partition(int left, int right, Compare &com)
{
    T pivot = _vec[right];
    int i = left;
    int j = left;
    for (; j < right; ++j) {
        if (com(_vec[j], pivot)) {
            std::swap(_vec[i], _vec[j]);
            ++i;
        }
    }
    std::swap(_vec[i], _vec[right]);
    return i;
}

template<typename T, typename Compare>
void MyQsort<T, Compare>::print()
{
    for (auto &elem : _vec) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}
}// end of namespace mysort

#endif
