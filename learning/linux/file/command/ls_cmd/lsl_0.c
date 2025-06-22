#include <func.h>

void printStat(struct dirent *p, struct stat *buf);

int main(int argc, char *argv[])
{
    ARGS_CHECK(argc, 2);
    DIR *dirp = opendir(argv[1]);//获取目录流

    chdir(argv[1]);
    struct dirent *pdirent;//获取目录项
    struct stat statbuf;//文件结构体 
    while((pdirent = readdir(dirp)) != NULL) {
        int ret = stat(pdirent->d_name, &statbuf);
        ERROR_CHECK(ret, -1, "stat");
        printStat(pdirent, &statbuf);
    }

    closedir(dirp);
    return 0;
}

void printStat(struct dirent *pdirent, struct stat *buf){
    struct tm *tmp;
    tmp = gmtime(&buf->st_mtime);
    printf("%6o %ld %s %s %5ld %d %d %d %d %-15s\n",
           buf->st_mode,
           buf->st_nlink,
           getpwuid(buf->st_uid)->pw_name,
           getgrgid(buf->st_gid)->gr_name,
           buf->st_size,
           tmp->tm_mon,
           tmp->tm_mday,
           tmp->tm_hour,
           tmp->tm_min,
           pdirent->d_name
          );
}
