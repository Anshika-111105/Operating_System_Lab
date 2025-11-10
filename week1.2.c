//Write a program to print process Id's of parent and child process i.e. parent should print its 
//own and its child process id while child process should print its own and its parent process 
//id. (use getpid(), getppid()).
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }
    else if (pid == 0) {
        printf("\nCHILD PROCESS:\n");
        printf("My PID (Child's PID): %d\n", getpid());
        printf("My Parent's PID: %d\n", getppid());
    }else {
        printf("\nPARENT PROCESS:\n");
        printf("My PID (Parent's PID): %d\n", getpid());
        printf("My Child's PID: %d\n", pid);
        
        wait(NULL);
    }
    return 0;
}