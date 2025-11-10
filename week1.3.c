//Write a program to create child process. Make sure that parent process waits un l child has 
//not completed its execu on. (use wait(), exit()) What will happen if parent process dies 
//before child process? Illustrate it by crea ng one more child of parent process. 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid1, pid2;
    int status;
    
    printf("=== SCENARIO 1: Parent waits for child ===\n");
    printf("Parent PID: %d\n\n", getpid());
    
    pid1 = fork();
    
    if (pid1 < 0) {
        perror("Fork failed");
        exit(1);
    }
    else if (pid1 == 0) {
        printf("Child 1 started - PID: %d, Parent PID: %d\n", getpid(), getppid());
        printf("Child 1 is working...\n");
        sleep(3);
        printf("Child 1 completed its execution\n");
        exit(0);
    }
    else {
        printf("Parent created Child 1 with PID: %d\n", pid1);
        printf("Parent is waiting for Child 1 to complete...\n");
        wait(&status);
        printf("Child 1 has finished. Parent resumes execution.\n\n");
    }
    
    printf("=== SCENARIO 2: Parent dies before child (Orphan Process) ===\n");
    printf("Parent PID: %d\n\n", getpid());
    
    pid2 = fork();
    
    if (pid2 < 0) {
        perror("Fork failed");
        exit(1);
    }
    else if (pid2 == 0) {
        printf("Child 2 started - PID: %d, Parent PID: %d\n", getpid(), getppid());
        printf("Child 2 is sleeping for 5 seconds...\n");
        sleep(2);
        printf("Child 2 woke up - PID: %d, Parent PID: %d (Check if changed!)\n", 
               getpid(), getppid());
        sleep(3);
        printf("Child 2 completed - Final Parent PID: %d\n", getppid());
        printf("Child 2 has become an ORPHAN process (adopted by init/systemd)\n");
        exit(0);
    }
    else {
        printf("Parent created Child 2 with PID: %d\n", pid2);
        printf("Parent will NOT wait and will terminate immediately!\n");
        printf("Parent terminating... Child 2 will become orphan.\n");
        exit(0);
    }
    
    return 0;
}