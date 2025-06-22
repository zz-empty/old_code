#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <list>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::deque;
using std::list;

void print(deque<int> num)
{
    for (size_t idx = 0; idx != num.size(); ++idx) {
        cout << num[idx] << " ";
    }
    cout << endl;
}

void print_iterator(deque<int> num)
{
    /* deque<int>::iterator it = num.begin(); */
    auto it = num.begin();
    for (; it != num.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
}

void print_auto(deque<int> num)
{
    for (auto &elem : num) {
        cout << elem << " ";
    }
    cout << endl;
}

void test1()
{
    deque<int> num;
    deque<int> num1(10, 9);

    print(num1);
}

void test2()
{
    int arr[10] = {1, 3, 2, 5, 4,
                6, 8, 9, 1};

    deque<int> num(arr, arr + 10);
    /* print(num); */
    print_iterator(num);
}

void test3()
{
    deque<int> num = { 3, 2, 2, 4, 9, 5, 8, 1 };
    print_auto(num);
}

int main()
{
    test3();
    return 0;
}

