//Write a program to implement the concept of Producer-Consumer problem using semaphores
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5

// Shared buffer
int buffer[BUFFER_SIZE];
int in = 0;  // Producer index
int out = 0; // Consumer index

// Semaphores
sem_t empty;  // Counts empty slots
sem_t full;   // Counts full slots
pthread_mutex_t mutex; // Mutual exclusion

// Production and consumption counters
int produced_count = 0;
int consumed_count = 0;
int total_items = 10; // Total items to produce/consume

// Producer function
void* producer(void* arg) {
    int producer_id = *((int*)arg);
    
    while(1) {
        // Check if production is complete
        if (produced_count >= total_items) {
            break;
        }
        
        // Produce an item
        int item = rand() % 100;
        
        // Wait for empty slot
        sem_wait(&empty);
        
        // Lock the critical section
        pthread_mutex_lock(&mutex);
        
        if (produced_count >= total_items) {
            pthread_mutex_unlock(&mutex);
            sem_post(&empty);
            break;
        }
        
        // Add item to buffer
        buffer[in] = item;
        printf("[PRODUCER %d] Produced item %d at position %d\n", 
               producer_id, item, in);
        
        // Display buffer status
        printf("Buffer: [");
        for (int i = 0; i < BUFFER_SIZE; i++) {
            if ((in >= out && i < in && i >= out) || 
                (in < out && (i >= out || i < in))) {
                printf("%d", buffer[i]);
            } else {
                printf(" ");
            }
            if (i < BUFFER_SIZE - 1) printf(", ");
        }
        printf("]\n\n");
        
        in = (in + 1) % BUFFER_SIZE;
        produced_count++;
        
        // Unlock the critical section
        pthread_mutex_unlock(&mutex);
        
        // Signal that buffer has one more full slot
        sem_post(&full);
        
        sleep(1); // Simulate production time
    }
    
    return NULL;
}

// Consumer function
void* consumer(void* arg) {
    int consumer_id = *((int*)arg);
    
    while(1) {
        // Check if consumption is complete
        if (consumed_count >= total_items) {
            break;
        }
        
        // Wait for full slot
        sem_wait(&full);
        
        // Lock the critical section
        pthread_mutex_lock(&mutex);
        
        if (consumed_count >= total_items) {
            pthread_mutex_unlock(&mutex);
            sem_post(&full);
            break;
        }
        
        // Remove item from buffer
        int item = buffer[out];
        printf("[CONSUMER %d] Consumed item %d from position %d\n", 
               consumer_id, item, out);
        
        // Display buffer status
        printf("Buffer: [");
        for (int i = 0; i < BUFFER_SIZE; i++) {
            if ((in > out && i < in && i > out) || 
                (in < out && (i > out || i < in)) ||
                (in == out && consumed_count < produced_count)) {
                printf("%d", buffer[i]);
            } else {
                printf(" ");
            }
            if (i < BUFFER_SIZE - 1) printf(", ");
        }
        printf("]\n\n");
        
        out = (out + 1) % BUFFER_SIZE;
        consumed_count++;
        
        // Unlock the critical section
        pthread_mutex_unlock(&mutex);
        
        // Signal that buffer has one more empty slot
        sem_post(&empty);
        
        sleep(2); // Simulate consumption time
    }
    
    return NULL;
}

int main() {
    int num_producers, num_consumers;
    
    printf("========================================\n");
    printf("  Producer-Consumer Problem\n");
    printf("  Using Semaphores\n");
    printf("========================================\n");
    
    printf("Enter number of producers: ");
    scanf("%d", &num_producers);
    
    printf("Enter number of consumers: ");
    scanf("%d", &num_consumers);
    
    printf("Enter total items to produce/consume: ");
    scanf("%d", &total_items);
    
    printf("\nBuffer Size: %d\n", BUFFER_SIZE);
    printf("Starting simulation...\n\n");
    
    // Initialize semaphores
    sem_init(&empty, 0, BUFFER_SIZE); // Initially all slots are empty
    sem_init(&full, 0, 0);             // Initially no slots are full
    pthread_mutex_init(&mutex, NULL);
    
    // Create producer and consumer threads
    pthread_t producers[num_producers];
    pthread_t consumers[num_consumers];
    int producer_ids[num_producers];
    int consumer_ids[num_consumers];
    
    // Create producer threads
    for (int i = 0; i < num_producers; i++) {
        producer_ids[i] = i + 1;
        pthread_create(&producers[i], NULL, producer, &producer_ids[i]);
    }
    
    // Create consumer threads
    for (int i = 0; i < num_consumers; i++) {
        consumer_ids[i] = i + 1;
        pthread_create(&consumers[i], NULL, consumer, &consumer_ids[i]);
    }
    
    // Wait for all producer threads to finish
    for (int i = 0; i < num_producers; i++) {
        pthread_join(producers[i], NULL);
    }
    
    // Wait for all consumer threads to finish
    for (int i = 0; i < num_consumers; i++) {
        pthread_join(consumers[i], NULL);
    }
    
    printf("========================================\n");
    printf("Simulation completed!\n");
    printf("Total items produced: %d\n", produced_count);
    printf("Total items consumed: %d\n", consumed_count);
    printf("========================================\n");
    
    // Cleanup
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);
    
    return 0;
}