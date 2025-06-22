#ifndef __LOGGER_HPP__
#define __LOGGER_HPP__

#include <string.h>
#include <log4cpp/Category.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/RollingFileAppender.hh>
#include <log4cpp/Priority.hh>

using namespace log4cpp;
using std::string;

namespace wd
{

class Logger
{
public:
    static Logger * getInstance();
    static void destroy();

    template<typename... Args>
    void warn(const char* msg, Args... args);

    template<typename... Args>
    void error(const char* msg, Args... args);

    template<typename... Args>
    void debug(const char* msg, Args... args);

    template<typename... Args>
    void info(const char* msg, Args... args);
    
    template<typename... Args>
    void fatal(const char* msg, Args... args);

    template<typename... Args>
    void crit(const char* msg, Args... args);

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

//------------------------Logger实现---------------------------
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
    OstreamAppender *poa = new OstreamAppender("oafile", &std::cout);
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

//递归出口
void Mycat(std::stringstream &ss, const char *str)
{
    return;
}

//将输入的可变参数拼接成一个完整的字符串，存入内存流中
template<typename T, typename ...Args>
void Mycat(std::stringstream &ss, const char *str, const T &val, Args ...args)
{
    size_t i = 0;
    while (i < strlen(str)) {
        if ('%' == str[i]) {
            char c = str[i++];
            //判断类型
            if ('d' == c || 'c' == c || 'f' == c || 's' == c) {
                ss << val;
                Mycat(ss, str + i + 2, args...);
                return;//跳出循环
            }
            else {
                std::cout << "非法输入格式!" << std::endl;
                exit(-1);
            }
        }
        else {
            ss << str[i++];
        }
    }
}


template<typename... Args>
void Logger::warn(const char* msg, Args... args)
{
    std::stringstream ss;
    ss << "\t[" << __FILE__ << " " << __func__ << " " << __LINE__ << "]\t";

    std::stringstream temp;
    Mycat(temp, msg, args...);
    ss << temp.str();

    _mycat.warn(ss.str());
}

template<typename... Args>
void Logger::debug(const char* msg, Args... args)
{
    std::stringstream ss;
    ss << "\t[" << __FILE__ << " " << __func__ << " " << __LINE__ << "]\t";

    std::stringstream temp;
    Mycat(temp, msg, args...);
    ss << temp.str();

    _mycat.debug(ss.str());
}
template<typename... Args>
void Logger::error(const char* msg, Args... args)
{
    std::stringstream ss;
    ss << "\t[" << __FILE__ << " " << __func__ << " " << __LINE__ << "]\t";

    std::stringstream temp;
    Mycat(temp, msg, args...);
    ss << temp.str();

    _mycat.error(ss.str());
}
template<typename... Args>
void Logger::info(const char* msg, Args... args)
{
    std::stringstream ss;
    ss << "\t[" << __FILE__ << " " << __func__ << " " << __LINE__ << "]\t";

    std::stringstream temp;
    Mycat(temp, msg, args...);
    ss << temp.str();

    _mycat.info(ss.str());
}
template<typename... Args>
void Logger::fatal(const char* msg, Args... args)
{
    std::stringstream ss;
    ss << "\t[" << __FILE__ << " " << __func__ << " " << __LINE__ << "]\t";

    std::stringstream temp;
    Mycat(temp, msg, args...);
    ss << temp.str();

    _mycat.fatal(ss.str());
}
template<typename... Args>
void Logger::crit(const char* msg, Args... args)
{
    std::stringstream ss;
    ss << "\t[" << __FILE__ << " " << __func__ << " " << __LINE__ << "]\t";

    std::stringstream temp;
    Mycat(temp, msg, args...);
    ss << temp.str();

    _mycat.crit(ss.str());
}

}//end of namespace wd

#endif
