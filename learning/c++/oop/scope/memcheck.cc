#include <iostream>

using std::cout;
using std::endl;

int main()
{
    int *pInt = new int(10);
    delete pInt;
    return 0;
}

