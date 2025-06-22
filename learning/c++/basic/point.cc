#include <iostream>

using std::cout;
using std::endl;

int main()
{
    const int number = 2;
    int number2 = 3;

    const int * pi = &number;
    /* *pi = 3; */
    pi = &number2;
    return 0;
}

