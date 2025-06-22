#include "string.hpp"
#include <iostream>

using std::cout;
using std::endl;

using namespace wd;

void test()
{
    String s1("hello");
    cout << "s1 = " << s1 << endl;
    printf("s1's address: %p\n", s1.c_str());
    printf("s1's RefCount: %d\n", s1.getRefCount());

    cout << endl;
    cout << "-----String s2 = s1----------" << endl;
    String s2 = s1;
    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;
    printf("s1's address: %p\n", s1.c_str());
    printf("s2's address: %p\n", s2.c_str());
    printf("s1's RefCount: %d\n", s1.getRefCount());
    printf("s2's RefCount: %d\n", s2.getRefCount());

    cout << endl;
    String s3("world");
    cout << "s3 = " << s3 << endl;
    printf("s3's address: %p\n", s3.c_str());
    printf("s3's RefCount: %d\n", s3.getRefCount());

    cout << endl << "执行s3 = s1" << endl;
    s3 = s1;
    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;
    cout << "s3 = " << s3 << endl;
    printf("s1's address: %p\n", s1.c_str());
    printf("s2's address: %p\n", s2.c_str());
    printf("s3's address: %p\n", s3.c_str());
    printf("s1's RefCount: %d\n", s1.getRefCount());
    printf("s2's RefCount: %d\n", s2.getRefCount());
    printf("s3's RefCount: %d\n", s3.getRefCount());

    cout << endl << "执行s3[0] = 'H'" << endl;
    s3[0] = 'H';
    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;
    cout << "s3 = " << s3 << endl;
    printf("s1's address: %p\n", s1.c_str());
    printf("s2's address: %p\n", s2.c_str());
    printf("s3's address: %p\n", s3.c_str());
    printf("s1's RefCount: %d\n", s1.getRefCount());
    printf("s2's RefCount: %d\n", s2.getRefCount());
    printf("s3's RefCount: %d\n", s3.getRefCount());

    cout << endl << "对s1[0]读操作时" << endl;
    cout << "s1[0] = " << s1[0] << endl;
    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;
    cout << "s3 = " << s3 << endl;
    printf("s1's address: %p\n", s1.c_str());
    printf("s2's address: %p\n", s2.c_str());
    printf("s3's address: %p\n", s3.c_str());
    printf("s1's RefCount: %d\n", s1.getRefCount());
    printf("s2's RefCount: %d\n", s2.getRefCount());
    printf("s3's RefCount: %d\n", s3.getRefCount());
}


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
    test();
    /* test0(); */
    return 0;
}

