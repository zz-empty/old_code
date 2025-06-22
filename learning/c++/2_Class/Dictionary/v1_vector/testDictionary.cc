#include "Dictionary.hpp"
#include <iostream>

#define ARGS_CHECK(argc,num) {if(argc != num) {   \
        fprintf(stderr, "args error!\n");\
        return -1;}}

using std::cout;
using std::endl;

void test0(char *filename)
{
    using namespace wd;
    Dictionary dict;

    dict.read(filename);
    dict.sort_by_wordcnt();
    /* dict.sort_by_name(); */
    /* dict.display(); */
    /* dict.store("dictionary01.txt"); */
    dict.store("dictionary02.txt");
}

void test1(char *filename)
{
    using namespace wd;
    Dictionary dict;

    dict.read(filename);
    dict.top10();
}

int main(int argc, char **argv)
{
    ARGS_CHECK(argc, 2);
    test0(argv[1]);
    /* test1(argv[1]); */
    return 0;
}

