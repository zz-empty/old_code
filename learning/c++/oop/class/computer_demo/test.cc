#include "computer.h"
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

/* Computer g_pc("xiaomi", 5500);//全局对象 */

void test3()
{
    /* g_pc.print(); */

    /* char brand[20] = {0}; */
    /* float  price; */
    /* cout << "please input pc brand and price: "; */
    /* cin >> brand >> price; */


    /* Computer pc(brand, price); */
    /* cout << endl; */
    Computer pc("lenovo", 5000);//栈对象
    pc.print();
    cout << endl;

    /* Computer *h_pc = new Computer("apple", 8000);//堆对象 */
    /* h_pc->print(); */
    /* delete h_pc; */

    //拷贝构造函数
    Computer pc2 = pc;
    pc2.setBrand("mac");
    pc2.print();

}

void test4()
{
    //test operator=
    Computer pc("lenovo", 5000);//栈对象
    pc.print();
    cout << endl;

    Computer pc2 = pc;
    pc2.setBrand("MacBook air");
    pc2.setPrice(6666);
    pc2.print();

    cout << endl;
    cout << "执行 pc2 = pc" << endl;
    pc2 = pc;
    pc.print();
    pc2.print();
}

void test5()
{
    Computer pc("lenovo", 5000);
    
    cout << "111" << endl;
    pc.destroy();
    cout << "222" << endl;
}
