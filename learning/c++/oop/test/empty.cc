#include <iostream>

using std::cout;
using std::endl;

class Empty
{
};

int main()
{
    cout << "sizof(Empty) = " << sizeof(Empty) << endl;

    Empty e1;
    Empty e2;
    Empty e3;

    cout << "&e1 = " << &e1 << endl;
    cout << "&e2 = " << &e2 << endl;
    cout << "&e3 = " << &e3 << endl;
    return 0;
}

