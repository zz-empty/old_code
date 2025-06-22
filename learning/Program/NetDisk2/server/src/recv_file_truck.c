#include "head.h"
#include "func.h"

//获取文件大小
int get_filesize(char *filename)
{
    //遍历此目录下的所有文件
    int size = 0;
    DIR *dirp = opendir("./");
    struct dirent *pcur;
    while ((pcur = readdir(dirp)) != NULL) {
        if (!strcmp(filename, pcur->d_name)) {
            struct stat st;
            stat(filename, &st);
            printf("有这个文件!\n");
            printf("this file size: %ld\n", st.st_size);
            size = st.st_size;
            break;
        }
    }

    closedir(dirp);
    return size;
}

//小于100M的接收方式
int recv_file_truck(int fd_socket, char *filename)
{
    Truck_t truck;
    int ret = -1;

    //断点续传
    //在本地找是否有这个文件, 有发送文件大小，没有发送0
    off_t offset = get_filesize(filename);
    send(fd_socket, &offset, sizeof(int), 0);
    printf("offset = %ld\n", offset);

    //打开文件，并偏移文件指针
    int fd_file = open(filename, O_WRONLY|O_CREAT, 0666);
    EXIT_CHECK(fd_file, -1, "open");
    if (offset) {
        lseek(fd_file, offset, SEEK_SET);
    }

    //循环接收文件内容
    while (1) {
        //重置小货车
        memset(&truck, 0, sizeof(truck));
        //先接数据长度
        recv(fd_socket, &truck._data_len, sizeof(int), 0);
        printf("len = %d\n", truck._data_len);
        if (0 == truck._data_len) {
            //传输完毕
            printf("Transfer Finish!\n");
            //关闭文件
            close(fd_file);
            return 0;
        }

        //根据数据长度接收数据内容
        //防止发送方发的慢，导致接收缓冲区将车厢当成车头，设置recv参数为MSG_WAITALL
        ret = recv(fd_socket, truck._data, truck._data_len, MSG_WAITALL);
        if (0 == ret) {
            //对端异常断开
            close(fd_file);
            return -2;
        }

        //将接收数据写入文件
        write(fd_file, truck._data, ret);
    }
}
