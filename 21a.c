/*
============================================================================
Name : 21a.c
Author : Rathod Nisha MT2023195
Description : Write two programs so that both can communicate by FIFO -Use two way communications.
Date: 5th Oct, 2023.
============================================================================
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#include "./21.h"

void main()
{
    int readBytes, writeBytes;
    int fifoOneFD, fifoTwoFD;
    char data[100];

    init();

    fifoOneFD = open(fifoOneName, O_WRONLY);
    if (fifoOneFD == -1)
    {
        perror("Error while opening fifoOne");
        _exit(0);
    }

    fifoTwoFD = open(fifoTwoName, O_RDONLY);
    if (fifoOneFD == -1)
    {
        perror("Error while opening fifoTwo");
        _exit(0);
    }

    writeBytes = write(fifoOneFD, "I am here via fifo using 21a.c", 31);

    if (writeBytes == -1)
        perror("Error while writing to FIFO fifoOne!");

    close(fifoOneFD);

    readBytes = read(fifoTwoFD, &data, 100);

    if (readBytes == -1)
    {
        perror("Error while reading from FIFO fifoTwo!");
        _exit(0);
    }

    printf("From 21a.c: %s\n", data);

    close(fifoTwoFD);
}
