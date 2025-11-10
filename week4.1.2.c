/*Given a list of processes, their CPU burst mes and arrival mes, print the Gan chart for the 
following given scheduling policies. Also find average wai ng me and average turnaround me 
required for complete execu on of these processes. 
a) Priority  – process which has highest priority will get CPU first. 
b) Round Robin – each process is provided a fix me to execute. Once a process is executed for a 
given me period, it is preempted and other process executes for the given me period.*/
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

typedef struct {
    int pid;
    int burst_time;
    int arrival_time;
    int priority;
    int remaining_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
} Process;

void priority_scheduling(Process p[], int n) {
    int completed = 0, current_time = 0;
    bool is_completed[n];
    float total_wt = 0, total_tat = 0;
    
    for (int i = 0; i < n; i++) {
        is_completed[i] = false;
        p[i].remaining_time = p[i].burst_time;
    }
    
    printf("\nGantt Chart: ");
    
    while (completed != n) {
        int idx = -1;
        int highest_priority = INT_MIN;
        
        // Find process with highest priority that has arrived
        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= current_time && !is_completed[i]) {
                if (p[i].priority > highest_priority) {
                    highest_priority = p[i].priority;
                    idx = i;
                } else if (p[i].priority == highest_priority) {
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

void round_robin(Process p[], int n, int time_quantum) {
    int current_time = 0;
    int completed = 0;
    float total_wt = 0, total_tat = 0;
    int queue[100], front = 0, rear = 0;
    bool in_queue[n];
    
    for (int i = 0; i < n; i++) {
        p[i].remaining_time = p[i].burst_time;
        in_queue[i] = false;
    }
    
    // Add first process that arrives at time 0
    for (int i = 0; i < n; i++) {
        if (p[i].arrival_time == 0) {
            queue[rear++] = i;
            in_queue[i] = true;
        }
    }
    
    printf("\nGantt Chart: ");
    
    while (completed != n) {
        if (front == rear) {
            // Queue is empty, find next arriving process
            int next_arrival = INT_MAX;
            for (int i = 0; i < n; i++) {
                if (p[i].remaining_time > 0 && p[i].arrival_time > current_time) {
                    if (p[i].arrival_time < next_arrival)
                        next_arrival = p[i].arrival_time;
                }
            }
            if (next_arrival != INT_MAX) {
                current_time = next_arrival;
                for (int i = 0; i < n; i++) {
                    if (p[i].arrival_time <= current_time && p[i].remaining_time > 0 && !in_queue[i]) {
                        queue[rear++] = i;
                        in_queue[i] = true;
                    }
                }
            }
            continue;
        }
        
        int idx = queue[front++];
        in_queue[idx] = false;
        
        printf("P%d ", p[idx].pid);
        
        int exec_time = (p[idx].remaining_time > time_quantum) ? time_quantum : p[idx].remaining_time;
        
        p[idx].remaining_time -= exec_time;
        current_time += exec_time;
        
        // Add newly arrived processes to queue
        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= current_time && p[i].remaining_time > 0 && !in_queue[i] && i != idx) {
                queue[rear++] = i;
                in_queue[i] = true;
            }
        }
        
        // If current process still has remaining time, add it back to queue
        if (p[idx].remaining_time > 0) {
            queue[rear++] = idx;
            in_queue[idx] = true;
        } else {
            // Process completed
            p[idx].completion_time = current_time;
            p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
            p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
            
            total_wt += p[idx].waiting_time;
            total_tat += p[idx].turnaround_time;
            completed++;
        }
    }
    
    printf("\nAverage waiting time: %.2f", total_wt / n);
    printf("\nAverage turnaround time: %.2f\n", total_tat / n);
}

int main() {
    int n, choice, time_quantum;
    
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
    printf("1. Priority Scheduling\n");
    printf("2. Round Robin\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    
    switch(choice) {
        case 1:
            printf("Priority: ");
            for (int i = 0; i < n; i++) {
                scanf("%d", &p[i].priority);
            }
            priority_scheduling(p, n);
            break;
        case 2:
            printf("Time Quantum: ");
            scanf("%d", &time_quantum);
            round_robin(p, n, time_quantum);
            break;
        default:
            printf("Invalid choice!\n");
    }
    
    return 0;
}