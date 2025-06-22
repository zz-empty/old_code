#ifndef __LOG_H__
#define __LOG_H__

#include <log4cpp/Category.hh>

using namespace log4cpp;

class MyLogger
{
public:
    static MyLogger *getInstance();
    static void destory();

    void warn(const char *msg);
	void error(const char *msg);
	void debug(const char *msg);
	void info(const char *msg);

private:
    MyLogger();
    ~MyLogger();
    MyLogger(const MyLogger &rhs) = delete;
    MyLogger &operator=(const MyLogger &rhs) = delete;

private:
    static MyLogger *_pLogger;
    Category &_mycat;
};

#define PREFIX(msg) ("\t" + string(__FILE__) + " " + \
                string(__func__) + " " + \
                string(std::to_string(__LINE__)) + "    " + msg).c_str()

#define LOGINFO(msg) MyLogger::getInstance()->info(PREFIX(msg));
#define LOGWARN(msg) MyLogger::getInstance()->warn(PREFIX(msg));
#define LOGERROR(msg) MyLogger::getInstance()->error(PREFIX(msg));
#define LOGDEBUG(msg) MyLogger::getInstance()->debug(PREFIX(msg));
#define LOGDESTORY() MyLogger::destory();

#endif
