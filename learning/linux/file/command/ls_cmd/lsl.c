#include <func.h>

int ls_al(DIR *dirp);
void printmode(mode_t st_mode);

int main(int argc, char *argv[])
{
    ARGS_CHECK(argc, 2);
    DIR *dirp = opendir(argv[1]);//获取目录流

    int ret = chdir(argv[1]);//改变当前工作目录
    ERROR_CHECK(ret, -1, "chdir");

    ls_al(dirp);
    closedir(dirp);
    return 0;
}
int ls_al(DIR *dirp){
    struct dirent *pdirent;
    struct stat *pstatbuf = (struct stat*)malloc(sizeof(struct stat));

    while((pdirent = readdir(dirp)) != NULL) {
        int ret = stat(pdirent->d_name, pstatbuf);
        ERROR_CHECK(ret, -1, "stat");

        printmode(pstatbuf->st_mode);
    }
    return 0;
}
void printmode(mode_t st_mode){
        
}
