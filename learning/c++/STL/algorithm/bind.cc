#include <iostream>
#include <functional>

using std::cout;
using std::endl;
using std::bind;

int add(int a, int b, int c, int d)
{
    /* cout << "int add(int a, int b)" << endl; */
    return a + b + c + d;
}

void test()
{
    auto f = bind(add, 3, 4, 1, 3);
    cout << "f() = " << f() << endl;
}

class Test
{
public:
    int add(int x, int y) 
    {
        /* cout << "int Test::add(int, int)" << endl; */
        return x + y;
    }

    int data = 100;//c++11
};

void test_classFunc()
{
    Test tst;
    auto f = bind(&Test::add, &tst, 7, 8);
    std::function<int()> f1 = bind(&Test::add, &tst, 7, 7);
    cout << "f() = " << f() << endl;

    cout << endl;
    auto f2 = bind(&Test::add, &tst, 7, std::placeholders::_1);
    cout << "f2(22) = " << f2(22) << endl;

    cout << endl;
    std::function<int(int,int)> f3 = bind(&add, std::placeholders::_1, 3, std::placeholders::_2, 7);
    cout << "f3(6, 6) = " << f3(6, 6) << endl;

    cout << endl;
    std::function<int()> f5 = bind(&Test::data, &tst);
    cout << "f5(100) = " << f5() << endl;
}

int main()
{
    /* test(); */
    test_classFunc();
    return 0;
}

