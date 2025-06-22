#include <iostream>

using std::cout;
using std::endl;

#ifdef __cplusplus
extern "C" 
{
#endif
    int add(int x, int y) {
        return x + y;
    }

#ifdef __cplusplus
} //end of extern "C"
#endif

long add(int x, int y, int z) {
    return x + y + z;
}

int main()
{
    return 0;
}

