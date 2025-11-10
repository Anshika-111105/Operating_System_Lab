/*Write a program to communicate parent and child process with each other in such a way that whenever child writes 
something, parent process can read it. Consider mode of communication is through a) pipe  b) message passing c) shared memory */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define BUFFER_SIZE 256

// Structure for message queue
struct message {
    long msg_type;
    char msg_text[BUFFER_SIZE];
};

// ==================== PIPE COMMUNICATION ====================
void pipe_communication() {
    int pipefd[2];
    pid_t pid;
    char write_msg[BUFFER_SIZE];
    char read_msg[BUFFER_SIZE];
    
    // Create pipe
    if (pipe(pipefd) == -1) {
        perror("Pipe creation failed");
        exit(1);
    }
    
    pid = fork();
    
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }
    
    if (pid == 0) {
        // Child process - Writer
        close(pipefd[0]); // Close reading end
        
        printf("\n[CHILD] Enter message to send to parent: ");
        fgets(write_msg, BUFFER_SIZE, stdin);
        write_msg[strcspn(write_msg, "\n")] = '\0'; // Remove newline
        
        write(pipefd[1], write_msg, strlen(write_msg) + 1);
        printf("[CHILD] Message sent: %s\n", write_msg);
        
        close(pipefd[1]);
        exit(0);
    } else {
        // Parent process - Reader
        close(pipefd[1]); // Close writing end
        
        wait(NULL); // Wait for child to write
        
        read(pipefd[0], read_msg, BUFFER_SIZE);
        printf("[PARENT] Message received from child: %s\n", read_msg);
        
        close(pipefd[0]);
    }
}

// ==================== MESSAGE QUEUE COMMUNICATION ====================
void message_queue_communication() {
    key_t key;
    int msgid;
    pid_t pid;
    struct message msg;
    
    // Generate unique key
    key = ftok("progfile", 65);
    
    // Create message queue
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("Message queue creation failed");
        exit(1);
    }
    
    pid = fork();
    
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }
    
    if (pid == 0) {
        // Child process - Sender
        msg.msg_type = 1;
        
        printf("\n[CHILD] Enter message to send to parent: ");
        fgets(msg.msg_text, BUFFER_SIZE, stdin);
        msg.msg_text[strcspn(msg.msg_text, "\n")] = '\0';
        
        msgsnd(msgid, &msg, sizeof(msg.msg_text), 0);
        printf("[CHILD] Message sent: %s\n", msg.msg_text);
        
        exit(0);
    } else {
        // Parent process - Receiver
        wait(NULL);
        
        msgrcv(msgid, &msg, sizeof(msg.msg_text), 1, 0);
        printf("[PARENT] Message received from child: %s\n", msg.msg_text);
        
        // Destroy message queue
        msgctl(msgid, IPC_RMID, NULL);
    }
}

// ==================== SHARED MEMORY COMMUNICATION ====================
void shared_memory_communication() {
    key_t key;
    int shmid;
    pid_t pid;
    char *shared_mem;
    char write_msg[BUFFER_SIZE];
    
    // Generate unique key
    key = ftok("shmfile", 65);
    
    // Create shared memory segment
    shmid = shmget(key, BUFFER_SIZE, 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("Shared memory creation failed");
        exit(1);
    }
    
    pid = fork();
    
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }
    
    if (pid == 0) {
        // Child process - Writer
        shared_mem = (char*) shmat(shmid, NULL, 0);
        
        printf("\n[CHILD] Enter message to send to parent: ");
        fgets(write_msg, BUFFER_SIZE, stdin);
        write_msg[strcspn(write_msg, "\n")] = '\0';
        
        strcpy(shared_mem, write_msg);
        printf("[CHILD] Message written to shared memory: %s\n", write_msg);
        
        shmdt(shared_mem);
        exit(0);
    } else {
        // Parent process - Reader
        wait(NULL);
        
        shared_mem = (char*) shmat(shmid, NULL, 0);
        printf("[PARENT] Message read from shared memory: %s\n", shared_mem);
        
        shmdt(shared_mem);
        
        // Destroy shared memory
        shmctl(shmid, IPC_RMID, NULL);
    }
}

// ==================== MAIN FUNCTION ====================
int main() {
    int choice;
    
    printf("========================================\n");
    printf("  Inter-Process Communication (IPC)\n");
    printf("========================================\n");
    printf("1. Pipe Communication\n");
    printf("2. Message Queue Communication\n");
    printf("3. Shared Memory Communication\n");
    printf("========================================\n");
    printf("Enter your choice (1-3): ");
    scanf("%d", &choice);
    getchar(); // Clear newline from buffer
    
    switch(choice) {
        case 1:
            printf("\n=== PIPE COMMUNICATION ===\n");
            pipe_communication();
            break;
        case 2:
            printf("\n=== MESSAGE QUEUE COMMUNICATION ===\n");
            message_queue_communication();
            break;
        case 3:
            printf("\n=== SHARED MEMORY COMMUNICATION ===\n");
            shared_memory_communication();
            break;
        default:
            printf("Invalid choice!\n");
            return 1;
    }
    
    printf("\nCommunication completed successfully!\n");
    return 0;
}