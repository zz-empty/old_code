#include "log.h"
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;


string connectStr(const char *msg) {
    string s1 = string("\tFile:") + string(__FILE__) + " " + 
                string("Func:") + string(__func__) + " " + 
                string("Line:") + string(std::to_string(__LINE__)) + "\t" + 
                msg;
    return s1;
}

void test1() 
{
    MyLogger *ps1 = MyLogger::getInstance();

    ps1->warn("warning");
    ps1->info("warning");
    ps1->error("warning");
    ps1->debug("warning");

    MyLogger::destory();
}

void test2()
{
    MyLogger::getInstance()->warn("something is coming!");
}

void test3()
{
    cout << "File:" << __FILE__ << "\tFunc:" << __FUNCTION__ << "\tLine:" << __LINE__ << endl;
}

void test4()
{
    MyLogger::getInstance()->warn(connectStr("waring").c_str());
    MyLogger::getInstance()->info(connectStr("some info").c_str());
    MyLogger::getInstance()->error(connectStr("some error").c_str());
    MyLogger::getInstance()->debug(connectStr("few defug").c_str());

    MyLogger::destory();

}

void test5()
{
    MyLogger::getInstance()->warn(PREFIX("warning"));
    MyLogger::getInstance()->info(PREFIX("some coming"));
    MyLogger::getInstance()->error(PREFIX("some error"));
    MyLogger::getInstance()->debug(PREFIX("some bug"));

    MyLogger::destory();
}

void test6()
{
    LOGINFO("normal info");
    LOGWARN("warning");
    LOGERROR("something error");
    LOGDEBUG("few bug");

    LOGDESTORY();
}

int main()
{
    test6();
    return 0;
}

