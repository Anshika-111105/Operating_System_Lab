//Write a program to open (use opendir(), readdir(), closedir() ) a directory and list its contents.  
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
int main() {
    DIR *dir;
    struct dirent *entry;
    char dirname[256];
    int count = 0;
    printf("======================================\n");
    printf("     DIRECTORY LISTING PROGRAM\n");
    printf("======================================\n\n");
    printf("Enter directory path (e.g., . for current, / for root): ");
    scanf("%s", dirname);
    dir = opendir(dirname);
    if (dir == NULL) {
        perror("Error opening directory");
        return 1;
    }
    printf("\nContents of directory '%s':\n", dirname);
    printf("--------------------------------------\n");
    
    while ((entry = readdir(dir)) != NULL) {
        count++;
        printf("%3d. %s", count, entry->d_name);
        
        if (entry->d_type == DT_DIR) {
            printf(" [Directory]");
        } else if (entry->d_type == DT_REG) {
            printf(" [File]");
        } else if (entry->d_type == DT_LNK) {
            printf(" [Link]");
        }
        
        printf("\n");
    }
    printf("--------------------------------------\n");
    printf("Total entries: %d\n\n", count);
    closedir(dir);
    return 0;
}