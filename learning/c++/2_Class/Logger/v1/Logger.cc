#include "Logger.hpp"
#include <iostream>

#include <log4cpp/PatternLayout.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/RollingFileAppender.hh>
#include <log4cpp/Priority.hh>

using std::cout;
using std::endl;

using namespace log4cpp;

namespace wd
{

Logger* Logger::_pLog = nullptr;

Logger * Logger::getInstance()
{
    if (!_pLog) {
        _pLog = new Logger();
    }
    return _pLog;
}

void Logger::destroy()
{
    if (_pLog) {
        delete _pLog;
        _pLog = nullptr;
    }
}


Logger::Logger()
:_mycat(Category::getRoot().getInstance("Mycat"))
{
    //格式化器

    PatternLayout *pp1 = new PatternLayout();
    pp1->setConversionPattern("%d %c [%p] %m %n");
    PatternLayout *pp2 = new PatternLayout();
    pp2->setConversionPattern("%d %c [%p] %m %n");

    //输出器
    OstreamAppender *poa = new OstreamAppender("oafile", &cout);
    poa->setLayout(pp1);

    RollingFileAppender *pra = new RollingFileAppender("RollingFileAppender", "work.log", 5 * 1024, 3);
    pra->setLayout(pp2);

    _mycat.addAppender(poa);
    _mycat.addAppender(pra);

    //过滤器
    _mycat.setPriority(Priority::DEBUG);
}

Logger::~Logger()
{
    Category::shutdown();
}

void Logger::warn(const char* msg)
{
    _mycat.warn(msg);
}
void Logger::error(const char* msg)
{
    _mycat.error(msg);
}
void Logger::debug(const char* msg)
{
    _mycat.debug(msg);
}
void Logger::info(const char* msg)
{
    _mycat.info(msg);
}

}//end of namespace wd
