#include <string.h>
#include "string.h"
#include <iostream>

using std::cout;
using std::endl;

void test1();
void test2();

int main() 
{
    test2();
    return 0;
}

void test1()
{
    String s1;
    s1.print();

    s1 = "hello, world";
    s1.print();

    cout << endl;
    String s2 = s1;
    s2.print();
}

void test2()
{
    cout << "----constructor with nothind----" << endl;
    String str1;
	str1.print();
    cout << endl;

    cout << "----constructor with para----" << endl;
	String str2 = "Hello,world";
	String str3("wangdao");
	
	str2.print();		
	str3.print();	
    cout << endl;
	
    cout << "----copy constructor----" << endl;
	String str4 = str3;
	str4.print();
    cout << endl;
	
    cout << "----copy assignment operator----" << endl;
	str4 = str2;
	str4.print();
    cout << endl;
}
