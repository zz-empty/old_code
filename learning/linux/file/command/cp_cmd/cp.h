#pragma once
#define BUFFER_SIZE 1024
int copy_file(const char*, const char*);
int copy_dir(const char*, const char*);
int copy_file_to_dir(const char *src_file, const char *dest_dir);
int derectory_exists(const char *path);//check if the dest exist
void copy_file_data(int src_fd, int dest_fd);
