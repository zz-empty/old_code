#include "Mylogger.h"
#include <stdlib.h>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
 
using std::cout;
using std::endl;
 
Mylogger * Mylogger::_pInstance=Mylogger::getInstance(); //必须在实现文件中初始化，在头文件中初始化易出现重复定义
 
Mylogger::Mylogger()
:_root(Category::getRoot().getInstance("Mycat"))  //获得日志记录器,记录器名为Mycat
{
    //设置日志的格式
    //文件格式
    PatternLayout *ppl1 = new PatternLayout();   
    ppl1->setConversionPattern("%d %c [%p] %m %n");
 
    //终端格式
    PatternLayout *ppl2 = new PatternLayout();
    ppl2->setConversionPattern("%d %c [%p] %m %n");
 
    //设置日志输出的地点
    //输出到文件
    FileAppender *pfa = new FileAppender("FileAppender123", LOGFILENAME);
    pfa->setLayout(ppl1);
 
    //输出到输出流对象
    OstreamAppender *poa = new OstreamAppender("OstreamAppender1", &cout);
    poa->setLayout(ppl2);
 
    //绑定到记录器
    _root.addAppender(poa);
    _root.addAppender(pfa);
    _root.setPriority(Priority::DEBUG);
    
    cout<<"Mylogger()"<<endl;
}
 
void Mylogger::destroy()//销毁单例对象
{
    if(_pInstance!=nullptr)
    {
        delete _pInstance;
        _pInstance=nullptr;
    }
}
Mylogger *Mylogger::getInstance()//创建单例对象
{
    if(_pInstance==nullptr)
    {
        _pInstance=new Mylogger();
        atexit(destroy);//单例模式自动释放：注册函数，进程结束时自动调用
    }
    return _pInstance;
}
 
Mylogger::~Mylogger()
{
    cout<<"~Mylogger()"<<endl;
    Category::shutdown();//回收日志资源
}
 
void Mylogger::info(const char *msg)
{
    _root.info(msg);
}
 
void Mylogger::error(const char *msg)
{
    _root.error(msg);
}
 
void Mylogger::warn(const char *msg)
{
    _root.warn(msg);
}
 
void Mylogger::debug(const char *msg)
{
    _root.debug(msg);
}
