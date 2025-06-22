#include "student.hpp"

#include <iostream>

using std::cout;
using std::endl;

namespace myclass
{

void Student::display() const
{
    if (_id) {
        cout << "Student info : id = " << _id;
        if (_name) {
            cout << ", name = " << _name;

        }
        cout << ", age = " << _age << endl;
    }
    else {
        cout << "------no stu_info-------" << endl;
    }
}

Student::Student(const Student &rhs)
{
    _id = rhs._id;
    _name = new char[strlen(rhs._name) + 1]();
    strcpy(_name, rhs._name);
    _age = rhs._age;
}

Student & Student::operator=(const Student &rhs)
{
    if (this != &rhs) {
        if (_name) {
            delete [] _name;
            _name = nullptr;
        }

        _id = rhs._id;
        _name = new char[strlen(rhs._name) + 1]();
        strcpy(_name, rhs._name);
        _age = rhs._age;
    }
    return *this;
}

void Student::setName(const char *name)
{
    if (_name) {
        delete [] _name;
        _name = nullptr;
    }

    _name = new char[strlen(name) + 1]();
    strcpy(_name, name);
}

ostream &operator<<(ostream &os, const Student &rhs)
{
    os << "id = " << rhs._id  
       << ", name = " << rhs._name
       << ", age = " << rhs._age << endl;
    return os;
}

} //end of namespace myclass
