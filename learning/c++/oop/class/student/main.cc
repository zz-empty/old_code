#include "student.h"
#include <iostream>

using std::cout;
using std::endl;

int main()
{
    Student stu(1, "zhang", 19);
    stu.display();

    cout << endl;
    cout << "-------modify stu_info-------" << endl;
    stu.setID(33);
    stu.setName("qin");
    stu.setAge(54);
    stu.display();
    cout << endl;
    return 0;
}

