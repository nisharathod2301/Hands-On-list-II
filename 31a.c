/*
============================================================================
Name : 31a.c
Author : Rathod Nisha MT2023195
Description : Write a program to create a semaphore and initialize value to the semaphore
 a. create a binary semaphore
 b. create a counting semaphore

Date: 6th Oct, 2023.
============================================================================
*/
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    key_t semKey;
    int semIdentifier;
    int semctlStatus;

    union semun {
        int val;
    } semSet;

    semKey = ftok(".", 2);
    if (semKey == -1) {
        perror("Error");
        return 1;
    }

    semIdentifier = semget(semKey, 1, IPC_CREAT | 0777);
    if (semIdentifier == -1) {
        perror("Error creating semaphore");
        return 1;
    } else {
        printf("Semaphore created with identifier: %d\n", semIdentifier);
    }

    semSet.val = 1;

    semctlStatus = semctl(semIdentifier, 0, SETVAL, semSet);

    if (semctlStatus == -1) {
        perror("Error");
        return 1;
    }

    return 0;
}
