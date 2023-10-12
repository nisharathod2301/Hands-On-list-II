/*
============================================================================
Name : 34b_server.c
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
#include <pthread.h>

void communicate(int *fd) {
    ssize_t readBytes, writeBytes;
    char dataFromClient[100];
    
    // Server - Client communication
    writeBytes = write(*fd, "Yes we did", 10);
    if (writeBytes == -1)
        perror("Error");
    else
        printf("Message sent\n");

    readBytes = read(*fd, dataFromClient, 100);
    if (readBytes == -1)
        perror("Error");
    else
        printf("From client- %s\n", dataFromClient);
    
    close(*fd);
}

int main() {
    int socketFileDescriptor, connectionFileDescriptor;
    int bindStatus;
    int listenStatus;
    int clientSize;

    struct sockaddr_in address, client;

    pthread_t threadID;

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
        if (connectionFileDescriptor == -1)
            perror("Error");
        else {
            if (pthread_create(&threadID, NULL, (void *)communicate, &connectionFileDescriptor))
                perror("Error");
        }
    }

    close(socketFileDescriptor);
    return 0;
}


