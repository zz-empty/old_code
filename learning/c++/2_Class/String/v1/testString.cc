#include "string.hpp"
#include <iostream>

using std::cout;
using std::endl;

using namespace wd;

void test0()
{

    String s1;
    String s2("hello");
    String s3(s2);

    s1 = s2;
    s1 = "world";

    s2 += s1;
    s3 += "world";

    cout << "s1[0] = " << s1[0] << endl;
    s2[2] = 'O';

    cout << "s1.size() = " << s1.size() << endl;
    cout << "s2.c_str() = " << s2.c_str() << endl;

    cout << endl;
    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;
    cout << "s3 = " << s3 << endl;
    
    cout << endl;
    cout << "put a string: ";
    std::cin >> s1;
    cout << "s1 = " << s1 << endl;

    cout << endl;
    cout << "s1 + s2 = " << s1 + s2 << endl;
}

int main()
{
    test0();
    return 0;
}

