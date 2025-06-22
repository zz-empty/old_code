#ifndef __STUDENT_H__
#define __STUDENT_H__


class Student
{
public:
    Student(int id, const char *name, int age);
    ~Student();
    Student(const Student &rhs);
    Student &operator=(const Student &rhs);

    void display();
    int getID();
    bool setID(int id);
    bool setName(const char *name);
    bool setAge(int age);
private:
    int _id;
    char *_name; //指向堆空间
    int _age;
};

#endif
