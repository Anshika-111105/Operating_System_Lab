//Disc Scheduling Algorithms 
#include <stdio.h>
#include <stdlib.h>

#define MAX 200  // Total number of tracks (0–199)

void sort(int arr[], int n) {
    // Simple Bubble Sort for ordering requests
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int fcfs(int requests[], int n, int head) {
    int seek_time = 0;
    for (int i = 0; i < n; i++) {
        seek_time += abs(requests[i] - head);
        head = requests[i];
    }
    return seek_time;
}

int scan(int requests[], int n, int head, int direction) {
    int seek_time = 0;
    int temp[MAX], size = 0;

    for (int i = 0; i < n; i++)
        temp[i] = requests[i];
    temp[n] = head;
    size = n + 1;

    sort(temp, size);

    int pos;
    for (int i = 0; i < size; i++) {
        if (temp[i] == head) {
            pos = i;
            break;
        }
    }

    // Move right first
    if (direction == 1) {
        for (int i = pos; i < size - 1; i++)
            seek_time += abs(temp[i + 1] - temp[i]);
        seek_time += abs(MAX - 1 - temp[size - 1]);
        for (int i = pos - 1; i >= 0; i--)
            seek_time += abs(temp[i + 1] - temp[i]);
    }
    // Move left first
    else {
        for (int i = pos; i > 0; i--)
            seek_time += abs(temp[i] - temp[i - 1]);
        seek_time += abs(temp[0] - 0);
        for (int i = pos + 1; i < size; i++)
            seek_time += abs(temp[i] - temp[i - 1]);
    }
    return seek_time;
}

int cscan(int requests[], int n, int head, int direction) {
    int seek_time = 0;
    int temp[MAX], size = 0;

    for (int i = 0; i < n; i++)
        temp[i] = requests[i];
    temp[n] = head;
    size = n + 1;

    sort(temp, size);

    int pos;
    for (int i = 0; i < size; i++) {
        if (temp[i] == head) {
            pos = i;
            break;
        }
    }

    // Move right (towards higher track numbers)
    if (direction == 1) {
        for (int i = pos; i < size - 1; i++)
            seek_time += abs(temp[i + 1] - temp[i]);
        seek_time += abs((MAX - 1) - temp[size - 1]);
        seek_time += (MAX - 1);  // Jump from end to start
        for (int i = 0; i < pos; i++)
            seek_time += abs(temp[i + 1] - temp[i]);
    }
    // Move left (towards lower track numbers)
    else {
        for (int i = pos; i > 0; i--)
            seek_time += abs(temp[i] - temp[i - 1]);
        seek_time += abs(temp[0] - 0);
        seek_time += (MAX - 1);  // Jump from start to end
        for (int i = size - 1; i > pos; i--)
            seek_time += abs(temp[i] - temp[i - 1]);
    }

    return seek_time;
}

int main() {
    int n, head, choice, direction;
    printf("Enter number of disk requests: ");
    scanf("%d", &n);

    int requests[n];
    printf("Enter the track numbers: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &requests[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("\nChoose Disk Scheduling Algorithm:\n");
    printf("1. FCFS\n2. SCAN\n3. C-SCAN\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    if (choice == 2 || choice == 3) {
        printf("Enter direction (1 for right/up, 0 for left/down): ");
        scanf("%d", &direction);
    }

    int seek = 0;
    switch (choice) {
        case 1:
            seek = fcfs(requests, n, head);
            printf("\nTotal Seek Movement (FCFS): %d\n", seek);
            break;

        case 2:
            seek = scan(requests, n, head, direction);
            printf("\nTotal Seek Movement (SCAN): %d\n", seek);
            break;

        case 3:
            seek = cscan(requests, n, head, direction);
            printf("\nTotal Seek Movement (C-SCAN): %d\n", seek);
            break;

        default:
            printf("Invalid choice!\n");
    }

    return 0;
}
