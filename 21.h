/*
============================================================================
Name : 21.h
Author : Rathod Nisha MT2023195
Description : Write two programs so that both can communicate by FIFO -Use two way communications.
Date: 5th Oct, 2023.
============================================================================
*/

#include <errno.h>

char *fifoOneName = "./21_File1";
char *fifoTwoName = "./21_File2";

void init()
{
    int fifoOneStatus, fifoTwoStatus;

    fifoOneStatus = mkfifo(fifoOneName, S_IRWXU);
    if (!(errno == EEXIST || fifoOneStatus != -1))
        perror("Error while creating FIFO file fifoOne");

    fifoTwoStatus = mkfifo(fifoTwoName, S_IRWXU);
    if (!(errno == EEXIST || fifoTwoStatus != -1))
        perror("Error while creating FIFO file fifoTwo");
}

