#include <string.h>
#include <iostream>

using std::cout;
using std::endl;

class Student
{
public:
    Student(int id, const char *name);

    void display() const;

    void *operator new(size_t sz);
    void operator delete(void *ptr);

    void destory();
private:
    ~Student();

private:
    int _id;
    char *_name;
};

void Student::destory()
{
    delete this;
}

Student::~Student()
{
    cout << "~Student()" << endl;
    if (_name) {
        delete _name;
        _name = nullptr;
    }
}

void Student::display() const
{
    cout << "---id:" << _id;
    if (_name) {
        cout << "   name:" << _name;
    }
    cout << "---" << endl;
}

Student::Student(int id, const char *name)
: _id(id)
, _name(new char[strlen(name) + 1]())
{
    cout << "Student(int, const char*)" << endl;
    strcpy(_name, name);
}

void *Student::operator new(size_t sz)
{
    cout << "void *operator new(size_t)" << endl;
    void *ret = malloc(sz);
    return ret;
}

void Student::operator delete(void *ptr)
{
    cout << "void operator delete(void*)" << endl;
    free(ptr);
}

void test_heap();

int main() 
{
    test_heap();
}


void test_heap()
{
    Student *pstu = new Student(1, "wangye");

    cout << endl;
    pstu->display();
    cout << endl;

    pstu->destory();
}

