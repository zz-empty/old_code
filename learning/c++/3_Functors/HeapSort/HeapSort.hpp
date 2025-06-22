#ifndef __HEAPSORT_HPP__
#define __HEAPSORT_HPP__

#include <iostream>
#include <vector>

using std::cout;
using std::endl;

namespace mysort
{

template <typename T, typename Compare = std::less<T>>
class HeapSort
{
public:
    HeapSort(T *arr, size_t size, Compare com);
    void heapAdjust(size_t ,size_t ,Compare &com);
    void sort(Compare &com);
    void print();
private:
    std::vector<T> _vec;
};

template <typename T, typename Compare>
HeapSort<T, Compare>::HeapSort(T *arr, size_t size, Compare com)
{
    for (size_t i = 0; i < size; ++i) {
        _vec.push_back(arr[i]);
    }

    //从最后一个父节点开始，建立大根堆
    for (int i = _vec.size() / 2 - 1; i >= 0; --i) {
        heapAdjust(i, size, com);
    }
    //交换堆顶和末尾
    std::swap(_vec[0], _vec[size - 1]);
    //减小堆的规模，重建堆，直到堆的规模为2时
    for (int i = _vec.size() - 1; i > 1; --i) {
        heapAdjust(0, i, com);
        std::swap(_vec[0], _vec[i - 1]);
    }
}

template <typename T, typename Compare>
void HeapSort<T, Compare>::heapAdjust(size_t pos, size_t len, Compare &com)
{
    size_t dad = pos;
    size_t left = 2 * dad + 1;//左孩子

    while (left < len) {
        //如果右孩子存在，且大于左孩子，则更新孩子
        if (left + 1 < len && com(_vec[left], _vec[left + 1])) {
            left = left + 1;
        }

        //如果孩子大于父节点，更换位置
        if (com(_vec[dad], _vec[left])) {
            std::swap(_vec[left], _vec[dad]);
            //向下循环
            dad = left;
            left = 2 * dad + 1;
        }
        else {
            break;
        }
    }
}

template <typename T, typename Compare>
void HeapSort<T, Compare>::sort(Compare &com)
{
    HeapSort(0, _vec.size(), com);
}

template <typename T, typename Compare>
void HeapSort<T, Compare>::print()
{
    for (auto &elem : _vec) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

}// end of namespace mysort

#endif
