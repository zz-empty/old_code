#include <func.h>
char *getDirname(char *path); //get dirname from path
char *getFilename(char *path); //get filename from path
void printFileType(struct stat *pstat);
void printLine_2(struct stat *pstat);
void printLine_3(struct stat *pstat);
void printLine_4(struct stat *pstat);
void printLine_5(struct stat *pstat);
void printLine_6(struct stat *pstat);
void printLine_7(struct stat *pstat);
void printTime(struct tm *ptm);

int main(int argc, char *argv[])
{
    ARGS_CHECK(argc, 2);

    //get file info
    struct stat statbuf;
    int ret = stat(argv[1], &statbuf);
    ERROR_CHECK(ret, -1, "stat");


    //get filename
    char *name;
    if ((statbuf.st_mode & S_IFMT) == S_IFDIR) {
        char *path;
        chdir(argv[1]);
        path = getcwd(NULL, 0);
        name = getDirname(path);
    }
    else {
        name = getFilename(argv[1]);
    }

    //print first line
    printf("%7s '%s'", "File:", name);
    printf("\n");
    //print second line
    printLine_2(&statbuf);
    //print third line
    printLine_3(&statbuf);
    //print forth line
    printLine_4(&statbuf);
    //print fifth line
    printLine_5(&statbuf);
    //print sixth line
    printLine_6(&statbuf);
    //print seventh line
    printLine_7(&statbuf);
    //print eighth line
    printf("%7s -\n", "Birth:");
      
    return 0;
}

void printTime(struct tm *tmp){
    const char *mon[] = {"01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12"};
    printf(" %d-%2s-%2d", tmp->tm_year + 1900, mon[tmp->tm_mon], tmp->tm_mday);

    const char *format[] = {
        "00", "01", "02", "03", "04", "05", "06",
        "07", "08", "09"};
    if (tmp->tm_hour <= 1) {
            printf(" %2s-%2d-%2d", format[tmp->tm_hour + 8], tmp->tm_min, tmp->tm_sec);
    }
    else {
            printf(" %2d-%2d-%2d", tmp->tm_hour + 8, tmp->tm_min, tmp->tm_sec);
    }
}

void printLine_7(struct stat *pstat){
    printf("%7s", "Change:");
    struct tm *tmp;
    tmp = gmtime(&pstat->st_atime);
    printTime(tmp);
    printf("\n");
}
void printLine_6(struct stat *pstat){
    printf("%7s", "Modify:");
    struct tm *tmp;
    tmp = gmtime(&pstat->st_mtime);
    printTime(tmp);
    printf("\n");
}
void printLine_5(struct stat *pstat){
    printf("%7s", "Access:");
    struct tm *tmp;
    tmp = gmtime(&pstat->st_atime);
    printTime(tmp);
    printf("\n");
}
void printLine_4(struct stat *pstat){
    //Access Uid gid
    printf("%7s (%04o/", "Access:", pstat->st_mode & 0777);
    printFileType(pstat);
    //print ugo's mode
    int mask = 0x100; //start from user's r
    int i, j;
    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            if (mask & pstat->st_mode) {
                switch (j) {
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
            else {
                printf("-");
            }
            mask >>= 1;
        }
    }
    printf(")  ");

    struct passwd *utmp;
    utmp = getpwuid(pstat->st_uid);
    printf("%s (%5d/%8s)   ", "Uid:", pstat->st_uid, utmp->pw_name);

    struct group *gtmp;
    gtmp = getgrgid(pstat->st_gid);
    printf("%s (%5d/%8s)", "Gid:", pstat->st_gid, gtmp->gr_name);
    printf("\n");
}

void printLine_3(struct stat *pstat){
    //Device Inode Links
    printf("%7s %lxh/%ldd\t", "Device:", pstat->st_dev, pstat->st_dev);
    printf("%s %-12d", "Inode:", pstat->st_ino);
    printf("%s %d", "Links:", pstat->st_nlink);
    printf("\n");
}
void printLine_2(struct stat *pstat){
    //size blocks ioblock type
    printf("%7s %-10ld\t", "Size:", pstat->st_size);
    printf("%s %-11ld", "Blocks:", pstat->st_blocks);
    printf("%s %-7ld", "IO Block:", pstat->st_blksize);

    mode_t mode = pstat->st_mode;
    if (mode & S_IFDIR) {
        printf("directory");
    }
    else if (mode & S_IFREG) {
        printf("regular file");
    }
    else if (mode & S_IFIFO) {
        printf("fifo");
    }
    else if (mode & S_IFCHR) {
        printf("character device");
    }
    else if (mode & S_IFBLK) {
        printf("block device");
    }
    else if (mode & S_IFLNK) {
        printf("symbolic link");
    }
    else if (mode & S_IFSOCK) {
        printf("socket");
    }
    printf("\n");
}
char *getDirname(char *path){
    //get length of filename
    int tail = strlen(path) - 1;
    int size = 0;
    int i;
    for (i = tail; path[i] != '/'; --i) {
        size++;
    }
    
    //get everychar of filename
    char *str = (char*)malloc(sizeof(char) * (size+1));
    i = 0;
    while (path[tail] != '/') {
        str[i++] = path[tail--];
    }
    str[i] = '\0';

    //adjust str to rightname
    int j;
    for (i = 0, j = size - 1; i < j; ++i, --j) {
        char tmp = str[i];
        str[i] = str[j];
        str[j] = tmp;
    }

    return str;
}
char *getFilename(char *path) {
   //get size of filename
   int len = strlen(path);
   int size = 0;
   int i;
   int j;
   for (i = len - 1; i != -1 && path[i] != '/'; --i) {
       size++;
   }

   //set str to obtain filename
   char *str = (char*)malloc(sizeof(char) * (size + 1));
   str[size] = '\0';
   for (i = size - 1, j = len - 1; i != -1 && path[i] != '/'; --i, --j) {
       str[i] = path[j];
   }

   return str;
}

void printFileType(struct stat *pstat) {
    switch(pstat->st_mode & S_IFMT) {
    case S_IFREG:
        printf("-");
        break;
    case S_IFDIR:
        printf("d");
        break;
    case S_IFSOCK:
        printf("s");
        break;
    case S_IFIFO:
        printf("p");
        break;
    case S_IFLNK:
        printf("l");
        break;
    case S_IFCHR:
        printf("c");
        break;
    case S_IFBLK:
        printf("b");
        break;
    }
}
