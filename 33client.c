/*
============================================================================
Name : 33client.c
Author : Rathod Nisha MT2023195
Description : Write a program to communicate between two machines using socket.
Date: 7th Oct, 2023.
============================================================================
*/
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    int socketFileDescriptor;
    int connectStatus;

    struct sockaddr_in address;
    ssize_t readBytes, writeBytes;
    char dataFromServer[100];

    socketFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFileDescriptor == -1) {
        perror("Error");
        return 0;
    }
    printf("socket created at client\n");

    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_family = AF_INET;
    address.sin_port = htons(8080);

    connectStatus = connect(socketFileDescriptor, (struct sockaddr *)&address, sizeof(address));
    if (connectStatus == -1) {
        perror("Error");
        return 0;
    }
    printf("connection sucessful\n");

    readBytes = read(socketFileDescriptor, dataFromServer, 100);
    if (readBytes == -1) {
        perror("Error");
    } else {
        printf("Frrom server - %s\n", dataFromServer);
    }

    writeBytes = write(socketFileDescriptor, "Hey server guy", 15);
    if (writeBytes == -1) {
        perror("Error");
    } else {
        printf("Message sent!\n");
    }

    close(socketFileDescriptor);

    return 0;
}
