#include "Logger.hpp"
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

using namespace wd;


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

int main()
{
    test2();
    return 0;
}

