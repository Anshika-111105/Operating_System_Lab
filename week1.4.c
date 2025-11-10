//Write a program to implement Orphan and Zombie Process.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void createOrphanProcess() {
    pid_t pid;
    
    printf("\n========== ORPHAN PROCESS DEMONSTRATION ==========\n");
    
    pid = fork();
    
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }
    else if (pid == 0) {
        printf("\n[CHILD] Child process started\n");
        printf("[CHILD] PID: %d, Parent PID: %d\n", getpid(), getppid());
        
        sleep(3);
        
        printf("\n[CHILD] After parent terminated\n");
        printf("[CHILD] PID: %d, Parent PID: %d (adopted by init/systemd)\n", 
               getpid(), getppid());
        printf("[CHILD] This is an ORPHAN PROCESS!\n");
        printf("[CHILD] Orphan process terminating...\n\n");
        exit(0);
    }
    else {
        printf("\n[PARENT] Parent process PID: %d\n", getpid());
        printf("[PARENT] Created child with PID: %d\n", pid);
        printf("[PARENT] Parent will terminate immediately without waiting\n");
        printf("[PARENT] Child will become orphan...\n");
        exit(0);
    }
}

void createZombieProcess() {
    pid_t pid;
    
    printf("\n========== ZOMBIE PROCESS DEMONSTRATION ==========\n");
    
    pid = fork();
    
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }
    else if (pid == 0) {
        printf("\n[CHILD] Child process started\n");
        printf("[CHILD] PID: %d, Parent PID: %d\n", getpid(), getppid());
        printf("[CHILD] Child executing for 2 seconds...\n");
        sleep(2);
        printf("[CHILD] Child completed execution and exiting...\n");
        printf("[CHILD] Child will become ZOMBIE (parent not calling wait)\n\n");
        exit(0);
    }
    else {
        printf("\n[PARENT] Parent process PID: %d\n", getpid());
        printf("[PARENT] Created child with PID: %d\n", pid);
        printf("[PARENT] Parent is NOT calling wait()\n");
        printf("[PARENT] Child will become a ZOMBIE process\n");
        printf("[PARENT] Check with: ps aux | grep Z (or) ps -l\n");
        printf("[PARENT] Parent sleeping for 10 seconds...\n");
        printf("[PARENT] During this time, child becomes zombie (defunct)\n");
        
        sleep(10);
        
        printf("\n[PARENT] Parent woke up after 10 seconds\n");
        printf("[PARENT] Now calling wait() to reap zombie child...\n");
        wait(NULL);
        printf("[PARENT] Zombie child has been reaped!\n");
        printf("[PARENT] Parent terminating...\n\n");
        exit(0);
    }
}

int main() {
    int choice;
    printf("======================================\n");
    printf("  ORPHAN & ZOMBIE PROCESS DEMO\n");
    printf("======================================\n");
    printf("\n1. Create ORPHAN Process");
    printf("\n2. Create ZOMBIE Process");
    printf("\n3. Exit");
    printf("\n\nEnter your choice: ");
    scanf("%d", &choice);
    switch(choice) {
        case 1:
            createOrphanProcess();
            break;
        case 2:
            createZombieProcess();
            break;
        case 3:
            printf("Exiting...\n");
            exit(0);
        default:
            printf("Invalid choice!\n");
    }
    
    return 0;
}