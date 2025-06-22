#include <func.h>
void printType(mode_t st_mode);
void printMode(mode_t st_mode);

int main(int argc, char *argv[])
{
    ARGS_CHECK(argc, 2);

    struct stat statbuf;
    int ret = stat(argv[1], &statbuf);
    ERROR_CHECK(ret, -1, "stat");

    //第一行 文件名
    printf("%7s \'%s\'\n", "File:", argv[1]);

    //第二行 文件大小 字节块 IO块 文件类型
    printf("%7s %-10ld\t", "Size:", statbuf.st_size);
    printf("%7s %-11ld", "Blocks:", statbuf.st_blocks);
    printf("%s %-7ld", "IO Block:", statbuf.st_blksize);
    //bug 识别不了链接文件
    printType(statbuf.st_mode);
    printf("\n");

    //第三行 设备   Inode   Links
    printf("%7s %-15ld", "Device:", statbuf.st_dev);
    printf("%7s %-10ld ", "Inode:", statbuf.st_ino);
    printf("%7s %ld ", "Links:", statbuf.st_nlink);
    printf("\n");

    //第四行 权限 用户ID 组ID
    printf("%7s (%d/", "Access:", statbuf.st_mode);
    printMode(statbuf.st_mode);
    printf(")\t");
    printf("%s (%d/%s)\t", "Uid:", statbuf.st_uid, getpwuid(statbuf.st_uid)->pw_name);
    printf("%s (%d/%s)\t", "Gid:", statbuf.st_gid, getgrgid(statbuf.st_gid)->gr_name);

    printf("\n");

    struct tm *timebuf;
    //第五行 最后访问时间
    timebuf  = gmtime(&statbuf.st_atime);
    printf("%7s %4d-%2d-%2d %2d:%2d:%2d", "Access:", 
           timebuf->tm_year,
           timebuf->tm_mon,
           timebuf->tm_mday,
           timebuf->tm_hour,
           timebuf->tm_min,
           timebuf->tm_sec);
    printf("\n");
    //第六行
    timebuf  = gmtime(&statbuf.st_mtime);
    printf("%7s %4d-%2d-%2d %2d:%2d:%2d", "Modify:", 
           timebuf->tm_year,
           timebuf->tm_mon,
           timebuf->tm_mday,
           timebuf->tm_hour,
           timebuf->tm_min,
           timebuf->tm_sec);
    printf("\n");

    //第七行
    timebuf  = gmtime(&statbuf.st_ctime);
    printf("%7s %4d-%2d-%2d %2d:%2d:%2d", "Change:", 
           timebuf->tm_year,
           timebuf->tm_mon,
           timebuf->tm_mday,
           timebuf->tm_hour,
           timebuf->tm_min,
           timebuf->tm_sec);
    printf("\n");

    //第八行
    printf("%7s -\n", "Birth:");
    return 0;
}

void printType(mode_t st_mode){
    if (st_mode & S_IFDIR){
        printf("directory");
    }
    else if (st_mode & S_IFREG) {
        printf("regular file");
    }
    else if (st_mode & S_IFIFO) {
        printf("fifo");
    }
    else if (st_mode & S_IFCHR) {
        printf("character device");
    }
    else if (st_mode & S_IFBLK) {
        printf("block device");
    }
    else if (st_mode & S_IFLNK) {
        printf("symbolic link");
    }
    else if (st_mode & S_IFSOCK) {
        printf("socket");
    }
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
