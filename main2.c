/**
 * Author:  7e12
 * Date:    19 May 2021
 * Version: v1.0.0
**/

// This side: read first, then write

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#define ARRAY_SIZE 64

int main(void) {
    int fd;
    char writeArr[ARRAY_SIZE], readArr[ARRAY_SIZE];
    char *mFIFO = "/tmp/myfifo";

    while (1)
    {
        // Open FIFO for reading only
        fd = open(mFIFO, O_RDONLY);
        read(fd, readArr, ARRAY_SIZE);
        printf("[user]: %s", readArr);
        close(fd);

        // Open FIFO for writing only
        fd = open(mFIFO, O_WRONLY);
        printf("[you]: ");
        fgets(writeArr, ARRAY_SIZE, stdin);
        write(fd, writeArr, strlen(writeArr) + 1);
        close(fd);
    }

    return 0;
}
