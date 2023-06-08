// Dhruv Rajeshkumar Shah
// 21BCE0611

// Round Robin (RR) Scheduling Algorithm
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

int main() {
    int n;
    int quantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    printf("Enter the time quantum: ");
    scanf("%d", &quantum);

    int burst_time[MAX_SIZE], remaining_time[MAX_SIZE];
    int completion_time[MAX_SIZE], waiting_time[MAX_SIZE], turnaround_time[MAX_SIZE], process_id[MAX_SIZE];
    int total_waiting_time = 0, total_turnaround_time = 0;

    // Taking input for burst time of each process
    printf("Enter the burst time of each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Enter process ID of the process: ");
        scanf("%d", &process_id[i]);
        printf("Burst time of process ID %d: ", process_id[i]);
        scanf("%d", &burst_time[i]);
        printf("\n");
        remaining_time[i] = burst_time[i];  // Initialize remaining time with burst time
    }

    int current_time = 0;
    int completed_processes = 0;

    while (completed_processes < n) {
        for (int i = 0; i < n; i++) {
            if (remaining_time[i] > 0) {
                if (remaining_time[i] <= quantum) {
                    current_time += remaining_time[i];
                    remaining_time[i] = 0;
                    completion_time[i] = current_time;
                    waiting_time[i] = completion_time[i] - burst_time[i];
                    turnaround_time[i] = completion_time[i];
                    total_waiting_time += waiting_time[i];
                    total_turnaround_time += turnaround_time[i];
                    completed_processes++;
                } else {
                    current_time += quantum;
                    remaining_time[i] -= quantum;
                }
            }
        }
    }

    // Printing the table
    printf("\nProcess ID\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", process_id[i], burst_time[i], completion_time[i], waiting_time[i], turnaround_time[i]);
    }

    // Printing the average waiting time and average turnaround time
    printf("\nAverage waiting time: %.2f\n", (float)total_waiting_time / n);
    printf("Average turnaround time: %.2f\n", (float)total_turnaround_time / n);

    return 0;
}