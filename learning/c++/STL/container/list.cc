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

void print(list<int> num)
{
    for (size_t idx = 0; idx != num.size(); ++idx) {
        /* cout << num[idx] << " "; */
    }
    cout << endl;
}

void print_iterator(list<int> num)
{
    /* list<int>::iterator it = num.begin(); */
    auto it = num.begin();
    for (; it != num.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
}

void print_auto(list<int> num)
{
    for (auto &elem : num) {
        cout << elem << " ";
    }
    cout << endl;
}

void test1()
{
    list<int> num;
    list<int> num1(10, 9);

    print(num1);
}

void test2()
{
    int arr[10] = {1, 3, 2, 5, 4,
                6, 8, 9, 1};

    list<int> num(arr, arr + 10);
    /* print(num); */
    print_iterator(num);
}

void test3()
{
    list<int> num = { 3, 2, 2, 4, 9, 5, 8, 1 };
    print_auto(num);
}

int main()
{
    test3();
    return 0;
}

