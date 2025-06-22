#include <func.h>
#include "cp.h"

int main(int argc, char *argv[]){
    ARGS_CHECK(argc, 3);

    //copy_file(argv[1], argv[2]);
    //copy_file_to_dir(argv[1], argv[2]);
    
    struct stat src_dest;
    if (-1 == stat(argv[1], &src_dest)){
        perror("Error stating source");
        exit(EXIT_FAILURE);
    }
    if (S_ISDIR(src_dest.st_mode)) {
        copy_dir(argv[1], argv[2]);
    }
    else if (S_ISREG(src_dest.st_mode)) {
        copy_file(argv[1], argv[2]);
    }
    else {
        fprintf(stderr, "Unsupported file wctype_t\n");
        exit(EXIT_FAILURE);
    }
    return 0;
}
