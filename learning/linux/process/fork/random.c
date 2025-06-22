#include <func.h>
int main(int argc, char *argv[])
{
    ARGS_CHECK(argc, 3);
    int lhs = atoi(argv[1]);
    int rhs = atoi(argv[2]);

    srand(time(NULL));
    int range = rhs - lhs + 1;
    int random_num = lhs + rand() % range;

    printf("random_num = %d\n", random_num);
    return 0;
}

