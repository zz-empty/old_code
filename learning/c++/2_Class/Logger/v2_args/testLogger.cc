#include "Logger.hpp"
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

using namespace wd;


#if 1
void test0()
{
    Logger::getInstance()->warn("something is warn!");
    Logger::getInstance()->error("something is error!");
    Logger::getInstance()->debug("something is debug!");
    Logger::getInstance()->info("the important info!");
}

void test1()
{
    Logger::getInstance()->warn(MSGCAT("something is warn!"));
    Logger::getInstance()->error(MSGCAT("something is error!"));
    Logger::getInstance()->debug(MSGCAT("something is debug!"));
    Logger::getInstance()->info(MSGCAT("the important info!"));
}

void test2()
{
    LOGINFO("info is comming!");
    LOGWARN("warn is comming!");
    LOGDEBUG("debug is comming!");
    LOGERROR("error is comming!");
}
#endif
void test3()
{

    Logger *log = Logger::getInstance();
    int number = 100;
    const char *pStr = "hello, log4cpp";
    log->warn("this is a warn message, number = %d, str = %s\n", number, pStr);
    log->info("The log is info message");
    log->error("The log is error message");
    log->fatal("The log is fatal message");
    log->crit("The log is crit message");
    log->warn("this is a warn message");
    Logger::destroy();
}

int main()
{
    test3();
    return 0;
}

