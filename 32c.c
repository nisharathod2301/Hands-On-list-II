/*
============================================================================
Name : 32c.c
Author : Rathod Nisha MT2023195
Description : Write a program to implement semaphore to protect any critical section.
 a. rewrite the ticket number creation program using semaphore
 b. protect shared memory from concurrent write access
 c. protect multiple pseudo resources ( may be two) using counting semaphore
 d. remove the created semaphore

Date: 7th Oct, 2023.
============================================================================
*/

#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    char *filename = "./data32c.txt";

    int fileDescriptor;
    ssize_t readBytes;
    off_t lseekOffset;
    char data[1000];

    key_t semKey;
    int semIdentifier;
    int semctlStatus;
    int semopStatus;

    union semun {
        int val;
    } semSet;

    fileDescriptor = open(filename, O_RDONLY);
    if (fileDescriptor == -1) {
        perror("Error");
        return 1;
    }

    semKey = ftok(".", 331);
    if (semKey == -1) {
        perror("Error");
        return 1;
    }

    semIdentifier = semget(semKey, 1, 0);
    if (semIdentifier == -1) {
        semIdentifier = semget(semKey, 1, IPC_CREAT | 0700);
        if (semIdentifier == -1) {
            perror("Error");
            return 1;
        }

        semSet.val = 2;
        semctlStatus = semctl(semIdentifier, 0, SETVAL, semSet);
        if (semctlStatus == -1) {
            perror("Error");
            return 1;
        }
    }

    struct sembuf semOp;
    semOp.sem_num = 0;
    semOp.sem_flg = IPC_NOWAIT;

    printf("enter to go inside cs\n");
    getchar();

    semOp.sem_op = -1;
    semopStatus = semop(semIdentifier, &semOp, 1);
    if (semopStatus == -1) {
        perror("Error");
        return 1;
    }

    
    printf("you are in cs now\n");

    readBytes = read(fileDescriptor, &data, 1000);
    if (readBytes == -1) {
        perror("Error");
        return 1;
    } else if (readBytes == 0) {
        printf("no data to read from\n");
    } else {
        printf("Data- %s\n", data);
    }

    printf("\nenter to exit\n");
    getchar();

    semOp.sem_op = 1;
    semopStatus = semop(semIdentifier, &semOp, 1);
    if (semopStatus == -1) {
        perror("Error");
        return 1;
    }

    close(fileDescriptor);

    return 0;
}
