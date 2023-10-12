/*
============================================================================
Name : 32a.c
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
    char *ticketFile = "./ticket.txt";
    int fileDescriptor, readBytes, writeBytes;
    off_t lseekOffset;
    int data;

    key_t semKey;
    int semIdentifier;
    int semctlStatus;
    int semopStatus;

    union semun {
        int val;
    } semSet;

    fileDescriptor = open(ticketFile, O_CREAT | O_RDWR, S_IRWXU);
    if (fileDescriptor == -1) {
        perror("Error opening the ticket file");
        return 1;
    }

    semKey = ftok(".", 331);
    if (semKey == -1) {
        perror("Error computing key");
        return 1;
    }

    semIdentifier = semget(semKey, 1, 0);
    if (semIdentifier == -1) {
        semIdentifier = semget(semKey, 1, IPC_CREAT | 0700);
        if (semIdentifier == -1) {
            perror("Error creating semaphore");
            return 1;
        }

        semSet.val = 1;
        semctlStatus = semctl(semIdentifier, 0, SETVAL, semSet);
        if (semctlStatus == -1) {
            perror("Error initializing a binary semaphore");
            return 1;
        }
    }

    struct sembuf semOp;
    semOp.sem_num = 0;
    semOp.sem_flg = 0;

    printf("Press enter to obtain a lock on the critical section\n");
    getchar();

    semOp.sem_op = -1;
    semopStatus = semop(semIdentifier, &semOp, 1);
    if (semopStatus == -1) {
        perror("Error operating on semaphore");
        return 1;
    }

    printf("Obtained a lock on the critical section\n");
    printf("Now entering the critical section\n");

    readBytes = read(fileDescriptor, &data, sizeof(data));
    if (readBytes == -1) {
        perror("Error reading from the ticket file");
        return 1;
    } else if (readBytes == 0) {
        data = 1;
    } else {
        data += 1;
        lseekOffset = lseek(fileDescriptor, 0, SEEK_SET);
        if (lseekOffset == -1) {
            perror("Error seeking");
            return 1;
        }
    }

    writeBytes = write(fileDescriptor, &data, sizeof(data));
    if (writeBytes == -1) {
        perror("Error writing to the ticket file");
        return 1;
    }

    printf("Your ticket number is: %d\n", data);
    printf("Press enter to exit from the critical section\n");
    getchar();

    semOp.sem_op = 1;
    semopStatus = semop(semIdentifier, &semOp, 1);
    if (semopStatus == -1) {
        perror("Error operating on semaphore");
        return 1;
    }
    close(fileDescriptor);

    return 0;
}
