#include <log4cpp/BasicLayout.hh>
#include <log4cpp/SimpleLayout.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/RollingFileAppender.hh>
#include <log4cpp/Category.hh>
#include <log4cpp/Priority.hh>
#include <iostream>

using std::cout;
using std::endl;

using namespace log4cpp;//一次性将log4cpp中的实体全部引出来

void test()
{
    //日志的格式
    /* BasicLayout *pbl = new BasicLayout(); */
    SimpleLayout *psl = new SimpleLayout();

    //日志的目的地
    /* OstreamAppender *pos = new OstreamAppender("OstreamAppender123", &cout); */
    /* pos->setLayout(pbl); */
    OstreamAppender *pos = new OstreamAppender("OstreamAppender123", &cout);
    pos->setLayout(psl);
    
    //日志种类（日志记录器）
    Category &root = Category::getRoot();
    root.addAppender(pos);
    root.setPriority(Priority::ERROR);//过滤器

    root.fatal("The log is fatal");
    root.alert("The log is alter");
    root.crit("The log is crit");
    root.error("The log is error");
    root.warn("The log is warn");

    //回收资源
    Category::shutdown();

}

void test2()
{
    //日志的格式
    PatternLayout *ppl1 = new PatternLayout();
    ppl1->setConversionPattern("%d %c [%p] %m %n");

    PatternLayout *ppl2 = new PatternLayout();
    ppl2->setConversionPattern("%d %c [%p] %m %n");

    //日志的目的地
    OstreamAppender *pos = new OstreamAppender("OstreamAppender123", &cout);
    pos->setLayout(ppl1);

    RollingFileAppender *ppfa = 
        new RollingFileAppender("RollingFileAppender123", "test.log",
                                5 * 1024, 3);
    ppfa->setLayout(ppl2);
    
    //日志种类（日志记录器）
    Category &root = Category::getRoot();
    root.addAppender(pos);
    root.addAppender(ppfa);
    root.setPriority(Priority::ERROR);//过滤器

    size_t idx = 0;
    while(idx < 100)
    {
       root.fatal("The log is fatal");
       root.alert("The log is alter");
       root.crit("The log is crit");
       root.error("The log is error");
       root.warn("The log is warn");
       ++idx;

    }

    //回收资源
    Category::shutdown();

}
void test3()
{
    //日志的格式
    PatternLayout *ppl1 = new PatternLayout();
    ppl1->setConversionPattern("%d %c [%p] %m %n");

    PatternLayout *ppl2 = new PatternLayout();
    ppl2->setConversionPattern("%d %c [%p] %m %n");

    //日志的目的地
    OstreamAppender *pos = new OstreamAppender("OstreamAppender123", &cout);
    pos->setLayout(ppl1);

    FileAppender *pfl = new FileAppender("FileAppender1234", "wd.log");
    pfl->setLayout(ppl2);
    
    //日志种类（日志记录器）
    Category &root = Category::getRoot().getInstance("MyCat");
    root.addAppender(pos);
    root.addAppender(pfl);
    root.setPriority(Priority::ERROR);//过滤器

    root.fatal("The log is fatal");
    root.alert("The log is alter");
    root.crit("The log is crit");
    root.error("The log is error");
    root.warn("The log is warn");

    //回收资源
    Category::shutdown();

}
int main(int argc, char **argv)
{
    test2();
    return 0;
}
