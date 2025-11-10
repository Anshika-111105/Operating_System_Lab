/*1.Sequential/Contiguous – each file occupied con guous blocks on the disk.  
2. Linked – each file is linked list of disk blocks. the disk blocks may be sca ered anywhere on the disk.  
3. Indexed – index is maintained for the list of all blocks used by the file. */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_FILES 100
#define MAX_BLOCKS 100
#define MAX_NAME 50

// Structure to store file information
typedef struct {
    char name[MAX_NAME];
    int start_block;
    int num_blocks;
    int blocks[MAX_BLOCKS];
} File;

// ==================== CONTIGUOUS ALLOCATION ====================
void contiguous_allocation() {
    int n_files;
    File files[MAX_FILES];
    char search_name[MAX_NAME];
    
    printf("\n========================================\n");
    printf("  Contiguous File Allocation\n");
    printf("========================================\n\n");
    
    printf("Enter number of files: ");
    scanf("%d", &n_files);
    
    // Input file details
    for (int i = 0; i < n_files; i++) {
        printf("Enter file %d name: ", i + 1);
        scanf("%s", files[i].name);
        
        printf("Enter starting block of file %d: ", i + 1);
        scanf("%d", &files[i].start_block);
        
        printf("Enter no of blocks in file %d: ", i + 1);
        scanf("%d", &files[i].num_blocks);
        
        // Generate contiguous blocks
        for (int j = 0; j < files[i].num_blocks; j++) {
            files[i].blocks[j] = files[i].start_block + j;
        }
        printf("\n");
    }
    
    // Search for file
    printf("Enter the file name to be searched: ");
    scanf("%s", search_name);
    
    // Find and display file
    bool found = false;
    for (int i = 0; i < n_files; i++) {
        if (strcmp(files[i].name, search_name) == 0) {
            found = true;
            printf("\n%-15s %-15s %-20s %s\n", "File Name", "Start block", "No. of blocks", "Blocks occupied");
            printf("--------------------------------------------------------------------------------\n");
            printf("%-15s %-15d %-20d ", files[i].name, files[i].start_block, files[i].num_blocks);
            
            for (int j = 0; j < files[i].num_blocks; j++) {
                printf("%d", files[i].blocks[j]);
                if (j < files[i].num_blocks - 1) printf(", ");
            }
            printf("\n");
            break;
        }
    }
    
    if (!found) {
        printf("\nFile not found!\n");
    }
}

// ==================== LINKED ALLOCATION ====================
void linked_allocation() {
    int n_files;
    File files[MAX_FILES];
    char search_name[MAX_NAME];
    
    printf("\n========================================\n");
    printf("  Linked File Allocation\n");
    printf("========================================\n\n");
    
    printf("Enter number of files: ");
    scanf("%d", &n_files);
    
    // Input file details
    for (int i = 0; i < n_files; i++) {
        printf("Enter file %d name: ", i + 1);
        scanf("%s", files[i].name);
        
        printf("Enter starting block of file %d: ", i + 1);
        scanf("%d", &files[i].start_block);
        
        printf("Enter no of blocks in file %d: ", i + 1);
        scanf("%d", &files[i].num_blocks);
        
        printf("Enter blocks for file %d: ", i + 1);
        for (int j = 0; j < files[i].num_blocks; j++) {
            scanf("%d", &files[i].blocks[j]);
        }
        printf("\n");
    }
    
    // Search for file
    printf("Enter the file name to be searched: ");
    scanf("%s", search_name);
    
    // Find and display file
    bool found = false;
    for (int i = 0; i < n_files; i++) {
        if (strcmp(files[i].name, search_name) == 0) {
            found = true;
            printf("\n%-15s %-15s %-20s %s\n", "File Name", "Start block", "No. of blocks", "Blocks occupied");
            printf("--------------------------------------------------------------------------------\n");
            printf("%-15s %-15d %-20d ", files[i].name, files[i].start_block, files[i].num_blocks);
            
            for (int j = 0; j < files[i].num_blocks; j++) {
                printf("%d", files[i].blocks[j]);
                if (j < files[i].num_blocks - 1) printf(", ");
            }
            printf("\n");
            break;
        }
    }
    
    if (!found) {
        printf("\nFile not found!\n");
    }
}

// ==================== INDEXED ALLOCATION ====================
void indexed_allocation() {
    int n_files;
    File files[MAX_FILES];
    char search_name[MAX_NAME];
    
    printf("\n========================================\n");
    printf("  Indexed File Allocation\n");
    printf("========================================\n\n");
    
    printf("Enter number of files: ");
    scanf("%d", &n_files);
    
    // Input file details
    for (int i = 0; i < n_files; i++) {
        printf("Enter file %d name: ", i + 1);
        scanf("%s", files[i].name);
        
        printf("Enter index block of file %d: ", i + 1);
        scanf("%d", &files[i].start_block);
        
        printf("Enter no of blocks in file %d: ", i + 1);
        scanf("%d", &files[i].num_blocks);
        
        printf("Enter blocks for file %d: ", i + 1);
        for (int j = 0; j < files[i].num_blocks; j++) {
            scanf("%d", &files[i].blocks[j]);
        }
        printf("\n");
    }
    
    // Search for file
    printf("Enter the file name to be searched: ");
    scanf("%s", search_name);
    
    // Find and display file
    bool found = false;
    for (int i = 0; i < n_files; i++) {
        if (strcmp(files[i].name, search_name) == 0) {
            found = true;
            printf("\n%-15s %-15s %-20s %s\n", "File Name", "Index block", "No. of blocks", "Blocks occupied");
            printf("--------------------------------------------------------------------------------\n");
            printf("%-15s %-15d %-20d ", files[i].name, files[i].start_block, files[i].num_blocks);
            
            for (int j = 0; j < files[i].num_blocks; j++) {
                printf("%d", files[i].blocks[j]);
                if (j < files[i].num_blocks - 1) printf(", ");
            }
            printf("\n");
            break;
        }
    }
    
    if (!found) {
        printf("\nFile not found!\n");
    }
}

// ==================== MAIN FUNCTION ====================
int main() {
    int choice;
    
    printf("========================================\n");
    printf("  File Allocation Strategies\n");
    printf("========================================\n");
    printf("1. Contiguous Allocation\n");
    printf("2. Linked Allocation\n");
    printf("3. Indexed Allocation\n");
    printf("========================================\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    
    switch(choice) {
        case 1:
            contiguous_allocation();
            break;
        case 2:
            linked_allocation();
            break;
        case 3:
            indexed_allocation();
            break;
        default:
            printf("Invalid choice!\n");
            return 1;
    }
    
    printf("\n========================================\n");
    
    return 0;
}