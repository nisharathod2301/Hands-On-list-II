/*
============================================================================
Name : 25.c
Author : Rathod Nisha MT2023195
Description : Write a program to print a message queue's (use msqid_ds and ipc_perm structures)
 a. access permission
 b. uid, gid
 c. time of last message sent and received
 d. time of last change in the message queue
 d. size of the queue
 f. number of messages in the queue
 g. maximum number of bytes allowed
 h. pid of the msgsnd and msgrcv
 
Date: 6th Oct, 2023.
============================================================================
*/
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
//Note: I am not able to find d. that is size of queue, because there is no member named '__msg_cbytes' in macOs
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

    printf("Key: %d\n", queueKey);
    printf("message queue id is %d\n", queueIdentifier);

    msgctlStatus = msgctl(queueIdentifier, IPC_STAT, &messageQueueInfo);

    if (msgctlStatus == -1)
    {
        perror("Error");
        _exit(0);
    }

    printf("access permission- %od\n", messageQueueInfo.msg_perm.mode);
    printf("uid- %d\n", messageQueueInfo.msg_perm.uid);
    printf("gid- %d\n", messageQueueInfo.msg_perm.gid);
    printf("time of last message sent- %ld\n", messageQueueInfo.msg_stime);
    printf("time of last message recieved- %ld\n", messageQueueInfo.msg_rtime);
    printf("number of messages in the queue- %ld\n", messageQueueInfo.msg_qnum);
    printf("maximum number of bytes allowed- %ld\n", messageQueueInfo.msg_qbytes);
    printf("pid of the msgsnd- %d\n", messageQueueInfo.msg_lspid);
    printf("pid of the msgrcv- %d\n", messageQueueInfo.msg_lrpid);
    return 0;
}
