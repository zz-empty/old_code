#include "wordInstead.hpp"
#include <iostream>

using std::cout;
using std::endl;

using namespace myfunc;

void test0(const string &file, const string &rule)
{
    WordInstead w1(file, rule);
}

int main()
{
    test0("file.txt", "rule.txt");
    return 0;
}

