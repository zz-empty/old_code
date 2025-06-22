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

template<typename Container>
void display(const Container &c)
{
    for (auto &elem : c) {
        cout << elem << " ";
    }
    cout << endl;
}

std::ostream &operator<<(std::ostream &os, const vector<int> &rhs)
{
    display(rhs);
    return os;
}
std::ostream &operator<<(std::ostream &os, const deque<int> &rhs)
{
    display(rhs);
    return os;
}
std::ostream &operator<<(std::ostream &os, const list<int> &rhs)
{
    display(rhs);
    return os;
}



void test1()
{
    vector<int> num = {3, 12, 41, 8, 3, 2, 6, 9};
    display(num);

    cout << endl;
    cout << "-------insert elem to vector-------" << endl;
    num.push_back(33);
    num.push_back(99);
    display(num);
    num.pop_back();
    display(num);

}

void test_erase()
{
    vector<int> number;
    number.push_back(1);
    number.push_back(3);
    number.push_back(6);
    number.push_back(6);
    number.push_back(7);
    number.push_back(6);
    number.push_back(9);
    number.push_back(8);
    display(number);

    cout << endl;
    cout << "--------test erase--------" << endl;
    auto it = number.begin();
    for (; it != number.end();) {
        if (*it == 6) {
            number.erase(it);
        }
        else {
            ++it;
        }
    }

    display(number);
}

void test_capacity()
{
    vector<int> number = {3, 2, 1, 4, 5};
    display(number);
    cout << "number.size = " << number.size() << endl;
    cout << "number.capacity = "  << number.capacity() << endl;

    cout << endl;
    number.push_back(10);
    cout << "number.size = " << number.size() << endl;
    cout << "number.capacity = "  << number.capacity() << endl;
}

void test_init()
{
    //1 空
    vector<int> vec1;
    deque<int> deq1;
    list<int> lis1;

    //2 多个相同元素
    vector<int> vec2(10, 3);
    deque<int> deq2(6, 3);
    list<int> lis2(9, 3);
    cout << "vec2 = " << vec2 << endl;
    cout << "deq2 = " << deq2 << endl;
    cout << "lis2 = " << lis2 << endl;
    cout << endl;

    //3 大括号
    vector<int> vec3 = {3, 4, 5, 8, 9};
    deque<int> deq3 = {5, 3, 2, 8, 9};
    list<int> lis3 = {5, 3, 2, 3, 2};
    cout << "vec3 = " << vec3 << endl;
    cout << "deq3 = " << deq3 << endl;
    cout << "lis3 = " << lis3 << endl;
    cout << endl;

    //4 迭代器范围
    int arr[] = {3, 4, 2, 8};
    vector<int> vec4(arr, arr + 4);
    deque<int> deq4(arr, arr + 4);
    list<int> lis4(arr, arr + 4);
    cout << "vec3 = " << vec3 << endl;
    cout << "deq3 = " << deq3 << endl;
    cout << "lis3 = " << lis3 << endl;
    cout << endl;
}

int main()
{
    /* test1(); */
    /* test_erase(); */
    /* test_capacity(); */
    test_init();
    return 0;
}

