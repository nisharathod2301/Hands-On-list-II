/*
============================================================================
Name : 34a_server.c
Author : Rathod Nisha MT2023195
Description : Write a program to create a concurrent server.
 a. use fork
 b. use pthread_create
Date: 7th Oct, 2023.
============================================================================
*/


#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int socketFileDescriptor, connectionFileDescriptor;
    int bindStatus;
    int listenStatus;
    int clientSize;

    struct sockaddr_in address, client;

    ssize_t readBytes, writeBytes;
    char dataFromClient[100];

    socketFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFileDescriptor == -1) {
        perror("Error");
        return 0;
    }

    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_family = AF_INET;
    address.sin_port = htons(8080);

    bindStatus = bind(socketFileDescriptor, (struct sockaddr *)&address, sizeof(address));
    if (bindStatus == -1) {
        perror("Error");
        return 0;
    }
    printf("Connection established\n");

    listenStatus = listen(socketFileDescriptor, 2);
    if (listenStatus == -1) {
        perror("Error");
        return 0;
    }
    printf("Server listening...\n");
    
    while (1) {
        clientSize = (int)sizeof(client);
        connectionFileDescriptor = accept(socketFileDescriptor, (struct sockaddr *)&client, &clientSize);
        if (connectionFileDescriptor == -1) {
            perror("Error");
        } else {
            if (fork() == 0) {
                // Child
                writeBytes = write(connectionFileDescriptor, "How are you client?", 15);
                if (writeBytes == -1) {
                    perror("Error");
                } else {
                    printf("Message sent\n");
                }
                readBytes = read(connectionFileDescriptor, dataFromClient, 100);
                if (readBytes == -1) {
                    perror("Error");
                } else {
                    printf("From client- %s\n", dataFromClient);
                }
                exit(0);
            } else {
                // Parent
                close(connectionFileDescriptor);
            }
        }
    }

    close(socketFileDescriptor);
    return 0;
}
