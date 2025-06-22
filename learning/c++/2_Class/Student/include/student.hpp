#ifndef __STUDENT_HPP
#define __STUDENT_HPP

#include <string.h>
#include <iostream>

namespace myclass
{

using std::cout;
using std::endl;
using std::ostream;

class Student
{
private:
    ~Student()
    {
        if (_name) {
            delete [] _name;
            _name = nullptr;
        }
    }

public:
    Student()
    :_id(0)
    ,_name(nullptr)
    ,_age(0)
    {}

    Student(int id, const char * name, int age)
    :_id(id)
    ,_name(new char[strlen(name) + 1]())
    ,_age(age)
    {
        strcpy(_name, name);
    }

    Student(const Student &rhs);
    Student & operator=(const Student &rhs);

    void display() const;
    int id() const { return _id; }
    char * name() const { return _name; }
    int age() const { return _age; }
    void setId(int id) { _id = id; }
    void setAge(int age) { _age = age; }
    void setName(const char *name);

    friend ostream &operator<<(ostream &os, const Student &rhs);

private:
    /* void *operator new(size_t sz); */
    /* void operator delete(void *pstr); */

private:
    int _id;
    char* _name;
    int _age;
};



}//end of namespace myclass

#endif
