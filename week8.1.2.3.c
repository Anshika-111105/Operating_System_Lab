/*I. Best Fit – block which is closes to the size of request is allocated i.e. the smallest hole that is big enough to allocate to the requesting program. 
II. First Fit – start searching the list from beginning, take the first block whose size is greater than or equal to the requesting program size and allocate it to program. 
III. Worst Fit – block which is largest among all is allocated for the program. */
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

// Best Fit Memory Allocation
void best_fit(int block_sizes[], int n_blocks, int process_sizes[], int n_processes) {
    int allocation[n_processes];
    bool is_allocated[n_blocks];
    int remaining[n_blocks];
    
    // Initialize
    for (int i = 0; i < n_processes; i++) {
        allocation[i] = -1; // -1 means not allocated
    }
    
    for (int i = 0; i < n_blocks; i++) {
        is_allocated[i] = false;
        remaining[i] = block_sizes[i];
    }
    
    printf("\n========================================\n");
    printf("  Best Fit Memory Allocation\n");
    printf("========================================\n\n");
    
    // For each process
    for (int i = 0; i < n_processes; i++) {
        int best_index = -1;
        int min_diff = INT_MAX;
        
        // Find the best fitting block
        for (int j = 0; j < n_blocks; j++) {
            if (remaining[j] >= process_sizes[i]) {
                int diff = remaining[j] - process_sizes[i];
                if (diff < min_diff) {
                    min_diff = diff;
                    best_index = j;
                }
            }
        }
        
        // Allocate if found
        if (best_index != -1) {
            allocation[i] = best_index;
            remaining[best_index] -= process_sizes[i];
        }
    }
    
    // Display results
    printf("Process No.\tProcess Size\tBlock No.\n");
    printf("--------------------------------------------------------\n");
    for (int i = 0; i < n_processes; i++) {
        printf("%d\t\t%d\t\t", i + 1, process_sizes[i]);
        if (allocation[i] != -1) {
            printf("%d\n", allocation[i] + 1);
        } else {
            printf("Not Allocated\n");
        }
    }
    
    printf("\n");
    for (int i = 0; i < n_processes; i++) {
        printf("%d - ", process_sizes[i]);
        if (allocation[i] != -1) {
            printf("%d\n", allocation[i] + 1);
        } else {
            printf("no free block allocated\n");
        }
    }
}

// First Fit Memory Allocation
void first_fit(int block_sizes[], int n_blocks, int process_sizes[], int n_processes) {
    int allocation[n_processes];
    int remaining[n_blocks];
    
    // Initialize
    for (int i = 0; i < n_processes; i++) {
        allocation[i] = -1;
    }
    
    for (int i = 0; i < n_blocks; i++) {
        remaining[i] = block_sizes[i];
    }
    
    printf("\n========================================\n");
    printf("  First Fit Memory Allocation\n");
    printf("========================================\n\n");
    
    // For each process
    for (int i = 0; i < n_processes; i++) {
        // Find first block that fits
        for (int j = 0; j < n_blocks; j++) {
            if (remaining[j] >= process_sizes[i]) {
                allocation[i] = j;
                remaining[j] -= process_sizes[i];
                break;
            }
        }
    }
    
    // Display results
    printf("Process No.\tProcess Size\tBlock No.\n");
    printf("--------------------------------------------------------\n");
    for (int i = 0; i < n_processes; i++) {
        printf("%d\t\t%d\t\t", i + 1, process_sizes[i]);
        if (allocation[i] != -1) {
            printf("%d\n", allocation[i] + 1);
        } else {
            printf("Not Allocated\n");
        }
    }
    
    printf("\n");
    for (int i = 0; i < n_processes; i++) {
        printf("%d - ", process_sizes[i]);
        if (allocation[i] != -1) {
            printf("%d\n", allocation[i] + 1);
        } else {
            printf("no free block allocated\n");
        }
    }
}

// Worst Fit Memory Allocation
void worst_fit(int block_sizes[], int n_blocks, int process_sizes[], int n_processes) {
    int allocation[n_processes];
    int remaining[n_blocks];
    
    // Initialize
    for (int i = 0; i < n_processes; i++) {
        allocation[i] = -1;
    }
    
    for (int i = 0; i < n_blocks; i++) {
        remaining[i] = block_sizes[i];
    }
    
    printf("\n========================================\n");
    printf("  Worst Fit Memory Allocation\n");
    printf("========================================\n\n");
    
    // For each process
    for (int i = 0; i < n_processes; i++) {
        int worst_index = -1;
        int max_size = -1;
        
        // Find the largest block that fits
        for (int j = 0; j < n_blocks; j++) {
            if (remaining[j] >= process_sizes[i]) {
                if (remaining[j] > max_size) {
                    max_size = remaining[j];
                    worst_index = j;
                }
            }
        }
        
        // Allocate if found
        if (worst_index != -1) {
            allocation[i] = worst_index;
            remaining[worst_index] -= process_sizes[i];
        }
    }
    
    // Display results
    printf("Process No.\tProcess Size\tBlock No.\n");
    printf("--------------------------------------------------------\n");
    for (int i = 0; i < n_processes; i++) {
        printf("%d\t\t%d\t\t", i + 1, process_sizes[i]);
        if (allocation[i] != -1) {
            printf("%d\n", allocation[i] + 1);
        } else {
            printf("Not Allocated\n");
        }
    }
    
    printf("\n");
    for (int i = 0; i < n_processes; i++) {
        printf("%d - ", process_sizes[i]);
        if (allocation[i] != -1) {
            printf("%d\n", allocation[i] + 1);
        } else {
            printf("no free block allocated\n");
        }
    }
}

int main() {
    int n_blocks, n_processes, choice;
    
    printf("Enter number of free blocks available: ");
    scanf("%d", &n_blocks);
    
    int block_sizes[n_blocks];
    printf("Enter size of each block: ");
    for (int i = 0; i < n_blocks; i++) {
        scanf("%d", &block_sizes[i]);
    }
    
    printf("Enter number of processes: ");
    scanf("%d", &n_processes);
    
    int process_sizes[n_processes];
    printf("Enter memory required by each process: ");
    for (int i = 0; i < n_processes; i++) {
        scanf("%d", &process_sizes[i]);
    }
    
    printf("\n========================================\n");
    printf("Select Memory Allocation Algorithm:\n");
    printf("1. Best Fit\n");
    printf("2. First Fit\n");
    printf("3. Worst Fit\n");
    printf("========================================\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    
    switch(choice) {
        case 1:
            best_fit(block_sizes, n_blocks, process_sizes, n_processes);
            break;
        case 2:
            first_fit(block_sizes, n_blocks, process_sizes, n_processes);
            break;
        case 3:
            worst_fit(block_sizes, n_blocks, process_sizes, n_processes);
            break;
        default:
            printf("Invalid choice!\n");
            return 1;
    }
    
    printf("\n========================================\n");
    
    return 0;
}