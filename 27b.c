/*
============================================================================
Name : 27b.c
Author : Rathod Nisha MT2023195
Description : Write a program to receive messages from the message queue.
 b. with IPC_NOWAIT as a flag
Date: 6th Oct, 2023.
============================================================================
*/
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    key_t queueKey;
    int queueIdentifier;
    ssize_t messageSize;

    struct msgbuf
    {
        long mtype;
        int someNumber;
    } data;

    queueKey = ftok(".", 1);

    if (queueKey == -1)
    {
        perror("Error");
        _exit(0);
    }

    queueIdentifier = msgget(queueKey, IPC_CREAT | 0700);

    if (queueIdentifier == -1)
    {
        perror("Error");
        _exit(0);
    }

    data.mtype = 1;

    messageSize = msgrcv(queueIdentifier, &data, sizeof(data), data.mtype, IPC_NOWAIT);

    if (messageSize == -1)
    {
        perror("Error");
        _exit(0);
    }

    printf("message recived is %d\n", data.someNumber);
    return 0;
}

