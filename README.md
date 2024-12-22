# Operating Systems Concepts and Solutions

This repository contains C-based implementations of key Operating Systems concepts, including process management, inter-process communication, system command simulation, and CPU scheduling algorithms.

## Features

1. **Mean Calculation Using Child Processes**  
   - Parent process spawns 7 child processes.  
   - Each child calculates the mean of 4 random integers.  
   - Demonstrates process creation and synchronization.  
   **File:** `q1.c`

2. **Binary Search Using Forking Processes**  
   - Implements recursive binary search via process forking.  
   - Demonstrates inter-process communication and recursion.  
   **File:** `q2.c`

3. **Custom System Commands**  
   - Simulates `date`, `cal`, and `uptime` commands.  
   - Demonstrates process management with `fork()` and `exec()`.  
   **Folder:** `q3/`  
   - Use the provided `Makefile` to compile all commands.

4. **CPU Scheduling Algorithms**  
   - Simulates FIFO, SJF, SRTF, and Round Robin scheduling.  
   - Displays execution order, response time, and turnaround time.  
   **File:** `q4.c`

## Setup and Execution

### Prerequisites
- GCC Compiler (Linux or Windows Subsystem for Linux).

### Compilation
- Compile individual programs:  
  ```bash
  gcc q1.c -o q1
  gcc q2.c -o q2
  gcc q4.c -o q4
