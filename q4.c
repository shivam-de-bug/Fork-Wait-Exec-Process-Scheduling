/*Write a c program to simulate the different CPU scheduling algorithms. Four
  scheduling algorithms should be implemented in the program:
  1. First In First Out (FIFO)
  2. Shortest Job First (SJF)
  3. Shortest Remaining Time First (SRTF)
  4. Round Robin (RR)
  The program should accept input for n processes (n>4), where each process has:
  ● Process ID: A unique identifier for the process.
  ● Arrival Time: The time at which the process arrives in the ready queue.
  ● Burst Time: The total time required by the process for execution.
  ● Time Quantum (TQ): The value of TQ should only be used in RR.
  For each scheduling algorithm, the program should:
  ● Calculate and display the order of execution of processes.
  ● Calculate and display the scheduling policy's Average Response Time and
  Average Turnaround Time.*/

  #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_PROC 100
#define MAX_ID_LENGTH 15


void swap_int(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}


void swap_str(char *a, char *b) {
    char tmp[MAX_ID_LENGTH];
    strcpy(tmp, a);
    strcpy(a, b);
    strcpy(b, tmp);
}


void sort_arr(int n, int at[], int bt[], char id[][MAX_ID_LENGTH]) {
    int i = 0, j;
    while (i < n - 1) {
        j = i + 1;
        while (j < n) {
            if (at[i] > at[j]) {
                swap_int(&at[i], &at[j]);
                swap_int(&bt[i], &bt[j]);
                swap_str(id[i], id[j]);
            }
            j++;
        }
        i++;
    }
}


void sort_burst(int n, int at[], int bt[], char id[][MAX_ID_LENGTH]) {
    int i = 0, j;
    while (i < n - 1) {
        j = i + 1;
        while (j < n) {
            if (bt[i] > bt[j] && at[i] <= at[j]) {
                swap_int(&at[i], &at[j]);
                swap_int(&bt[i], &bt[j]);
                swap_str(id[i], id[j]);
            }
            j++;
        }
        i++;
    }
}


void avg_times(int n, int ct[], int at[], int rt[]) {
    float tt = 0, rt_total = 0;
    int i = 0;
    while (i < n) {
        int ttt = ct[i] - at[i];
        tt += ttt;
        rt_total += rt[i];
        i++;
    }
    printf("Average Turnaround Time: %.2f\n", tt / n);
    printf("Average Response Time: %.2f\n", rt_total / n);
}


void fcfs_sched(int n, int at[], int bt[], char id[][MAX_ID_LENGTH]) {
    int ct[MAX_PROC + 2], wt[MAX_PROC + 2], rt[MAX_PROC + 2];
    int cur_time = 0;
    int i = 0;

    printf("\nFCFS Execution Order: ");
    while (i < n) {
        if (cur_time < at[i]) {
            cur_time = at[i];
        }

        ct[i] = cur_time + bt[i];
        wt[i] = cur_time - at[i];
        rt[i] = wt[i];

        printf("%s ", id[i]);
        cur_time += bt[i];
        i++;
    }
    printf("\n");

    avg_times(n, ct, at, rt);
}


void sjf_sched(int n, int at[], int bt[], char id[][MAX_ID_LENGTH]) {
    sort_burst(n, at, bt, id);
    int ct[MAX_PROC + 2], wt[MAX_PROC + 2], rt[MAX_PROC + 2];
    int cur_time = 0, pc = 0;
    int i = 0;

    printf("\nSJF Execution Order: ");
    while (pc < n) {
        int min_idx = -1, min_bt = INT_MAX;
        i = 0;

        while (i < n) {
            if (at[i] <= cur_time && bt[i] < min_bt) {
                min_bt = bt[i];
                min_idx = i;
            }
            i++;
        }

        if (min_idx != -1) {
            ct[min_idx] = cur_time + bt[min_idx];
            wt[min_idx] = cur_time - at[min_idx];
            rt[min_idx] = wt[min_idx];

            printf("%s ", id[min_idx]);

            cur_time += bt[min_idx];
            bt[min_idx] = INT_MAX; 
            pc++;
        } else {
            cur_time++;
        }
    }
    printf("\n");

    avg_times(n, ct, at, rt);
}


void srtf_sched(int n, int at[], int bt[], char id[][MAX_ID_LENGTH]) {
    int rt[MAX_PROC + 2], ct[MAX_PROC + 2], wt[MAX_PROC + 2], rt_arr[MAX_PROC + 2];
    int cur_time = 0, pc = 0;
    int i = 0, last_idx = -1;
    int is_comp[MAX_PROC + 2];
    
    while (i < n) {
        rt[i] = bt[i];
        is_comp[i] = 0;
        i++;
    }

    printf("\nSRTF Execution Order: ");
    while (pc < n) {
        int min_idx = -1, min_rt = INT_MAX;
        i = 0;

        while (i < n) {
            if (at[i] <= cur_time && rt[i] > 0 && rt[i] < min_rt) {
                min_rt = rt[i];
                min_idx = i;
            }
            i++;
        }

        if (min_idx != -1) {
            if (rt[min_idx] == bt[min_idx]) {
                rt_arr[min_idx] = cur_time - at[min_idx];
            }

            if (last_idx != min_idx) {
                printf("%s ", id[min_idx]);
                last_idx = min_idx;
            }

            cur_time++;
            rt[min_idx]--;

            if (rt[min_idx] == 0) {
                ct[min_idx] = cur_time;
                wt[min_idx] = ct[min_idx] - at[min_idx] - bt[min_idx];
                pc++;
                is_comp[min_idx] = 1;
                last_idx = -1;
            }
        } else {
            cur_time++;
        }
    }
    printf("\n");

    avg_times(n, ct, at, rt_arr);
}


void rr_sched(int n, int at[], int bt[], char id[][MAX_ID_LENGTH], int tq) {
    int rt[MAX_PROC + 2], ct[MAX_PROC + 2], tt[MAX_PROC + 2], wt[MAX_PROC + 2], rt_arr[MAX_PROC + 2];
    int cur_time = 0, completed = 0;
    int i = 0, total_tt = 0, total_rt = 0;
    int is_comp[MAX_PROC + 2], first_rt[MAX_PROC + 2];

    while (i < n) {
        rt[i] = bt[i];
        is_comp[i] = 0;
        first_rt[i] = -1;
        i++;
    }

    printf("\nRR Execution Order: ");
    while (completed < n) {
        int proc_exec = 0;
        i = 0;

        while (i < n) {
            if (at[i] <= cur_time && rt[i] > 0) {
                if (first_rt[i] == -1) {
                    rt_arr[i] = cur_time - at[i];
                    total_rt += rt_arr[i];
                    first_rt[i] = 1;
                }

                if (rt[i] > tq) {
                    cur_time += tq;
                    rt[i] -= tq;
                } else {
                    cur_time += rt[i];
                    rt[i] = 0;
                    completed++;
                    ct[i] = cur_time;
                    tt[i] = ct[i] - at[i];
                    total_tt += tt[i];
                }

                printf("%s ", id[i]);
                proc_exec = 1;
            }
            i++;
        }

        if (!proc_exec) {
            cur_time++;
        }
    }

    printf("\nAverage Turnaround Time: %.2f\n", (float)total_tt / n);
    printf("Average Response Time: %.2f\n", (float)total_rt / n);
}

int main() {
    int n, tq;
    int at[MAX_PROC], bt[MAX_PROC];
    char id[MAX_PROC][MAX_ID_LENGTH];

    printf("Number of Processes: ");
    scanf("%d", &n);

    int i = 0;
    while (i < n) {
        printf("Enter details for process %d (Process ID, Arrival Time, Burst Time): ", i + 1);
        scanf("%s %d %d", id[i], &at[i], &bt[i]);
        i++;
    }

    printf("Time Quantum for Round Robin: ");
    scanf("%d", &tq);

    sort_arr(n, at, bt, id);
    rr_sched(n, at, bt, id, tq);
    sort_arr(n, at, bt, id);
    srtf_sched(n, at, bt, id);
    sort_arr(n, at, bt, id);
    fcfs_sched(n, at, bt, id);
    sjf_sched(n, at, bt, id);

    return 0;
}
