/*
============================================================================
Name : 28.c
Author : Rathod Nisha MT2023195
Description : Write a program to change the exiting message queue permission. (use msqid_ds structure)
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
    struct msqid_ds messageQueueInfo;
    int msgctlStatus;

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

    msgctlStatus = msgctl(queueIdentifier, IPC_STAT, &messageQueueInfo);

    if (msgctlStatus == -1)
    {
        perror("Error");
        _exit(0);
    }

    messageQueueInfo.msg_perm.mode = 0776;

    msgctlStatus = msgctl(queueIdentifier, IPC_SET, &messageQueueInfo);

    if (msgctlStatus == -1)
    {
        perror("Error");
        _exit(0);
    }
    return 0;
}
