#include <log4cpp/BasicLayout.hh>
#include <log4cpp/SimpleLayout.hh>
#include <log4cpp/PatternLayout.hh>

#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/RollingFileAppender.hh>

#include <log4cpp/Category.hh>
#include <log4cpp/Priority.hh>

#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

using namespace log4cpp;

void test_BasicLayout();
void test_SimpleLayout();
void test_PatternLayout();
void test_RollingFileAppender();

int main()
{
    /* test_BasicLayout(); */
    /* test_SimpleLayout(); */
    /* test_PatternLayout(); */
    test_RollingFileAppender();
    return 0;
}

void test_BasicLayout()
{
    //set log layout
    BasicLayout *pbl = new BasicLayout();

    //set log destination
    OstreamAppender *pos = new OstreamAppender("OstreamAppender123", &cout);
    pos->setLayout(pbl);

    //create log recorder
    Category &root = Category::getRoot();
    root.addAppender(pos);
    root.setPriority(Priority::ERROR);//set log filter

    //recording
    root.fatal("The log is fatal");
    root.alert("The log is alert");
    root.crit("The log is crit");
    root.error("The log is error");
    root.warn("The log is warn");

    //recycling log_recorder resource
    Category::shutdown();
}

void test_SimpleLayout()
{
    //set log layout
    SimpleLayout *pbl = new SimpleLayout();

    //set log destination
    OstreamAppender *pos = new OstreamAppender("OstreamAppender123", &cout);
    pos->setLayout(pbl);

    //create log recorder
    Category &root = Category::getRoot();
    root.addAppender(pos);
    root.setPriority(Priority::ERROR);//set log filter

    //recording
    root.fatal("The log is fatal");
    root.alert("The log is alert");
    root.crit("The log is crit");
    root.error("The log is error");
    root.warn("The log is warn");

    //recycling log_recorder resource
    Category::shutdown();
}

void test_PatternLayout()
{
    //set log layout
    PatternLayout *ppl = new PatternLayout();
    ppl->setConversionPattern("%d %c [%p] %m %n");

    PatternLayout *ppl2 = new PatternLayout();
    ppl2->setConversionPattern("%d %c [%p] %m %n");

    //set log destination
    OstreamAppender *pos = new OstreamAppender("OstreamAppender123", &cout);
    pos->setLayout(ppl);

    FileAppender *pfl = new FileAppender("FileAppender123", "wd.log");
    pfl->setLayout(ppl2);

    //create log recorder
    /* Category &root = Category::getRoot(); */
    Category &root = Category::getRoot().getInstance("testlog");
    root.addAppender(pos);  //add dest ostream
    root.addAppender(pfl);  //add dest file
    root.setPriority(Priority::ERROR);//set log filter

    //recording
    root.fatal("The log is fatal");
    root.alert("The log is alert");
    root.crit("The log is crit");
    root.error("The log is error");
    root.warn("The log is warn");

    //recycling log_recorder resource
    Category::shutdown();
}

void test_RollingFileAppender()
{
    //set log layout
    PatternLayout *ppl = new PatternLayout();
    ppl->setConversionPattern("%d %c [%p] %m %n");

    PatternLayout *ppl2 = new PatternLayout();
    ppl2->setConversionPattern("%d %c [%p] %m %n");

    //set log destination
    OstreamAppender *pos = new OstreamAppender("OstreamAppender123", &cout);
    pos->setLayout(ppl);

    FileAppender *prf = new RollingFileAppender("FileAppender123", "test.log", 5 * 1024, 3);
    prf->setLayout(ppl2);

    //create log recorder
    /* Category &root = Category::getRoot(); */
    Category &root = Category::getRoot().getInstance("log_writer");
    root.addAppender(pos);  //add dest ostream
    root.addAppender(prf);  //add dest file
    root.setPriority(Priority::ERROR);//set log filter

    //recording
    size_t idx = 0;
    size_t end = 100;
    for (idx = 0; idx < end; ++idx) {
        root.fatal("The log is fatal");
        root.alert("The log is alert");
        root.crit("The log is crit");
        root.error("The log is error");
        root.warn("The log is warn");
    }

    //release log_recorder resource
    Category::shutdown();
}

