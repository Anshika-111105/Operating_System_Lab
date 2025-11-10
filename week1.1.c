//Write a program to create a child process using system call fork()
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    printf("Before fork() - Parent PID: %d\n", getpid());
    printf("----------------------------------------\n");
    pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }
    else if (pid == 0) {
        printf("CHILD PROCESS:\n");
        printf("  Child PID: %d\n", getpid());
        printf("  Parent PID: %d\n", getppid());
        printf("  fork() returned: %d\n", pid);
        printf("  Child is doing some work...\n");
        sleep(2);
        printf("  Child process finished!\n");
        exit(0);
    }
    else {
        printf("PARENT PROCESS:\n");
        printf("  Parent PID: %d\n", getpid());
        printf("  Child PID: %d\n", pid);
        printf("  fork() returned: %d\n", pid);
        printf("  Parent is waiting for child...\n");
        
        wait(NULL);
        
        printf("  Child has terminated.\n");
        printf("  Parent process finished!\n");
    }
    
    return 0;
}