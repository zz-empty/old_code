#include <iostream>

using std::cout;
using std::endl;

int main()
{
    int *pi = new int(10);
    cout << "pi = " << *pi << endl;

    int *pArr = new int[20]();

    delete [] pArr;

    delete pi;
    return 0;
}

