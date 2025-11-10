//Write a C program to simulate Bankers algorithm for the purpose of deadlock avoidance.
#include <stdio.h>
#include <stdbool.h>

int main() {
    int p, r;
    
    printf("Enter number of processes: ");
    scanf("%d", &p);
    
    printf("Enter number of resources: ");
    scanf("%d", &r);
    
    int max[p][r], allocated[p][r], need[p][r];
    int total[r], available[r];
    
    // Input Maximum requirement matrix
    printf("Enter Maximum requirement matrix:\n");
    for (int i = 0; i < p; i++) {
        printf("Process P%d: ", i);
        for (int j = 0; j < r; j++) {
            scanf("%d", &max[i][j]);
        }
    }
    
    // Input Allocated matrix
    printf("Enter Allocated matrix:\n");
    for (int i = 0; i < p; i++) {
        printf("Process P%d: ", i);
        for (int j = 0; j < r; j++) {
            scanf("%d", &allocated[i][j]);
        }
    }
    
    // Input Total resource vector
    printf("Enter Total resource vector: ");
    for (int i = 0; i < r; i++) {
        scanf("%d", &total[i]);
    }
    
    // Calculate Need matrix (Need = Max - Allocated)
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < r; j++) {
            need[i][j] = max[i][j] - allocated[i][j];
        }
    }
    
    // Calculate Available resources (Available = Total - Sum of Allocated)
    for (int i = 0; i < r; i++) {
        available[i] = total[i];
        for (int j = 0; j < p; j++) {
            available[i] -= allocated[j][i];
        }
    }
    
    // Display matrices
    printf("\n--- Maximum Matrix ---\n");
    for (int i = 0; i < p; i++) {
        printf("P%d: ", i);
        for (int j = 0; j < r; j++) {
            printf("%d ", max[i][j]);
        }
        printf("\n");
    }
    
    printf("\n--- Allocated Matrix ---\n");
    for (int i = 0; i < p; i++) {
        printf("P%d: ", i);
        for (int j = 0; j < r; j++) {
            printf("%d ", allocated[i][j]);
        }
        printf("\n");
    }
    
    printf("\n--- Need Matrix ---\n");
    for (int i = 0; i < p; i++) {
        printf("P%d: ", i);
        for (int j = 0; j < r; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }
    
    printf("\n--- Available Resources ---\n");
    for (int i = 0; i < r; i++) {
        printf("%d ", available[i]);
    }
    printf("\n");
    
    // Banker's Algorithm - Safety Check
    bool finish[p];
    int safe_sequence[p];
    int work[r];
    int count = 0;
    
    // Initialize finish array and work array
    for (int i = 0; i < p; i++) {
        finish[i] = false;
    }
    
    for (int i = 0; i < r; i++) {
        work[i] = available[i];
    }
    
    // Find safe sequence
    while (count < p) {
        bool found = false;
        
        for (int i = 0; i < p; i++) {
            if (!finish[i]) {
                bool can_allocate = true;
                
                // Check if need <= work for all resources
                for (int j = 0; j < r; j++) {
                    if (need[i][j] > work[j]) {
                        can_allocate = false;
                        break;
                    }
                }
                
                if (can_allocate) {
                    // Process can complete, add allocated resources back to work
                    for (int j = 0; j < r; j++) {
                        work[j] += allocated[i][j];
                    }
                    
                    safe_sequence[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }
        
        // If no process was found in this iteration, deadlock possible
        if (!found) {
            break;
        }
    }
    
    // Check if all processes finished
    printf("\n");
    if (count == p) {
        printf("Request can be fulfilled\n");
        printf("Safe Sequence: ");
        for (int i = 0; i < p; i++) {
            printf("P%d", safe_sequence[i]);
            if (i < p - 1) {
                printf(" -> ");
            }
        }
        printf("\n");
    } else {
        printf("Request cannot be fulfilled\n");
        printf("System is in unsafe state (Deadlock may occur)\n");
    }
    
    return 0;
}