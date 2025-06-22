#ifndef __MYLOGGER__H__
#define __MYLOGGER__H__
#include <log4cpp/Category.hh>
 
#define LOGFILENAME "test.log"
 
using namespace log4cpp;//导入全部log4cpp的全部实体
 
class Mylogger
{
public:
    static Mylogger *getInstance();
    static void destroy();
 
    void warn(const char * msg);
    void error(const char * msg);
    void debug(const char * msg);
    void info(const char * msg);
    
    template <class... Args>
    //不能把函数的实现写在Mylogger.cc中
    //和inline一样，函数的实现和声明不能分开，否则会链接失败
    void warn(const char * msg, Args... args)
    {
        _root.warn(msg, args...);
    }
 
    template <class... Args>
    void error(const char * msg, Args... args)
    {
        _root.error(msg, args...);
 
    }
 
    template <class... Args>
    void info(const char * msg, Args... args)
    {
        _root.info(msg, args...);
 
    }
 
 
    template <class... Args>
    void debug(const char * msg, Args... args)
    {
        _root.debug(msg, args...);
 
    }
 
 
private:
    Mylogger();
    ~Mylogger();
private:
    static Mylogger *_pInstance;
    Category &_root; //引用成员必须在构造函数的初始化列表进行初始化，否则会报错
 
};
 
//文件名、行号、函数名相关，这里没用到不用管
#define prefic(msg) string(__FILE__).append(" ").append(__FUNCTION__) \
            .append(" ").append(std::to_string(__LINE__))\
                    .append(":").append(msg).c_str()
 
//##__VA_ARGS__接收可变数目的参数，当宏的调用展开时，实际的参数就传递给函数了
#define logError(msg,...) Mylogger::getInstance()->error(msg,##__VA_ARGS__) 
#define logInfo(msg,...) Mylogger::getInstance()->info(msg,##__VA_ARGS__)
#define logDebug(msg,...) Mylogger::getInstance()->debug(msg,##__VA_ARGS__)
#define logWarn(msg,...) Mylogger::getInstance()->warn(msg,##__VA_ARGS__)
//##的用处：当只有msg参数时，忽略后面的,号
 
#endif
