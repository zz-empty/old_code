#include <func.h>
int fcnt, dcnt;

int dfsPrint(char *path, int width);

int main(int argc, char *argv[])
{
    ARGS_CHECK(argc, 2);
    printf("%s\n", argv[1]);

    dfsPrint(argv[1], 4);
    printf("\n%d directories, %d files\n", dcnt, fcnt);
    return 0;
}

int dfsPrint(char *path, int width){
    DIR *dirp = opendir(path);
    ERROR_CHECK(dirp, NULL, "opendir");

    struct dirent *pdirent;
    char newPath[1024] = {0};

    while((pdirent = readdir(dirp)) != NULL) {
        memset(newPath, 0, sizeof(newPath));
        if (strcmp(pdirent->d_name, ".") == 0 ||
            strcmp(pdirent->d_name, "..") == 0) {
            continue;
        }
        if (pdirent->d_type == DT_DIR) {
            dcnt++;
        }
        else if (pdirent->d_type == DT_REG) {
            fcnt++;
        }

        int i;
        for (i = 0; i < width - 4; ++i) {
            printf("%s", " ");
        }
        for (i = 0; i < 4; ++i) {
            printf("%s", "-");
        }
        printf("%s\n", pdirent->d_name);

        if(pdirent->d_type == DT_DIR) {
            sprintf(newPath, "%s/%s", path, pdirent->d_name);
            dfsPrint(newPath, width+4);
        }
    }

    closedir(dirp);
    return 0;
}
