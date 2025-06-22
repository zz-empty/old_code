#include <func.h>
void newFunc() {
    puts("NEWFUNC");
}
void func() {
    puts("func");
    _exit(0);
    exit(3);
}
int main()
{
    atexit(newFunc);
    func();
    return 0;
}

