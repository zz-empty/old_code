#include <iostream>

using std::cout;
using std::endl;

class Base
{
public:
    Base(int num) :_num(num) {}

    friend std::ostream & operator<<(std::ostream &os, const Base &rhs); 
    friend Base operator+(const Base &lhs, const Base &rhs);
    friend Base operator-(const Base &lhs, const Base &rhs);
    friend bool operator==(const Base &lhs, const Base &rhs);
private:
    int _num;
};

bool operator==(const Base &lhs, const Base &rhs)
{
    return lhs._num == rhs._num;
}

std::ostream & operator<<(std::ostream &os, const Base &rhs)
{
    cout << rhs._num;
    return os;
}

Base operator+(const Base &lhs, const Base &rhs)
{
    return Base(lhs._num + rhs._num);
}
Base operator-(const Base &lhs, const Base &rhs)
{
    return Base(lhs._num - rhs._num);
}


int main()
{
    int a = 3;
    int b = 4;

    Base x(a);
    Base y(b);

    cout << "x = " << x << endl;
    cout << "y = " << y << endl;

    cout << endl;
    cout << (x+y == b - a) << endl;
    return 0;
}

