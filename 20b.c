/*
============================================================================
Name : 20.c
Author : Rathod Nisha MT2023195
Description : Write two programs so that both can communicate by FIFO -Use one way communication.
Date: 5th Oct, 2023.
============================================================================
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

void main()
{
    int fileDescriptor;
    char *fifoFile = "./20";
    int readBytes;
    char data[100];

    fileDescriptor = open(fifoFile, O_RDONLY);

    if (fileDescriptor == -1)
        perror("Error");
    else
    {
        readBytes = read(fileDescriptor, data, 100);
        if (readBytes == -1)
            perror("Error");
        else
        {
            printf("bytes: %d\n", readBytes);
            printf("fromFIFO  - %s\n", data);
        }
        close(fileDescriptor);
    }
}
