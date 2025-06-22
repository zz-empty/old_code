#include "head.h"

//打印目录流中所有目录项节点信息
int ls_l(DIR *dirp);
//将文件类型和权限从数字转为字符串，并输出
void printMode(mode_t);

//执行ls -al命令
int lsl(const char *pathname)
{
    //获取目录流
    DIR *dirp = opendir(pathname);
    ERROR_CHECK(dirp, NULL, "opendir");

    //更改工作目录
    int ret = chdir(pathname);
    ERROR_CHECK(ret, -1, "ret");

    //打印目录流中每个目录项的详细信息
    ls_l(dirp);

    //关闭目录流
    closedir(dirp);
    return 0;
}

int ls_l(DIR *dirp) {
    struct dirent *pdirent;
    struct stat statbuf;

    while (NULL !=(pdirent = readdir(dirp))) {
        int ret = stat(pdirent->d_name, &statbuf);
        ERROR_CHECK(ret, -1, "stat");
        struct tm *tmp;
        tmp = gmtime(&statbuf.st_mtime);

        const char *mon[] = {"Jan", "Fab", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

        //打印类型和权限
        printMode(statbuf.st_mode);
        //打印链接、用户名、组名、大小、月份、天数
        printf(" %2ld %-s %-s %5ld %s %d",
               statbuf.st_nlink,
               getpwuid(statbuf.st_uid)->pw_name,
               getgrgid(statbuf.st_gid)->gr_name,
               statbuf.st_size,
               mon[tmp->tm_mon],
               tmp->tm_mday
              );

        //打印时间：min:sec
        printf(" %2d:%2d", (tmp->tm_hour+8)%24, tmp->tm_min);

        //打印文件名
        printf(" %-s\n", pdirent->d_name);
    }
    return 0;
}

void printMode(mode_t st_mode){
    mode_t mode;
    mode = st_mode & S_IFMT;
    //类型
    if (mode == S_IFREG){
        printf("-");
    }
    else if (mode == S_IFDIR) {
        printf("d");
    }
    else if (mode == S_IFCHR) {
        printf("c");
    }
    else if (mode == S_IFBLK) {
        printf("b");
    }
    else if (mode == S_IFIFO) {
        printf("p");
    }
    else if (mode == S_IFLNK) {
        printf("l");
    }
    else if (mode == S_IFSOCK){
        printf("s");
    }

    //用户的rwx
    if (st_mode & S_IRUSR) {
        printf("r");
    }
    else {
        printf("-");
    }
    if (st_mode & S_IWUSR) {
        printf("w");
    }
    else {
        printf("-");
    }
    if (st_mode & S_IXUSR) {
        printf("x");
    }
    else {
        printf("-");
    }

    //组的rwx
    if (st_mode & S_IRGRP) {
        printf("r");
    }
    else {
        printf("-");
    }
    if (st_mode & S_IWGRP) {
        printf("w");
    }
    else {
        printf("-");
    }
    if (st_mode & S_IXGRP) {
        printf("x");
    }
    else {
        printf("-");
    }

    //其他rdx
    if (st_mode & S_IROTH) {
        printf("r");
    }
    else {
        printf("-");
    }
    if (st_mode & S_IWOTH) {
        printf("w");
    }
    else {
        printf("-");
    }
    if (st_mode & S_IXOTH) {
        printf("x");
    }
    else {
        printf("-");
    }
}
