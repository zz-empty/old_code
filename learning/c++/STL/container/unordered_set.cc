#include <math.h>
#include <iostream>
#include <unordered_set>

using std::cout;
using std::endl;
using std::unordered_set;

template<typename Container>
void display(const Container &c)
{
    for (auto &elem : c) {
        cout << elem << " ";
    }
    cout << endl;
}

void test()
{
    unordered_set<int> number = {4, 2, 8, 7, 2, 5, 1, 4};
    display(number);
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

//特化版本的hash
namespace std
{

template<>
struct hash<Point>
{
    size_t operator()(const Point &rhs) const
    {
        return (rhs.getX() << 1) ^ (rhs.getY() << 2);
    }
};//end of struct hash<Point>

}//end of namespace std

//自定义hash
struct HashPoint
{
    size_t operator()(const Point &rhs) const
    {
        cout << "struct HashPoint" << endl;
        return (rhs.getX() << 1) ^ (rhs.getY() << 2);
    }
};

namespace std
{

template<>
struct equal_to<Point>
{
    bool operator()(const Point &lhs, const Point &rhs) const
    {
        cout << "struct equal_to" << endl;
        return (lhs.getX() == rhs.getX()) && (lhs.getY() == rhs.getY());
    }

};//end of struct equal_to<Point>

}//end of namespace std

#if 0
bool operator==(const Point &lhs, const Point &rhs)
{
    return (lhs.getX() == rhs.getX()) && (lhs.getY() == rhs.getY());
}
#endif

void test_class()
{
    unordered_set<Point> ps = {
    /* unordered_set<Point, HashPoint> ps = { */
        Point(3, 3),
        Point(3, 3),
        Point(3, 3),
        Point(3, 3),
        Point(2, 1),
        Point(4, 3),
        Point(0, 9),
        Point(-3, 1),
        Point(1, 3)
    };
    display(ps);
}

int main()
{
    /* test(); */
    test_class();
    return 0;
}

