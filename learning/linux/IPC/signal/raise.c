#include <func.h>

int main() 
{
    raise(SIGABRT);
    while(1);
    return 0;
}

