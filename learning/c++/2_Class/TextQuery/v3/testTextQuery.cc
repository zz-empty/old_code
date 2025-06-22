#include "TextQuery.hpp"
#include "Query.hpp"
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
    /* cout << "please input query word : " ; */
    /* std::cin >> word; */
    /* print(cout, tq.query(word)); */

    //单个单词查询
    /* Query q1("to"); */
    /* print(cout, q1.eval(tq)); */
     
    //逻辑非查询
    /* Query a = ~Query("the"); */
    /* print(cout, a.eval(tq)); */

    //逻辑或查询
    /* Query b = Query("market") | Query("industry"); */
    /* print(cout, b.eval(tq)); */
    //逻辑与查询
    Query c = Query("the") & Query("year");
    print(cout, c.eval(tq));


}

int main(int argc, char **argv)
{
    ARGS_CHECK(argc, 2);
    test0(argv[1]);
    return 0;
}

