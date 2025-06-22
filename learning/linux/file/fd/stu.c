#include <func.h>
typedef struct student{
    char id[30];
    char name[30];
    double score;
}Stu_t, *pStu_t;

int main(int argc, char *argv[])
{
    ARGS_CHECK(argc, 2);

    int fd = open(argv[1], O_RDWR);
    ERROR_CHECK(fd, -1, "open");

    //Stu_t s[3] = {
    //    "1001", "zhangsan", 66,
    //    "1003", "lisi", 88,
    //    "1007", "wangwu", 76
    //};
    Stu_t s[3];
    int i;
    puts("input three student info(id name score)");
    for (i = 0; i < 3; ++i) {
        scanf("%s%s%lf", s[i].id, s[i].name, &s[i].score);
    }

    //input on binary form
    for (i = 0; i < 3; ++i) {
        write(fd, &s[i], sizeof(Stu_t));
    }

    //print
    lseek(fd, 0, SEEK_SET);
    Stu_t buf;
    while (1) {
        int ret = read(fd, &buf, sizeof(buf));
        if (0 == ret) {
            break;
        }
        printf("%s\t%-10s\t%5.2lf\n", buf.id, buf.name, buf.score);
    }
    close(fd);
    return 0;
}

