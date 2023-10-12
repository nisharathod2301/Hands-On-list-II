/*
============================================================================
Name : 19.c
Author : Rathod Nisha MT2023195
Description : Create a FIFO file by
 a. mknod command
 b. mkfifo command
 c. use strace command to find out, which command (mknod or mkfifo) is better. c. mknod system call
Date: 5th Oct, 2023.
============================================================================
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    char *mkfifoName = "./mymkfifo";
    char *mknodName = "./mymknod-fifo";
    
    int mkfifo_status, mknod_status;

    mkfifo_status = mkfifo(mkfifoName, S_IRWXU);

    if (mkfifo_status == -1)
    {
        perror("Error");
        return 1;
    }
    else
    {
        printf("Successfully created\n");
    }

    mknod_status = mknod(mknodName, S_IFIFO | S_IRWXU, 0);

    if (mknod_status == -1)
    {
        perror("Error");
        return 1;
    }
    else
    {
        printf("Successfully created\n");
    }

    return 0;
}
