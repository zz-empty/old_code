#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int add(int x, int y, int z = 10)
{
    return x + y + z;
}

int main()
{
    int x;
    int y;
    int z;

    cout << "please input three number: ";
    cin >> x >> y >> z;
    
    cout << "add(x,y,z) = " << add(x, y, z) << endl;
    cout << "add(x,y) = " << add(x, y) << endl;
    return 0;
}

