#ifndef __LOGGER_HPP__
#define __LOGGER_HPP__

#include <log4cpp/Category.hh>

namespace wd
{

class Logger
{
public:
    static Logger * getInstance();
    static void destroy();

    void warn(const char* msg);
    void error(const char* msg);
    void debug(const char* msg);
    void info(const char* msg);

private:
    Logger();
    ~Logger();

private:
    static Logger * _pLog;
    log4cpp::Category &_mycat;
};

#define MSGCAT(msg) ("\t[" + string(__FILE__) + " " + \
                     string(__func__) + " " + string(std::to_string(__LINE__)) + "]\t" + msg).c_str()

#define LOGWARN(msg) Logger::getInstance()->warn(MSGCAT(msg))
#define LOGERROR(msg) Logger::getInstance()->error(MSGCAT(msg))
#define LOGDEBUG(msg) Logger::getInstance()->debug(MSGCAT(msg))
#define LOGINFO(msg) Logger::getInstance()->info(MSGCAT(msg));

}//end of namespace wd

#endif
