#include "dict.h"
#include <time.h>
#include <iostream>
#include <algorithm>

using std::cout;
using std::endl;

void test();

int main()
{
    test();
    return 0;
}

void test()
{
    Dictionary dict(8000);

    cout << "start reading..." << endl; 
    time_t beg = time(NULL);

    dict.read("The_Holy_Bible.txt");
    time_t end = time(NULL);

    cout << "cost " << (end - beg) << "s" << endl;
    cout << "finish reading" << endl; 

    /* dict.display(); */

    //sort vector
    dict.sort();
    /* dict.cnt_sort(); */
    /* dict.display(); */

    //to ofstream
    dict.store("words.txt");
}

