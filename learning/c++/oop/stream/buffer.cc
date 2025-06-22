#include <unistd.h>
#include <iostream>

using std::cout;
using std::endl;

void test_out();

int main()
{
    test_out();
    return 0;
}

void test_out()
{
    for (size_t idx = 0; idx < 1024; ++idx) {
        cout << "a";
    }
    cout << "b" << endl;

    sleep(3);
}
