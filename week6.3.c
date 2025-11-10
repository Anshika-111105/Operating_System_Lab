// Write a program to implement the concept of Dining-Philosopher problem.
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5  // Number of philosophers
#define THINKING 0
#define HUNGRY 1
#define EATING 2
#define LEFT (philosopher_id + N - 1) % N  // Left neighbor
#define RIGHT (philosopher_id + 1) % N     // Right neighbor

int state[N];              // State of each philosopher
sem_t mutex;               // Mutex for critical section
sem_t S[N];                // Semaphore for each philosopher
int eating_count[N] = {0}; // Count how many times each philosopher ate

// Function prototypes
void* philosopher(void* arg);
void take_forks(int philosopher_id);
void put_forks(int philosopher_id);
void test(int philosopher_id);
void think(int philosopher_id);
void eat(int philosopher_id);

// Philosopher thread function
void* philosopher(void* arg) {
    int philosopher_id = *((int*)arg);
    int meals = 3; // Each philosopher will eat 3 times
    
    for (int i = 0; i < meals; i++) {
        think(philosopher_id);
        take_forks(philosopher_id);
        eat(philosopher_id);
        put_forks(philosopher_id);
    }
    
    printf("\n[Philosopher %d] Finished dining (ate %d times)\n", 
           philosopher_id, eating_count[philosopher_id]);
    
    return NULL;
}

// Philosopher thinking
void think(int philosopher_id) {
    printf("[Philosopher %d] is THINKING\n", philosopher_id);
    sleep(rand() % 3 + 1); // Think for 1-3 seconds
}

// Philosopher eating
void eat(int philosopher_id) {
    printf("[Philosopher %d] is EATING (Fork %d and Fork %d)\n", 
           philosopher_id, LEFT, philosopher_id);
    
    // Display current state
    printf("State: [");
    for (int i = 0; i < N; i++) {
        if (state[i] == THINKING) printf("T");
        else if (state[i] == HUNGRY) printf("H");
        else if (state[i] == EATING) printf("E");
        if (i < N - 1) printf(" ");
    }
    printf("]\n\n");
    
    eating_count[philosopher_id]++;
    sleep(rand() % 2 + 1); // Eat for 1-2 seconds
}

// Take forks (chopsticks)
void take_forks(int philosopher_id) {
    sem_wait(&mutex); // Enter critical section
    
    state[philosopher_id] = HUNGRY;
    printf("[Philosopher %d] is HUNGRY\n", philosopher_id);
    
    test(philosopher_id); // Try to acquire forks
    
    sem_post(&mutex); // Exit critical section
    
    sem_wait(&S[philosopher_id]); // Wait if unable to get forks
}

// Put down forks (chopsticks)
void put_forks(int philosopher_id) {
    sem_wait(&mutex); // Enter critical section
    
    state[philosopher_id] = THINKING;
    printf("[Philosopher %d] put down forks %d and %d\n", 
           philosopher_id, LEFT, philosopher_id);
    
    // Check if left and right neighbors can eat
    test(LEFT);
    test(RIGHT);
    
    sem_post(&mutex); // Exit critical section
}

// Test if philosopher can eat
void test(int philosopher_id) {
    if (state[philosopher_id] == HUNGRY && 
        state[LEFT] != EATING && 
        state[RIGHT] != EATING) {
        
        state[philosopher_id] = EATING;
        sem_post(&S[philosopher_id]); // Allow philosopher to eat
    }
}

// Display dining table status
void display_table() {
    printf("\n========================================\n");
    printf("     Dining Philosophers Table\n");
    printf("========================================\n");
    printf("        Philosopher %d\n", 0);
    printf("       /           \\\n");
    printf("   Fork 4         Fork 0\n");
    printf("     /               \\\n");
    printf("Philosopher %d --- Philosopher %d\n", 4, 1);
    printf("    |                 |\n");
    printf("  Fork 3           Fork 1\n");
    printf("    |                 |\n");
    printf("Philosopher %d --- Philosopher %d\n", 3, 2);
    printf("     \\               /\n");
    printf("      Fork 2\n");
    printf("========================================\n\n");
}

int main() {
    pthread_t philosophers[N];
    int philosopher_ids[N];
    
    printf("========================================\n");
    printf("  Dining Philosophers Problem\n");
    printf("  Number of Philosophers: %d\n", N);
    printf("========================================\n\n");
    
    display_table();
    
    // Initialize semaphores
    sem_init(&mutex, 0, 1); // Binary semaphore for mutual exclusion
    
    for (int i = 0; i < N; i++) {
        sem_init(&S[i], 0, 0); // Each philosopher's semaphore
        state[i] = THINKING;
    }
    
    printf("Starting simulation...\n\n");
    
    // Create philosopher threads
    for (int i = 0; i < N; i++) {
        philosopher_ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &philosopher_ids[i]);
        usleep(100000); // Small delay to stagger thread creation
    }
    
    // Wait for all philosophers to finish
    for (int i = 0; i < N; i++) {
        pthread_join(philosophers[i], NULL);
    }
    
    printf("\n========================================\n");
    printf("Simulation completed!\n");
    printf("========================================\n");
    printf("Eating Summary:\n");
    for (int i = 0; i < N; i++) {
        printf("Philosopher %d ate %d times\n", i, eating_count[i]);
    }
    printf("========================================\n");
    
    // Cleanup
    sem_destroy(&mutex);
    for (int i = 0; i < N; i++) {
        sem_destroy(&S[i]);
    }
    
    return 0;
}