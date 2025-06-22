#include "list.hpp"
#include <iostream>

using std::cout;
using std::endl;

void test0()
{
    using namespace wd;

    List l1; 
    cout << "l1.size = " << l1.size() << endl;

    cout << endl;
    cout << "--------test push-----------" << endl;
    l1.push_back(2);
    l1.push_back(4);
    l1.push_back(3);
    l1.push_back(5);
    l1.push_back(6);
    l1.push_front(4);
    l1.push_front(9);
    l1.push_front(0);
    l1.push_front(1);
    l1.push_front(1);
    l1.display();
    cout << "l1.size = " << l1.size() << endl;

    cout << endl;
    cout << "--------test pop-------------" << endl;
    l1.pop_back();
    l1.pop_back();
    l1.pop_back();
    l1.display();
    cout << "l1.size = " << l1.size() << endl;

    cout << endl;
    l1.pop_front();
    l1.pop_front();
    l1.pop_front();
    l1.display();
    cout << "l1.size = " << l1.size() << endl;
    
    cout << endl;
    cout << "--------test find----------" << endl;
    if (l1.find(2)) {
        cout << "find!" << endl;
    }
    else {
        cout << "not find!" << endl;
    }

    cout << endl;
    cout << "--------test erase----------" << endl;
    if (l1.erase(9)) {
        cout << "delete succeed" << endl;
        l1.display();
        cout << "l1.size = " << l1.size() << endl;
    }
    else {
        cout << "delete fail" << endl;
        l1.display();
        cout << "l1.size = " << l1.size() << endl;
    }

    cout << endl;
    cout << "--------test insert----------" << endl;
    l1.insert(1, 99);
    l1.display();
    cout << "l1.size = " << l1.size() << endl;

    cout << endl;
    l1.insert(5, 88);
    l1.display();
    cout << "l1.size = " << l1.size() << endl;
    
}

int main()
{
    test0();
    return 0;
}

