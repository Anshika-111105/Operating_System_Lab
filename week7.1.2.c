/*I. FIFO – First In First Out : page which came first (i.e. oldest page) need to be moved out. 
II. LRU – Least Recently Used : page which is has not been used for longest me need to be moved out.*/
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

// Function to check if page is present in frames
bool is_present(int frames[], int n_frames, int page) {
    for (int i = 0; i < n_frames; i++) {
        if (frames[i] == page) {
            return true;
        }
    }
    return false;
}

// Function to display current frames
void display_frames(int frames[], int n_frames) {
    printf("Frames: [");
    for (int i = 0; i < n_frames; i++) {
        if (frames[i] == -1) {
            printf("  ");
        } else {
            printf("%2d", frames[i]);
        }
        if (i < n_frames - 1) printf(" | ");
    }
    printf("]");
}

// FIFO Page Replacement Algorithm
void fifo(int pages[], int n_pages, int n_frames) {
    int frames[n_frames];
    int page_faults = 0;
    int oldest = 0; // Points to the oldest page (to be replaced)
    
    // Initialize frames with -1 (empty)
    for (int i = 0; i < n_frames; i++) {
        frames[i] = -1;
    }
    
    printf("\n========================================\n");
    printf("  FIFO Page Replacement Algorithm\n");
    printf("========================================\n\n");
    printf("Page Reference String: ");
    for (int i = 0; i < n_pages; i++) {
        printf("%d ", pages[i]);
    }
    printf("\n\n");
    
    printf("%-10s %-30s %s\n", "Page", "Frames", "Page Fault");
    printf("--------------------------------------------------------\n");
    
    for (int i = 0; i < n_pages; i++) {
        printf("%-10d ", pages[i]);
        
        // Check if page is already present
        if (is_present(frames, n_frames, pages[i])) {
            display_frames(frames, n_frames);
            printf("   No\n");
        } else {
            // Page fault occurs
            frames[oldest] = pages[i];
            oldest = (oldest + 1) % n_frames; // Move to next position (circular)
            page_faults++;
            
            display_frames(frames, n_frames);
            printf("   Yes\n");
        }
    }
    
    printf("\n========================================\n");
    printf("Total number of page faults: %d\n", page_faults);
    printf("========================================\n");
}

// LRU Page Replacement Algorithm
void lru(int pages[], int n_pages, int n_frames) {
    int frames[n_frames];
    int last_used[n_frames]; // Stores the last used time of each frame
    int page_faults = 0;
    
    // Initialize frames with -1 (empty)
    for (int i = 0; i < n_frames; i++) {
        frames[i] = -1;
        last_used[i] = -1;
    }
    
    printf("\n========================================\n");
    printf("  LRU Page Replacement Algorithm\n");
    printf("========================================\n\n");
    printf("Page Reference String: ");
    for (int i = 0; i < n_pages; i++) {
        printf("%d ", pages[i]);
    }
    printf("\n\n");
    
    printf("%-10s %-30s %s\n", "Page", "Frames", "Page Fault");
    printf("--------------------------------------------------------\n");
    
    for (int i = 0; i < n_pages; i++) {
        printf("%-10d ", pages[i]);
        
        // Check if page is already present
        bool found = false;
        int page_index = -1;
        
        for (int j = 0; j < n_frames; j++) {
            if (frames[j] == pages[i]) {
                found = true;
                page_index = j;
                break;
            }
        }
        
        if (found) {
            // Page hit - update last used time
            last_used[page_index] = i;
            display_frames(frames, n_frames);
            printf("   No\n");
        } else {
            // Page fault occurs
            page_faults++;
            
            // Find position to replace
            int replace_index = -1;
            
            // Check if there's an empty frame
            for (int j = 0; j < n_frames; j++) {
                if (frames[j] == -1) {
                    replace_index = j;
                    break;
                }
            }
            
            // If no empty frame, find least recently used
            if (replace_index == -1) {
                int lru_time = INT_MAX;
                for (int j = 0; j < n_frames; j++) {
                    if (last_used[j] < lru_time) {
                        lru_time = last_used[j];
                        replace_index = j;
                    }
                }
            }
            
            // Replace page
            frames[replace_index] = pages[i];
            last_used[replace_index] = i;
            
            display_frames(frames, n_frames);
            printf("   Yes\n");
        }
    }
    
    printf("\n========================================\n");
    printf("Total number of page faults: %d\n", page_faults);
    printf("========================================\n");
}

int main() {
    int n_frames, n_pages, choice;
    
    printf("Enter number of frames available: ");
    scanf("%d", &n_frames);
    
    printf("Enter number of requests: ");
    scanf("%d", &n_pages);
    
    int pages[n_pages];
    
    printf("Enter page reference string: ");
    for (int i = 0; i < n_pages; i++) {
        scanf("%d", &pages[i]);
    }
    
    printf("\n========================================\n");
    printf("Select Page Replacement Algorithm:\n");
    printf("1. FIFO (First In First Out)\n");
    printf("2. LRU (Least Recently Used)\n");
    printf("========================================\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    
    switch(choice) {
        case 1:
            fifo(pages, n_pages, n_frames);
            break;
        case 2:
            lru(pages, n_pages, n_frames);
            break;
        default:
            printf("Invalid choice!\n");
            return 1;
    }
    
    return 0;
}