#include "Person.hpp"
#include "Employee.hpp"
#include <iostream>

using std::cout;
using std::endl;

void test0()
{
    using namespace wd;
    Person one("qin", 33);
    one.display();
}

void test1()
{
    using namespace wd;

    Employee e1("tom", 20, "manage", 6000);
    Employee e2("lili", 20, "produce", 8000);
    Employee e3("john", 20, "test", 4000);

    e1.display();
    e2.display();
    e3.display();

    cout << endl;
    double ave = (e1.getSalary() + e2.getSalary() + e3.getSalary()) / 3;
    cout << "they average_salary is " << ave << endl;
}

int main()
{
    test1();
    return 0;
}

