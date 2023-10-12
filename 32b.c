/*
============================================================================
Name : 32b.c
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
#include <sys/shm.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    key_t semKey;
    int semIdentifier;
    int semctlStatus;
    int semopStatus;

    key_t shmKey;
    int shmIdentifier;
    ssize_t shmSize = 20;
    char *shmPointer;

    union semun {
        int val;
    } semSet;

    semKey = ftok(".", 3321);
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

        semSet.val = 1;
        semctlStatus = semctl(semIdentifier, 0, SETVAL, semSet);
        if (semctlStatus == -1) {
            perror("Error");
            return 1;
        }
    }

    shmKey = ftok(".", 3322);
    if (shmKey == -1) {
        perror("Error");
        return 1;
    }

    shmIdentifier = shmget(shmKey, shmSize, IPC_CREAT | 0700);
    if (shmIdentifier == -1) {
        perror("Error");
        return 1;
    }

    shmPointer = shmat(shmIdentifier, (void *)0, 0);
    if (*shmPointer == -1) {
        perror("Error");
        return 1;
    }

    struct sembuf semOp;
    semOp.sem_num = 0;
    semOp.sem_flg = 0;

    printf("enter for lock in cs\n");
    getchar();

    semOp.sem_op = -1;
    semopStatus = semop(semIdentifier, &semOp, 1);
    if (semopStatus == -1) {
        perror("Error");
        return 1;
    }

    printf("cs is locked\n");
    printf("You are in critial section\n");

    printf("Data is written in shared memory\n");
    sprintf(shmPointer, "Hey we are critical");

    printf("enter for reading shared memory\n");
    getchar();

    printf("%s\n", shmPointer);

    printf("enter if you wanna exit\n");
    getchar();

    semOp.sem_op = 1;
    semopStatus = semop(semIdentifier, &semOp, 1);
    if (semopStatus == -1) {
        perror("Error");
        return 1;
    }

    printf("You are out of critical section\n");
    return 0;
}
