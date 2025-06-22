#include <iostream>
#include <string>
#include <deque>

using std::cout;
using std::endl;
using std::string;
using std::deque;


template<typename Container>
void display(const Container &c)
{
    for (auto &elem : c) {
        cout << elem << " ";
    }
    cout << endl;
}


void test1()
{
    deque<int> num = {3, 12, 41, 8, 3, 2, 6, 9};
    display(num);

    cout << endl;
    cout << "-------test deque push and pop-------" << endl;
    num.push_back(33);
    num.push_back(99);
    display(num);
    num.pop_back();
    display(num);

}

int main()
{
    test1();
    return 0;
}

