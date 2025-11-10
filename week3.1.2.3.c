//a) FCFS – First Come First Served : process which arrives first will get the CPU first. 
//b) SJF NP – Shortest Job First Non-Preemptive : process which needs CPU for least amount will 
//get the CPU first. Here non-preemptive means currently running process leaves CPU voluntarily after completing its execution. 
//c) SJF P – Shortest Job First Preemptive – Here preemptive means operating system decides when 
to move currently running process. 
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

typedef struct {
    int pid;
    int burst_time;
    int arrival_time;
    int remaining_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
} Process;

void fcfs(Process p[], int n) {
    int current_time = 0;
    float total_wt = 0, total_tat = 0;
    
    printf("\nGantt Chart: ");
    
    for (int i = 0; i < n; i++) {
        if (current_time < p[i].arrival_time)
            current_time = p[i].arrival_time;
        
        printf("P%d ", p[i].pid);
        
        p[i].completion_time = current_time + p[i].burst_time;
        p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
        p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
        
        current_time = p[i].completion_time;
        total_wt += p[i].waiting_time;
        total_tat += p[i].turnaround_time;
    }
    
    printf("\nAverage waiting time: %.2f", total_wt / n);
    printf("\nAverage turnaround time: %.2f\n", total_tat / n);
}

void sjf_non_preemptive(Process p[], int n) {
    int completed = 0, current_time = 0;
    bool is_completed[n];
    float total_wt = 0, total_tat = 0;
    
    for (int i = 0; i < n; i++)
        is_completed[i] = false;
    
    printf("\nGantt Chart: ");
    
    while (completed != n) {
        int idx = -1;
        int min_burst = INT_MAX;
        
        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= current_time && !is_completed[i]) {
                if (p[i].burst_time < min_burst) {
                    min_burst = p[i].burst_time;
                    idx = i;
                } else if (p[i].burst_time == min_burst) {
                    if (p[i].arrival_time < p[idx].arrival_time)
                        idx = i;
                }
            }
        }
        
        if (idx != -1) {
            printf("P%d ", p[idx].pid);
            current_time += p[idx].burst_time;
            p[idx].completion_time = current_time;
            p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
            p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
            
            total_wt += p[idx].waiting_time;
            total_tat += p[idx].turnaround_time;
            
            is_completed[idx] = true;
            completed++;
        } else {
            current_time++;
        }
    }
    
    printf("\nAverage waiting time: %.2f", total_wt / n);
    printf("\nAverage turnaround time: %.2f\n", total_tat / n);
}

void sjf_preemptive(Process p[], int n) {
    int completed = 0, current_time = 0;
    int prev_process = -1;
    float total_wt = 0, total_tat = 0;
    
    for (int i = 0; i < n; i++)
        p[i].remaining_time = p[i].burst_time;
    
    printf("\nGantt Chart: ");
    
    while (completed != n) {
        int idx = -1;
        int min_remaining = INT_MAX;
        
        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= current_time && p[i].remaining_time > 0) {
                if (p[i].remaining_time < min_remaining) {
                    min_remaining = p[i].remaining_time;
                    idx = i;
                } else if (p[i].remaining_time == min_remaining) {
                    if (p[i].arrival_time < p[idx].arrival_time)
                        idx = i;
                }
            }
        }
        
        if (idx != -1) {
            if (prev_process != idx) {
                printf("P%d ", p[idx].pid);
                prev_process = idx;
            }
            
            p[idx].remaining_time--;
            current_time++;
            
            if (p[idx].remaining_time == 0) {
                p[idx].completion_time = current_time;
                p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
                p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
                
                total_wt += p[idx].waiting_time;
                total_tat += p[idx].turnaround_time;
                completed++;
            }
        } else {
            current_time++;
        }
    }
    
    printf("\nAverage waiting time: %.2f", total_wt / n);
    printf("\nAverage turnaround time: %.2f\n", total_tat / n);
}

int main() {
    int n, choice;
    
    printf("Number of processes: ");
    scanf("%d", &n);
    
    Process p[n];
    
    printf("Burst time: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i].burst_time);
        p[i].pid = i;
    }
    
    printf("Arrival time: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i].arrival_time);
    }
    
    printf("\nSelect Scheduling Algorithm:\n");
    printf("1. FCFS (First Come First Served)\n");
    printf("2. SJF NP (Shortest Job First - Non-Preemptive)\n");
    printf("3. SJF P (Shortest Job First - Preemptive)\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    
    switch(choice) {
        case 1:
            fcfs(p, n);
            break;
        case 2:
            sjf_non_preemptive(p, n);
            break;
        case 3:
            sjf_preemptive(p, n);
            break;
        default:
            printf("Invalid choice!\n");
    }
    
    return 0;
}