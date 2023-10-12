/*
============================================================================
Name : 22a.c
Author : Rathod Nisha MT2023195
Description : Write a program to wait for data to be written into FIFO within 10 seconds, use select system call with FIFO.
Date: 5th Oct, 2023.
============================================================================
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>

#include "./22.h"

void main()
{
    int fileDescriptor, readBytes;
    char data[100];

    fd_set readFDSet;
    struct timeval timer;
    int selectStatus;

    init();

    fileDescriptor = open(fifoName, O_NONBLOCK | O_RDONLY);

    if (fileDescriptor == -1)
    {
        perror("Error");
        _exit(0);
    }

    FD_ZERO(&readFDSet);
    FD_SET(fileDescriptor, &readFDSet);

    timer.tv_sec = 10;
    timer.tv_usec = 0;

    selectStatus = select(fileDescriptor + 1, &readFDSet, NULL, NULL, &timer);

    if (selectStatus == -1)
        perror("Error");
    else if (selectStatus)
    {
        readBytes = read(fileDescriptor, &data, 100);

        if (readBytes == -1)
            perror("Error");
        else
            printf("From FIFO: %s\n", data);
    }
    else
        printf("Sedn in 10 secs\n");

    close(fileDescriptor);
}
