/**
 * @author:  7e12
 * @date:    19 May 2021
 * @version: v1.0.1
**/

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#define ARRAY_SIZE 64

int main(void) {
    int read_fd, write_fd;
    char read_array[ARRAY_SIZE], write_array[ARRAY_SIZE];

    // Create a fifo to transfer data from program 1 to program 2
    mkfifo("fifo_f1t2", 0666);

    // Create parent and child processes using fork()
    if (fork()) {
        while (1) {
            /* Parent process */
            // Open FIFO for writing only
            write_fd = open("fifo_f1t2", O_WRONLY);
            fgets(write_array, ARRAY_SIZE, stdin);
            write(write_fd, write_array, strlen(write_array) + 1);
            close(write_fd);
        }
    } else {
        while (1) {
            /* Child process */
            // Open FIFO for reading only
            read_fd = open("fifo_f2t1", O_RDONLY);
            read(read_fd, read_array, sizeof(read_array));
            printf("[p2] %s", read_array);
            close(read_fd);
        }
    }

    return 0;
}
