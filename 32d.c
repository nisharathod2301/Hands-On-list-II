/*
============================================================================
Name : 32d.c
Author : Rathod Nisha MT2023195
Description : Write a program to implement semaphore to protect any critical section.
 a. rewrite the ticket number creation program using semaphore
 b. protect shared memory from concurrent write access
 c. protect multiple pseudo resources ( may be two) using counting semaphore
 d. remove the created semaphore

Date: 7th Oct, 2023.
============================================================================
*/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    key_t semKey;
    int semIdentifier;
    int semctlStatus;

    semKey = ftok(".", 1);
    if (semKey == -1) {
        perror("Error");
        return 0;
    }

    semIdentifier = semget(semKey, 1, IPC_CREAT | 0777);
    if (semIdentifier == -1) {
        perror("Error");
        return 0;
    }

    printf("enter to remove the created semaphore\n");
    getchar();

    semctlStatus = semctl(semIdentifier, 0, IPC_RMID);

    if (semctlStatus == -1) {
        perror("Error");
        return 0;
    }
    else{
        printf("removed sucessfully");
    }
    return 0;
}
