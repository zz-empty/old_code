#include "HeapSort.hpp"
#include <iostream>

using std::cout;
using std::endl;

using namespace mysort;

void test0()
{
    int arr[9] = { 3, 4, 2, 9, 5, 7, 8, 1};

    /* HeapSort<int, std::less<int>> result(arr, 9, std::less<int>()); */
    HeapSort<int, std::greater<int>> result(arr, 9, std::greater<int>());
    result.print();
}

int main()
{
    test0();
    return 0;
}

