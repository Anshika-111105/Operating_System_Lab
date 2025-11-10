# Operating System Lab

## Course Overview

The Operating System Lab is designed to provide practical exposure to how modern operating systems manage resources, handle concurrency, and schedule processes efficiently. Each lab reinforces theoretical understanding through hands-on coding exercises.

## Weekly Topics & Experiments

### Week 1–2: System Calls
- Create and manage child processes using `fork()`, `wait()`, `exit()`
- Display parent and child process IDs using `getpid()`, `getppid()`
- Implement Orphan and Zombie processes
- Directory and file operations using `opendir()`, `readdir()`, `open()`, `read()`, `write()`, and `close()`
- Execute external commands using `execlp()` system call

### Week 3–4: Process Scheduling Algorithms
- FCFS (First Come First Served)
- SJF (Shortest Job First – Preemptive & Non-Preemptive)
- Priority Scheduling
- Round Robin (with Time Quantum)

**Output includes:** Gantt Chart, Average Waiting Time, and Average Turnaround Time

### Week 5: Deadlock Handling
- Banker's Algorithm for Deadlock Avoidance
- Deadlock Detection Algorithm with process-resource matrices

### Week 6: Process Synchronization
- Inter-process communication using Pipes, Message Passing, and Shared Memory
- Implement Producer–Consumer Problem using Semaphores
- Implement Dining Philosopher Problem

### Week 7: Page Replacement Algorithms
- FIFO (First In First Out)
- LRU (Least Recently Used)

Calculates total number of page faults for given page requests.

### Week 8: Memory Allocation Techniques
- Best Fit
- First Fit
- Worst Fit

Simulates allocation of processes into available memory blocks.

### Week 9–10: File Allocation Strategies
- Contiguous Allocation
- Linked Allocation
- Indexed Allocation

Demonstrates how files occupy disk blocks and how they can be retrieved efficiently.

### Week 11–12: Disk Scheduling Algorithms
- FCFS (First Come First Serve)
- SCAN (Elevator Algorithm)
- C-SCAN (Circular SCAN)

Calculates total head movement (seek time) for given disk requests.

## Tech Stack

- **Language:** C
- **Platform:** Linux/Unix
- **Compiler:** GCC
- **Editor:** VS Code / Terminal

## Learning Outcomes

- Understand internal working of operating systems
- Gain experience with process management, scheduling, and synchronization
- Implement memory, file, and disk management algorithms
- Develop debugging and system-level programming skills in C

## 📁 Repository Structure

```
📦 Operating-System-Lab
├── Week1_2_System_Calls/
├── Week3_4_Scheduling/
├── Week5_Deadlock/
├── Week6_Synchronization/
├── Week7_Page_Replacement/
├── Week8_Memory_Allocation/
├── Week9_10_File_Allocation/
├── Week11_12_Disk_Scheduling/
└── README.md
```

## Author

**Anshika Saklani**  
B.Tech (Computer Science & Engineering)  
Graphic Era Hill University

---

*This repository contains practical implementations of core operating system concepts through structured weekly exercises.*
