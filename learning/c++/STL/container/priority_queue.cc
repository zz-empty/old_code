#include <math.h>
#include <iostream>
#include <queue>
#include <vector>

using std::cout;
using std::endl;
using std::priority_queue;
using std::vector;

void test()
{
    vector<int> vec = { 3, 2, 3, 9, 8, 4, 8, 9, 5 };
    priority_queue<int> number;

    for (size_t offset = 0; offset < vec.size(); ++offset) {
        number.push(vec[offset]);
        cout << "优先级最高的元素: " << number.top() << endl;
    }

    while (!number.empty()) {
        cout << number.top() << " ";
        number.pop();
    }
    cout << endl;
}

class Point
{
public:
    Point(int ix = 0, int iy = 0)
    :_ix(ix)
    ,_iy(iy)
    {

    }

    int getX() const
    {
        return _ix;
    }
    int getY() const
    {
        return _iy;
    }

    double getDistance() const
    {
        return hypot(_ix, _iy);
    }

    friend std::ostream &operator<<(std::ostream &os, const Point &rhs);
private:
    int _ix;
    int _iy;
};

std::ostream &operator<<(std::ostream &os, const Point &rhs)
{
    os << "(" << rhs.getX() << "," << rhs.getY() << ")" ;
    return os;
}

bool operator<(const Point &lhs, const Point &rhs)
{
    /* return lhs.getX() < rhs.getX(); */
    if (lhs.getDistance() < rhs.getDistance()) {
        return true;
    }
    else if (lhs.getDistance() == rhs.getDistance()) {
        if (lhs.getX() < rhs.getX()) {
            return true;
        }
        else if (lhs.getX() == rhs.getX()) {
            if (lhs.getY() < rhs.getY()) {
                return true;
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool operator>(const Point &lhs, const Point &rhs)
{
    if (lhs.getDistance() > rhs.getDistance()) {
        return true;
    }
    else if (lhs.getDistance() == rhs.getDistance()) {
        if (lhs.getX() < rhs.getX()) {
            return true;
        }
        else if (lhs.getX() == rhs.getX()) {
            if (lhs.getY() > rhs.getY()) {
                return true;
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

struct Comparetion
{
    bool operator()(const Point &lhs, const Point &rhs)
    {
        /* return lhs.getX() < rhs.getX(); */
        if (lhs.getDistance() < rhs.getDistance()) {
            return true;
        }
        else if (lhs.getDistance() == rhs.getDistance()) {
            if (lhs.getX() < rhs.getX()) {
                return true;
            }
            else if (lhs.getX() == rhs.getX()) {
                if (lhs.getY() < rhs.getY()) {
                    return true;
                }
                else {
                    return false;
                }
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }
    }
};

void test_class()
{
    /* priority_queue<Point, vector<Point>, std::greater<Point>> number; */
    priority_queue<Point, vector<Point>, Comparetion> number;

    vector<Point> vec = {
        Point(1, 2),
        Point(1, 2),
        Point(1, -2),
        Point(-1, 2),
        Point(11, 1),
        Point(1, 12)
    };

    for (size_t offset = 0; offset < vec.size(); ++offset) {
        number.push(vec[offset]);
        cout << "优先级最高的元素: " << number.top() << endl;
    }

    while (!number.empty()) {
        cout << number.top() << " ";
        number.pop();
    }
    cout << endl;
}

int main()
{
    /* test(); */
    test_class();
    return 0;
}
