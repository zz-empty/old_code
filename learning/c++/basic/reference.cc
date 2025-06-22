#include <iostream>

using std::cout;
using std::endl;

int main()
{
    int num1 = 100;
    int &ref = num1;

    cout << "num1 = " << num1 << endl;
    cout << "ref = " << ref << endl;
    cout << "sizeof(ref) = " << sizeof(ref) << endl;

    return 0;
}

