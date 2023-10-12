
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
    int fifoStatus;
    char data[] = "hey there";
    int fileDescriptor;
    char *fifoFile = "./20";
    int writeBytes;

    fifoStatus = mkfifo(fifoFile, S_IRWXU);

    if (fifoStatus == -1)
        perror("Error");
    fileDescriptor = open(fifoFile, O_WRONLY);
    if (fileDescriptor == -1)
        perror("Error");
    else
    {
        writeBytes = write(fileDescriptor, &data, sizeof(data));
        if (writeBytes == -1)
            perror("Error");
        close(fileDescriptor);
    }
}
