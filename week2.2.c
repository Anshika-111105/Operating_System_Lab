//Write a program to show working of execlp() system call by execu ng ls command.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main() {
    pid_t pid;
    
    printf("======================================\n");
    printf("    execlp() SYSTEM CALL DEMO\n");
    printf("======================================\n\n");
    
    printf("Current Process PID: %d\n", getpid());
    printf("About to execute 'ls -l' command using execlp()\n");
    printf("--------------------------------------\n\n");
    
    pid = fork();
    
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }
    else if (pid == 0) {
        printf("Child Process PID: %d\n", getpid());
        printf("Executing ls command...\n\n");
        
        execlp("ls", "ls", "-l", NULL);
        
        perror("execlp failed");
        exit(1);
    }
    else {
        wait(NULL);
        
        printf("\n--------------------------------------\n");
        printf("Parent Process: Child has completed\n");
        printf("This line executes because parent didn't call exec\n");
        printf("Parent Process PID: %d\n", getpid());
    }
    
    return 0;
}