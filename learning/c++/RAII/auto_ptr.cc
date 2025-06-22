#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::auto_ptr;

void test()
{
    int *pInt = new int(10);
    auto_ptr<int> ap(pInt);
}

int main()
{
    return 0;
}

