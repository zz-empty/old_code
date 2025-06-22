#include "stack.hpp"
#include <iostream>

using std::cout;
using std::endl;

void test0()
{
    using namespace myclass;
    Stack st;
    cout << "Is stack empty? " << (st.empty() ? "yes" : "no") << endl;
    cout << "Is stack full? " << (st.full() ? "yes" : "no") << endl;

    cout << endl;
    cout << "----start push-----" << endl;
    int idx = 0;
    for (idx = 1; idx != 15; ++idx) {
        st.push(idx);
    }
    cout << "Is stack full? " << (st.full() ? "yes" : "no") << endl;

    cout << endl;
    cout << "----start pop-----" << endl;
    while (!st.empty()) {
        cout << st.top() << endl;
        st.pop();
    }
    cout << "Is stack empty? " << (st.empty() ? "yes" : "no") << endl;

}

int main()
{
    test0();
    return 0;
}

