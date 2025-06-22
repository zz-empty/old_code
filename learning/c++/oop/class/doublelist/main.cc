#include "list.h"
#include <iostream>

using std::cout;
using std::endl;

void test_node();
void test_list();

int main()
{
    /* test_node(); */
    test_list();
    return 0;
}

void test_list()
{
    List l1;
    l1.display();

    cout << endl;
    cout << "------test List::push_front--------" << endl;
    int idx = 0;
    for (idx = 0; idx <= 50; idx += 5) {
        /* l1.push_front(idx); */
        l1.push_back(idx);
        /* cout << "now size is " << l1.getsize() << endl; */
    }
    l1.display();

#if 0
    l1.pop_front();
    l1.pop_front();
    l1.pop_front();
    l1.pop_back();
    l1.display();
    l1.pop_back();
    l1.display();
#endif


#if 1
    cout << endl;
    cout << "------test List::deleteNode--------" << endl;
    l1.deleteNode(1);
    /* l1.deleteNode(0); */
    l1.display();
    l1.deleteNode(8);
    /* l1.deleteNode(18); */
    l1.display();
    cout << endl;
#endif

#if 0
    cout << endl;
    cout << "--------test List::find-----------" << endl;
    l1.find(5);
    l1.find(44);
    cout << endl;

    cout << endl;
    cout << "--------test List::location-----------" << endl;
    l1.location(3);
    l1.location(30);

    cout << endl;
    cout << "------execute List::destory-------" << endl;
    cout << "List_size is " << l1.getsize() << endl;
    l1.destory();
#endif

    cout << endl;
    cout << "--------test List::insert-----------" << endl;
    l1.insert(1, 66);
    /* l1.insert(1, 99); */
    /* l1.insert(1, 100); */
    l1.display();

    cout << endl;
    cout << "--------test List::erase-----------" << endl;
    l1.erase(20);
    l1.erase(66);
    l1.erase(50);
    cout << "erase over~" << endl;
    l1.display();

    cout << endl;
    cout << "--------test List::destory---------" << endl;
    cout << "size = " << l1.getsize() << endl;
    l1.destory();
    cout << endl;
}

void test_node()
{
    Node node;

    Node n2(10);
    n2._pPre = &node;
    node._pNext = &n2;

    cout << endl;
    cout << "&node = " << &node << endl;
    cout << "_data = " << node._data << endl;
    cout << "_pPre = " << node._pPre << endl;
    cout << "_pNext = " << node._pNext << endl;

    cout << endl;
    cout << "&n2= " << &n2 << endl;
    cout << "_data = " << n2._data << endl;
    cout << "_pPre = " << n2._pPre << endl;
    cout << "_pNext = " << n2._pNext << endl;


    cout << endl;
    Node n3 = n2;

    cout << "sizeof(n3) = " << sizeof(n3) << endl;
    cout << "&n3= " << &n3 << endl;
    cout << "_data = " << n3._data << endl;
    cout << "_pPre = " << n3._pPre << endl;
    cout << "_pNext = " << n3._pNext << endl;

    cout << endl;
    n3 = node;
    cout << "&n3= " << &n3 << endl;
    cout << "_data = " << n3._data << endl;
    cout << "_pPre = " << n3._pPre << endl;
    cout << "_pNext = " << n3._pNext << endl;
}
