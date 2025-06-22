#include "student.h"
#include <string.h>
#include <iostream>

using std::cout;
using std::endl;


Student::Student(int id, const char *name, int age)
:_id(id)
,_name(new char[strlen(name) + 1]())
,_age(age)
{
    cout << "Student(int, const char*, int)" << endl;
    strcpy(_name, name);
}

Student::~Student()
{
    cout << "~Student()" << endl;
    if (_name) {
        delete [] _name;
        _name = nullptr;
    }
}

Student::Student(const Student &rhs)
{
    cout << "Student(const Student &)" << endl;
    _id = rhs._id;
    _name = new char[strlen(rhs._name) + 1]();
    strcpy(_name, rhs._name);
    _age = rhs._age;
}

Student &Student::operator=(const Student &rhs)
{
    cout << "Student &operator=(const Student &)" << endl;
    if (this != &rhs) {
        delete [] _name;
        _name = nullptr;

        _name = new char[strlen(rhs._name) + 1]();
        strcpy(_name, rhs._name);
    }
    return *this;
}

void Student::display()
{
    cout << "---id = " << _id << ", "
         << "name = " << _name << ", "
         << "age = " << _age << "---" << endl;
}

int Student::getID()
{
    return _id;
}

bool Student::setID(int id)
{
    if (id < 1 || id > 100) {
        cout << "stu_id is illegal" << endl;
        return false;
    }
    _id = id;
    return true;
}

bool Student::setName(const char *name)
{
    if (strlen(name) > strlen(_name)) {
        delete [] _name;
        _name = nullptr;
        _name = new char[strlen(name) + 1]();
    }
    strcpy(_name, name);
    return true;
}

bool Student::setAge(int age)
{
    if (5 > age || 50 < age) {
        cout << "stu_age is illegal!" << endl;
        return false;
    }
    _age = age;
    return true;
}
