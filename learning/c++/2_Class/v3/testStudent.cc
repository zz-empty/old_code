#include "student.hpp"
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;


#if 0
void test0()
{
    using namespace myclass;

    Student s1(111, "zhangsan", 19);
    s1.display();

    cout << endl;
    Student s2;
    s2.display();

    cout << endl;
    cout << "-----------test Student::operator=-----------" << endl;
    s2 = s1;
    s2.display();

    cout << endl;
    cout << "-----------test Student(const Student &)-----------" << endl;
    Student s3 = s2;
    s3.display();

    cout << endl;
    s3.setId(003);
    s3.setName("king");
    s3.setAge(55);
    s3.display();

    cout << endl;
    cout << "s1 : " << s1 << endl;
    cout << "s2 : " << s2 << endl;
    cout << "s3 : " << s3 << endl;

}
#endif

void test1()
{
    using namespace myclass;
    //only_stack
    /* Student stu1(212, "king", 11); */
    /* stu1.display(); */

    //only_heap
    Student *pstu = new Student(111, "queue", 22);
    pstu->display();

}

int main()
{
    test1();
#ifdef DEBUG
    printf("you are handsome!!!\n");
#endif
    return 0;
}

