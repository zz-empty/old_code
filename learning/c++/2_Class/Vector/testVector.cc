#include "MyVector.hpp"
#include <iostream>

using std::cout;
using std::endl;
using namespace myclass;

void print(const MyVector<int> &vec)
{
    cout << "vec.size = " << vec.size() << "   ";
    cout << "vec.capacity = " << vec.capacity() << endl;
    for (auto &elem : vec) {
        cout << elem << " ";
    }
    cout << endl;
}

void test0()
{
    MyVector<int> vec;
    print(vec);

    cout << endl;
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);
    print(vec);

    cout << endl;
    vec.pop_back();
    vec.pop_back();
    print(vec);

    cout << endl;
    vec.push_back(9);
    vec.push_back(8);
    vec.push_back(7);
    vec.push_back(6);
    vec.push_back(5);
    print(vec);
}

int main()
{
    test0();
    return 0;
}

