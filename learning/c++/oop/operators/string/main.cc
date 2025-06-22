#include "string.h"
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;

void test1();

void test1()
{
    String s1;
    String s2("hello");
    String s3(s2);

    cout << "----- test operator<< -----" << endl;
    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;
    cout << "s3 = " << s3 << endl;

    cout << endl;
    cout << "----- test operator= ------" << endl;
    s1 = s3;
    s2 = "world";
    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;
    /* cout << "s1.size() = " << s1.size() << endl; */
    /* cout << "s2.size() = " << s2.size() << endl; */
    /* s1 += s2; */
    /* cout << "s1 = " << s1 << endl; */

    cout << endl;
    cout << "------ test operator+= ------" << endl;
    s1 += s2;
    s1 += " welcome here";
    cout << "s1 = " << s1 << endl;

    cout << endl;
    cout << "----- test operator[] ------" << endl;
    cout << "s1[0] = " << s1[0] << endl;
    cout << "s2[3] = " << s2[3] << endl;
    cout << "s3[1] = " << s3[1] << endl;

    cout << endl;
    cout << "----- test c_str() ------" << endl;
    const char *str = s1.c_str();
    cout << "str = " << str << endl;

    cout << endl;
    cout << "----- test operator ==" << endl;
    s3 = s2;
    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;
    cout << "s3 = " << s3 << endl;
    cout << "s1 == s2 ? " << (s1 == s2) << endl;
    cout << "s1 != s2 ? " << (s1 != s2) << endl;
    cout << "s3 == s2 ? " << (s3 == s2) << endl;
    cout << "s3 != s2 ? " << (s3 != s2) << endl;
    

#if 0
    cout << endl;
    cout << "-----test operator<-----" << endl;
    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;
    cout << "s3 = " << s3 << endl;
    cout << "s1 < s2 ? " << (s1 < s2) << endl;
    cout << "s1 > s2 ? " << (s1 > s2) << endl;
    cout << endl;
    cout << "s1 <= s2 ? " << (s1 <= s2) << endl;
    cout << "s1 >= s2 ? " << (s1 >= s2) << endl;
    cout << "s3 <= s2 ? " << (s3 <= s2) << endl;
    cout << "s3 >= s2 ? " << (s3 >= s2) << endl;

    cout << endl;
    cout << "-----test operator>>-----" << endl;
    cin >> s3;
    cout << "s3 = " << s3 << endl;
#endif

    cout << endl;
    cout << "----- test operator+ -----" << endl;
    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;
    cout << "s3 = " << s3 << endl;
    cout << endl;
    cout << "s1 + s2 = " << s1 + s2 << endl;
    cout << "s3 + \"shit\" = " << s3 + "shit" << endl;
    cout << "\"good\" + s2 = " << "good" + s2 << endl;
    
}


int main()
{
    test1();
    return 0;
}

