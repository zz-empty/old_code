#include <iostream>
#include <list>

using std::cout;
using std::endl;
using std::list;

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
    list<int> number = {4, 2, 1, 1, 8, 6, 5}; 
    display(number);
    
    cout << endl;
    cout << "-------test list::sort-------" << endl;
    /* number.sort(std::less<int>()); */
    number.sort(std::greater<int>());
    display(number);


    cout << endl;
    cout << "-------test list::reverse--------" << endl;
    number.reverse();
    display(number);

    cout << endl;
    cout << "------test list::splice---------" << endl;
    list<int> number3 = {5, 3, 2, 1, 9};
    display(number3);
    auto it = number.begin();
    ++it;
    ++it;
    /* number.splice(it, number3); */
    /* display(number); */
    /* display(number3); */
    number.splice(number.begin(), number3, number3.begin());
    display(number);
    display(number3);
}

int main()
{
    test();
    return 0;
}

