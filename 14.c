/*
============================================================================
Name : 14.c
Author : Rathod Nisha MT2023195
Description : Write a simple program to create a pipe, write to the pipe, read from pipe and display on the monitor.

Date: 5th Oct, 2023.
============================================================================
*/
#include <unistd.h>
#include <stdio.h>
void main()
{
    int pipefd[2]; //store the file descriptors of the pipe. pipefd[0] is for reading, and pipefd[1] is for writing.
    char *writeBuffer = "This was written in past.";
    char *readBuffer;
    int pipeStatus;
    int readBytes, writeBytes;
    pipeStatus = pipe(pipefd);

    if (pipeStatus == -1)
        perror("Error while creating the pipe! ");
    else
    {
        printf("writing...\n");
        writeBytes = write(pipefd[1], &writeBuffer, sizeof(writeBuffer));
        if (writeBytes == -1)
            perror("Error while writing to pipe!");
        else
        {
            printf("reading from pipe...\n");
            readBytes = read(pipefd[0], &readBuffer, writeBytes);
            if (readBytes == -1)
                perror("Error while reading from pipe!");
            else
                printf("From pipe- %s\n", readBuffer);
        }
    }
}
