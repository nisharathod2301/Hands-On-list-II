/*
============================================================================
Name : 23.c
Author : Rathod Nisha MT2023195
Description : Write a program to print the maximum number of files can be opened within a process and size of a pipe (circular buffer).
Date: 6th Oct, 2023.
============================================================================
*/
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>

int main()
{
    int fifoStatus;
    long maxFiles;
    long sizeOfPipe;

    char *fifoName = "23";
    fifoStatus = mkfifo(fifoName, S_IRWXU);

    if (!(errno == EEXIST || fifoStatus != -1))
        perror("Error");
    else
    {
        maxFiles = sysconf(_SC_OPEN_MAX);

        if (maxFiles == -1)
            perror("Error");
        else
            printf("Max files can be open is %ld\n", maxFiles);

        sizeOfPipe = pathconf(fifoName, _PC_PIPE_BUF);

        if (sizeOfPipe == -1)
            perror("Error");
        else
            printf("size of pipe is %ld\n", sizeOfPipe);
    }
    return 0;
}
