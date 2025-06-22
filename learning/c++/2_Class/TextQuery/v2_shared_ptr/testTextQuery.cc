#include "TextQuery.hpp"
#include <iostream>

#define ARGS_CHECK(argc,num) {if(argc != num) {   \
        fprintf(stderr, "args error!\n");\
        return -1;}}

using std::cout;
using std::endl;


void test0(char *filename)
{
    using namespace wd;
    TextQuery tq(filename);

    string word;
    cout << "please input query word : " ;
    std::cin >> word;
    print(cout, tq.query(word));
}

int main(int argc, char **argv)
{
    ARGS_CHECK(argc, 2);
    test0(argv[1]);
    return 0;
}

