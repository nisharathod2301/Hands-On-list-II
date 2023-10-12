/*
============================================================================
Name : 15.c
Author : Rathod Nisha MT2023195
Description : Write a simple program to send some data from parent to the child process.

Date: 5th Oct, 2023.
============================================================================
*/
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

void main()
{
    pid_t childPid;
    int pipefd[2];
    int pipeStatus;
    int readBytes, writeBytes;

    char *writeBuffer = "Hey kiddo", *readBuffer;

    pipeStatus = pipe(pipefd);

    if (pipeStatus == -1)
        perror("Error while creating pipe!");
    else
    {
        printf("Pipe created \n");
        childPid = fork();
        if (childPid == -1)
            perror("Error in fork");
        else if (childPid == 0)
        {
            readBytes = read(pipefd[0], &readBuffer, sizeof(writeBuffer));
            if (readBytes == -1)
                perror("Error in reading\n");
            else
                printf("Data from parent: %s\n", readBuffer);
        }
        else
        {
            writeBytes = write(pipefd[1], &writeBuffer, sizeof(writeBuffer));
            if (writeBytes == -1)
                perror("Error while writing");
        }
    }
}
