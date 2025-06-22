#include <func.h>
#include "cp.h"


int copy_dir(const char *src, const char *dst){
	DIR *dir;  
    struct dirent *entry;  
    char src_path[1024];  
    char dst_path[1024];  
  
    dir = opendir(src);
    mkdir(dst, 0777); 
  
    while ((entry = readdir(dir)) != NULL) {  
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {  
            continue;  
        }  
  
        snprintf(src_path, sizeof(src_path), "%s/%s", src, entry->d_name);  
        snprintf(dst_path, sizeof(dst_path), "%s/%s", dst, entry->d_name);  
  
        struct stat st;  
        if (stat(src_path, &st) == -1) {  
            perror("stat");  
            exit(EXIT_FAILURE);  
        }  
  
        if (S_ISDIR(st.st_mode)) {  
            copy_dir(src_path, dst_path);  
        } else {  
            copy_file(src_path, dst_path);  
        }  
    }  
  
    closedir(dir);  
    return 0;
}

int copy_file(const char *src, const char *dest) {
    //check src if exist
    int ret;
    struct stat src_stat;
    ret = stat(src, &src_stat); 
    ERROR_CHECK(ret, -1, "stat_src");

    struct stat dest_stat;
    stat(dest, &dest_stat);

    if (S_ISDIR(dest_stat.st_mode)) {
        copy_file_to_dir(src, dest);
    }
    else {
        //open srcfile
        int src_fd = open(src, O_RDONLY);
        ERROR_CHECK(src_fd, -1, "open_src");

        //create destfile
        int dest_fd = open(dest, O_WRONLY|O_CREAT, 0600);
        ERROR_CHECK(dest_fd, -1, "open_dest");

        //copy data
        copy_file_data(src_fd, dest_fd);

        close(src_fd);
        close(dest_fd);
    }
    printf("File copyed successful!\n");
    return 0;
}

int derectory_exists(const char *path) {
    struct stat stmp = {0};
    if (stat(path, &stmp) == 0 && S_ISDIR(stmp.st_mode)) {
        return 1;
    }
    return 0;
}

void copy_file_data(int src_fd, int dest_fd) {
    char buf[BUFFER_SIZE] = {0};
    int nread;

    //while((nread = read(src_fd, buf, sizeof(buf))) > 0) {
    while (1) {
        if ((nread = read(src_fd, buf, sizeof(buf))) == -1) {
            fprintf(stderr, "read error");
            exit(EXIT_FAILURE);
        }
        if (0 == nread) {
            break;
        }
        write(dest_fd, buf, nread);
    }
}

int copy_file_to_dir(const char *src, const char *dest){
    //check src if exist
    int ret;
    struct stat src_stat;
    ret = stat(src, &src_stat); 
    ERROR_CHECK(ret, -1, "stat");

    //check dir if exist
    ret = derectory_exists(dest);
    if (0 == ret) {
        fprintf(stderr, "dest does not exist!\n");
        return -1;
    }

    //build dest complete path
    char dest_file[BUFFER_SIZE] = {0};
    sprintf(dest_file, "%s/%s%s", dest, src, "\0");

    //open srcfile destfile
    int src_fd = open(src, O_RDONLY);
    ERROR_CHECK(src_fd, -1, "open_src");
    int dest_fd = open(dest_file, O_WRONLY|O_CREAT, 0600);
    ERROR_CHECK(dest_fd, -1, "open_dest");

    //copy
    copy_file_data(src_fd, dest_fd);

    close(src_fd);
    close(dest_fd);
    return 0;
}
