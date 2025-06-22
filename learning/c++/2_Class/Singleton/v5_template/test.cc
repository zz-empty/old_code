#include "Singleton.hpp"
#include "Point.hpp"
#include "Computer.hpp"

#include <iostream>
#include <memory>

using std::cout;
using std::endl;


void test0()
{
    using namespace wd;

    Computer* pc1 = Singleton<Computer>::getInstance("lenovo", 3000);
    Computer* pc2 = Singleton<Computer>::getInstance("lenovo", 3000);
    

    cout << "pc1 = " << pc1 << endl;
    cout << "pc2 = " << pc2 << endl;

    cout << endl;
    pc1->print();
    pc2->print();

}

void test1()
{
    using namespace wd;

    Point* pc1 = Singleton<Point>::getInstance(5, 5);
    Point* pc2 = Singleton<Point>::getInstance(5, 5);
    

    cout << "pc1 = " << pc1 << endl;
    cout << "pc2 = " << pc2 << endl;

    cout << endl;
    pc1->print();
    pc2->print();

}

int main()
{
    test1();
    return 0;
}

