/*
============================================================================
Name : 17a.c
Author : Rathod Nisha MT2023195
Description : Write a program to execute ls -l | wc.
 a. use dup
 b. use dup2
 c. use fcntl

Date: 5th Oct, 2023.
============================================================================
*/
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

void main()
{
    int pipefd[2];
    int pipeStatus;
    pid_t childPid;

    pipeStatus = pipe(pipefd);

    if (pipeStatus == -1) {
        perror("Error while creating the pipe!");
    } else {
        childPid = fork();

        if (childPid == -1) {
            perror("Error while forking child!");
        } else if (childPid == 0) {
            // Child process
            close(pipefd[1]); // Close the write end of the pipe
            dup2(pipefd[0], STDIN_FILENO); // Redirect standard input to the pipe

            execl("/usr/bin/wc", "wc", NULL); // Execute "wc" command
        } else {
            // Parent process
            close(pipefd[0]); // Close the read end of the pipe
            dup2(pipefd[1], STDOUT_FILENO); // Redirect standard output to the pipe

            execl("/usr/bin/ls", "ls", "-l", NULL); // Execute "ls -l" command
        }
    }
}
