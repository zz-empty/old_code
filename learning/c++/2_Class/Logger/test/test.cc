#include "Mylogger.h"
 
void test() 
{
    int number = 100;
    const char *pstr = "hello";
    logInfo("This is an info message. number = %d, str = %s\n", number, pstr);
    logWarn("this is a warn message!\n");
    logError("this is a error message! str=%s\n",pstr);
    logDebug("this is a debug message!,number=%d\n",number);
}
 
 
int main(int argc,char *argv[])
{
    test();
    return 0;
}
