#include <string.h>
#include <iostream>

using std::cout;
using std::endl;
using std::string;

void test()
{
    char str1[] = "hello";
    char str2[] = "world";
    str1[0] = 'H';

    size_t len1 = sizeof(str1);
    size_t len2 = sizeof str2;

    size_t len = len1 + len2 - 1;

    char *ptr = static_cast<char*>(malloc(len));
    memset(ptr, 0, len);
    strcat(ptr, str1);
    strcat(ptr, str2);
    cout << "ptr = " << ptr << endl;
    cout << "sizeof(ptr) = " << sizeof(ptr) << endl;
    cout << "strlen(ptr) = " << strlen(ptr) << endl;

    free(ptr);
    ptr = NULL;
}

void test2()
{
    string s1 = "hello";
    string s2 = "world";
    string s3 = s1 + s2;

    cout << "s1 = " << s1 << endl
         << "s2 = " << s2 << endl
         << "s3 = " << s3 << endl;

    cout << endl;
    const char *pstr = s3.c_str();
    cout << "pstr = " << pstr << endl;

    cout << endl;
    size_t len1 = sizeof(s3);
    size_t len2 = s3.size();
    size_t len3 = s3.length();
    /* cout << "len1 = " << len1 << endl */
    cout << "len2 = " << len2 << endl;
    cout << "len3 = " << len3 << endl;

    cout << endl;
    size_t idx = 0;
    for (idx = 0; s3[idx]; ++idx) {
        cout << s3[idx] << "   ";
    }
    cout << endl;

    cout << endl;
    string s4 = s3 + " pretty";
    cout << "s4 = " << s4 << endl;

    cout << endl;
    string s5 = s4 + 'A';
    cout << "s5 = " << s5 << endl;
    
    s5.append(" welcome");
    cout << "s5 = " << s5 << endl;
}

int main()
{
    test2();
    return 0;
}

