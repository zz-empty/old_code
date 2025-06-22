#include <func.h>

int main(int argc, char *argv[])
{
    ARGS_CHECK(argc, 2);
    DIR *dirp = opendir(argv[1]);

    struct dirent *pdirent;
    while((pdirent = readdir(dirp)) != NULL) {
        switch(pdirent->d_type){
        case DT_BLK:
            pdirent->d_type = 'b';
            break;
        case DT_CHR:
            pdirent->d_type = 'c';
            break;
        case DT_DIR:
            pdirent->d_type = 'd';
            break;
        case DT_LNK:
            pdirent->d_type = 'l';
            break;
        case DT_REG:
            pdirent->d_type = 'f';
            break;
        case DT_FIFO:
            pdirent->d_type = 'p';
            break;
        case DT_SOCK:
            pdirent->d_type = 's';
            break;
        }
        printf("ino = %ld, reclen = %d, type = %c, name = %s\n",
               pdirent->d_ino,
               pdirent->d_reclen,
               pdirent->d_type,
               pdirent->d_name);
    }
    
    closedir(dirp);
    return 0;
}

