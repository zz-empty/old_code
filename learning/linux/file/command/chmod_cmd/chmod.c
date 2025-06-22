#include <func.h>
int main(int argc, char *argv[])
{
    ARGS_CHECK(argc, 3);

    //argv[1]:convert from string to integer
    mode_t mode;
    sscanf(argv[1], "%o", &mode);

    //modify mode of the file
    int ret = chmod(argv[2], mode);
    ERROR_CHECK(ret, -1, "chmod");
    
    return 0;
}

