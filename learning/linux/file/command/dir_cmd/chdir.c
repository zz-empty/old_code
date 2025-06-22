#include <func.h>

int main(int argc, char *argv[])
{
    ARGS_CHECK(argc, 2);
    
    printf("before chdir, pwd = %s\n", getcwd(NULL, 0));
    int ret = chdir(argv[1]);
    ERROR_CHECK(ret, -1, "chdir");
    printf("after chdir, pwd = %s\n", getcwd(NULL, 0));

    return 0;
}

