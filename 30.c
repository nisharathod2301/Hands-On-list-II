/*
============================================================================
Name : 30.c
Author : Rathod Nisha MT2023195
Description : Write a program to create a shared memory.
 a. write some data to the shared memory
 b. attach with O_RDONLY and check whether you are able to overwrite.
 c. detach the shared memory
 d. remove the shared memory
Date: 6th Oct, 2023.
============================================================================
*/
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    key_t shmKey;
    int shmIdentifier;
    ssize_t shmSize = 20;
    char *shmPointer, *rdOnlyShmPointer;

    shmKey = ftok(".", 1);

    if (shmKey == -1)
    {
        perror("Error");
        _exit(0);
    }

    shmIdentifier = shmget(shmKey, shmSize, IPC_CREAT | 0700);

    if (shmIdentifier == -1)
    {
        perror("Error");
        _exit(0);
    }

    shmPointer = shmat(shmIdentifier, (void *)0, 0);

    if (*shmPointer == -1)
    {
        perror("Error");
        _exit(0);
    }

    printf("any key press to go and write in shared memory\n");
    getchar();

    sprintf(shmPointer, "This is a message");

    printf("any key press to go and read in shared memory\n");
    getchar();

    printf("from shared memory- %s\n", shmPointer);

    rdOnlyShmPointer = shmat(shmIdentifier, (void *)0, SHM_RDONLY);
    if (*rdOnlyShmPointer == -1)
    {
        perror("Error");
        _exit(0);
    }
    fflush(stdin);
    printf("any key to read from the shared memory!\n");
    getchar();

    printf("from shared memory- %s\n", rdOnlyShmPointer);

    printf("detaching the shared memory\n");
    shmdt(shmPointer);
    shmdt(rdOnlyShmPointer);

    printf("press any key to remove the shared memory\n");
    getchar();

    shmctl(shmIdentifier, IPC_RMID, NULL);
    return 0;
}
