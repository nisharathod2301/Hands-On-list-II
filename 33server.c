/*
============================================================================
Name : 33server.c
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
    int socketFileDescriptor, connectionFileDescriptor;
    int bindStatus, listenStatus, clientSize;

    struct sockaddr_in address, client;
    ssize_t readBytes, writeBytes;
    char dataFromClient[100];

    socketFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFileDescriptor == -1) {
        perror("Error");
        return 0;
    }
    printf("socked created\n");

    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_family = AF_INET;
    address.sin_port = htons(8080);

    bindStatus = bind(socketFileDescriptor, (struct sockaddr *)&address, sizeof(address));
    if (bindStatus == -1) {
        perror("Error");
        return 0;
    }
    printf("sucessfully connected\n");

    listenStatus = listen(socketFileDescriptor, 2);
    if (listenStatus == -1) {
        perror("Error");
        return 0;
    }
    printf("server is listening...\n");

    clientSize = (int)sizeof(client);
    connectionFileDescriptor = accept(socketFileDescriptor, (struct sockaddr *)&client, &clientSize);
    if (connectionFileDescriptor == -1) {
        perror("Error");
    } else {
        // Server - Client communication

        writeBytes = write(connectionFileDescriptor, "Hello clinet", 15);
        if (writeBytes == -1) {
            perror("Error");
        } else {
            printf("Message sent!\n");
        }

        readBytes = read(connectionFileDescriptor, dataFromClient, 100);
        if (readBytes == -1) {
            perror("Error");
        } else {
            printf("From client -  %s\n", dataFromClient);
        }
    }

    close(connectionFileDescriptor);
    close(socketFileDescriptor);

    return 0;
}
