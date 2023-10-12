/*
============================================================================
Name : 22b.c
Author : Rathod Nisha MT2023195
Description : Write a program to wait for data to be written into FIFO within 10 seconds, use select system call with FIFO.
Date: 5th Oct, 2023.
============================================================================
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#include "./22.h"

void main()
{
    int fileDescriptor, writeBytes;
    char data[100];

    fileDescriptor = open(fifoName, O_NONBLOCK | O_WRONLY);

    if (fileDescriptor == -1)
    {
        perror("Error");
        _exit(0);
    }

    writeBytes = write(fileDescriptor, "What are you up to?", 19);

    if (writeBytes == -1)
        perror("Error");

    close(fileDescriptor);
}



