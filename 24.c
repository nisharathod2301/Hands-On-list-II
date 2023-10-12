/*
============================================================================
Name : 24.c
Author : Rathod Nisha MT2023195
Description : Write a program to create a message queue and print the key and message queue id.

Date: 6th Oct, 2023.
============================================================================
*/
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main()
{
    key_t queueKey;
    int queueIdentifier;

    queueKey = ftok(".", 1);

    if (queueKey == -1)
    {
        perror("Error");
        _exit(0);
    }

    queueIdentifier = msgget(queueKey, IPC_CREAT | IPC_EXCL | 0700);
    if (queueIdentifier == -1)
    {
        perror("Error");
        _exit(0);
    }

    printf("Key: %d\n", queueKey);
    printf("message queue id is %d\n", queueIdentifier);
    return 0;
}
