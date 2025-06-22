#include <iostream>

using std::cout;
using std::endl;

class FunctionObject
{
public:
    FunctionObject(int cnt = 0) :_cnt(cnt) {}
    int operator()(int a, int b);
    int operator()(int a, int b, int c);
    int getCnt();
private:
    int _cnt;//record func state
};

int FunctionObject::getCnt()
{
    return _cnt;
}

int FunctionObject::operator()(int a, int b)
{
    ++_cnt;
    return a + b;
}
int FunctionObject::operator()(int a, int b, int c)
{
    ++_cnt;
    return a * b * c;
}

int main()
{
    FunctionObject fo;
    int a = 2;
    int b = 4;
    int c = 8;

    cout << "fo(a,b) = " << fo(a, b) << endl;
    cout << "fo(a,b,c) = " << fo(a, b, c) << endl;
    cout << "fo.cnt = " << fo.getCnt() << endl;
    return 0;
}

