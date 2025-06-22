#include "log.h"
#include <iostream>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>

using namespace log4cpp;

using std::cout;
using std::endl;

MyLogger *MyLogger::_pLogger = nullptr;

MyLogger *MyLogger::getInstance()
{
    if (!_pLogger) {
        _pLogger = new MyLogger();
    }
    return _pLogger;
}

void MyLogger::destory()
{
    if(_pLogger) {
        delete _pLogger;
        _pLogger = nullptr;
    }
}

MyLogger::MyLogger()
:_mycat(Category::getRoot().getInstance("Mycat"))
{
    //日志的格式
    PatternLayout *ppl1 = new PatternLayout();
    ppl1->setConversionPattern("%d %c [%p] %m %n");

    PatternLayout *ppl2 = new PatternLayout();
    ppl2->setConversionPattern("%d %c [%p] %m %n");

    //日志的地址
    OstreamAppender *poa = new OstreamAppender("OstreamAppender123", &cout);
    poa->setLayout(ppl1);

    FileAppender *pfa = new FileAppender("FileAppender123", "zkong.log");
    pfa->setLayout(ppl2);

    _mycat.addAppender(poa);
    _mycat.addAppender(pfa);
    _mycat.setPriority(Priority::DEBUG);
}

MyLogger::~MyLogger()
{
    Category::shutdown();
}

void MyLogger::warn(const char *msg)
{
    _mycat.warn(msg);
}

void MyLogger::error(const char *msg)
{
    _mycat.error(msg);
}

void MyLogger::debug(const char *msg)
{
    _mycat.debug(msg);
}

void MyLogger::info(const char *msg)
{
    _mycat.info(msg);
}
