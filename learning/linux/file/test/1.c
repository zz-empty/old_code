#include <func.h>
char* getDirname(char* path);
char* getFileName(char* path);
void printFilename(char* name);
void printLine2(struct stat* pstat);
void printLine3(struct stat* pstat);
void printLine4(struct stat* pstat);
void printFileType(struct stat* pstat);
int main(int argc,char* argv[])
{
    struct stat t_stat;
    int ret = stat(argv[1],&t_stat);
    char* name;
    if((t_stat.st_mode & S_IFMT) == S_IFDIR)
    {
        char* path;
        chdir(argv[1]);
        path = getcwd(NULL,0);
        name = getDirname(path);
        free(path);
    }
    else
    {
        name = getFileName(argv[1]);
    }
    printFilename(name);
    printLine2(&t_stat);
    printLine3(&t_stat);
    printLine4(&t_stat);
    free(name);

}
void printFilename(char* name)
{
    printf("  File: %s\n",name);
}

char* getFileName(char* path)
{
    int len = strlen(path);
    int size = 0;
    int i;
    int j;
    for(i = len - 1; i != - 1&& path[i] != '/';--i)
    {
        size++;
    }
    char* str = (char*)malloc(sizeof(char)* (size + 1));
    str[size] = '\0';
    for(i = len - 1,j = size - 1; i != - 1&& path[i] != '/';--i,--j)
    {
        str[j] = path[i];
    }
    return str;
}

char* getDirname(char* path)
{
    int tail = strlen(path) - 1;
    int size = 0;
    int i;
    int j;
    for(i = tail;path[i] != '/'; --i)
    {
        size++;
    }
    char* str = (char*)malloc(sizeof(char) * (size + 1));
    size = 0;
    while(path[tail] != '/')
    {
        str[size++] = path[tail--];
    }
    str[size] = '\0';
    for(i = 0, j = size - 1; i < j; ++i,--j)
    {
        char tmp = str[i];
        str[i] = str[j];
        str[j] = tmp;
    }
    return str;
}

void printLine2(struct stat* pstat)
{
    printf("  Size: %-10ld\t",pstat->st_size);
    printf("Blocks: %-10ld ",pstat->st_blocks);
    printf("IO Block: %-6ld ",pstat->st_blksize);
    printf("directory");
    printf("\n");
}
void printLine3(struct stat* pstat)
{
    printf("Device: %lxh/%ldd\t",pstat->st_dev,pstat->st_dev);
    printf("Inode: %-10ld  ",pstat->st_ino);
    printf("Links: %ld",pstat->st_nlink);
    printf("\n");
}
void printLine4(struct stat* pstat)
{
    printf("Access: (%04o/",pstat->st_mode & 0777);
    printFileType(pstat);
    int mask = 0x100;
    int i;
    int j;
    for(i = 0; i < 3; ++i)
    {
        for(j = 0; j < 3; ++j)
        {
            if(mask & pstat->st_mode)
            {
                switch(j)
                {
                case 0:
                    printf("r");
                    break;
                case 1:
                    printf("w");
                    break;
                case 2:
                    printf("x");
                    break;
                }
            }
            else
            {
                printf("-");
            }
            mask >>= 1;
        }
    }
    printf(")  ");
    printf("Uid: (%5d/%8s)   ",pstat->st_uid,getpwuid(pstat->st_uid)->pw_name);
    printf("Gid: (%5d/%8s)",pstat->st_gid,getgrgid(pstat->st_gid)->gr_name);
    printf("\n");

}
void printFileType(struct stat* pstat)
{
    switch(pstat->st_mode & S_IFMT)
    {
    case S_IFSOCK:
        printf("s");
        break;
    case S_IFLNK:
        printf("l");
        break;
    case S_IFREG:
        printf("-");
        break;
    case S_IFBLK:
        printf("b");
        break;
    case S_IFDIR:
        printf("d");
        break;
    case S_IFCHR:
        printf("c");
        break;
    case S_IFIFO:
        printf("p");
        break;
    }

}
