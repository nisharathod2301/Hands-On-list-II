/*
============================================================================
Name : 22.h
Author : Rathod Nisha MT2023195
Description : Write a program to wait for data to be written into FIFO within 10 seconds, use select system call with FIFO.
Date: 5th Oct, 2023.
============================================================================
*/


#include <errno.h>
char *fifoName = "./22_File";

void init()
{
    int fifoStatus;

    fifoStatus = mkfifo(fifoName, S_IRWXU);
    if (!(errno == EEXIST || fifoStatus != -1))
        perror("Error");
}
