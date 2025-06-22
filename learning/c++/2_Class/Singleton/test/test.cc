# include <iostream>
# include "Computer.hpp"
# include "Point.hpp"
# include "Singleton.hpp"

using namespace std;


template<typename T>
T* Singleton<T>::_pInstance = nullptr;//懒汉模式


void test()
{
    Computer *pc1 = Singleton<Computer>::getInstance("Xiaomi", 6666);
    Computer *pc2 = Singleton<Computer>::getInstance("Xiaomi", 6666);
    printf("pc1 = %p\n", pc1);
    printf("pc2 = %p\n", pc2);
    pc1->print();
    pc2->print();
}

void test2()
{
    Point *pt3 = Singleton<Point>::getInstance(1, 2);
    Point *pt4 = Singleton<Point>::getInstance(1, 2);
    printf("pt3 = %p\n", pt3);
    printf("pt4 = %p\n", pt4);
    pt3->print();
    pt4->print();
}

int main()
{
    test();
    /* test2(); */
}
