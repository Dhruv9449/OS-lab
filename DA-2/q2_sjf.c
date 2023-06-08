// Dhruv Rajeshkumar Shah
// 21BCE0611

// Shortest Job First (SJF) Scheduling Algorithm
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int arrival_time[n], burst_time[n], completion_time[n], waiting_time[n], turnaround_time[n], process_id[n];
    int total_waiting_time = 0, total_turnaround_time = 0;

    // Taking input for arrival time and burst time
    printf("Enter the arrival time and burst time of each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Enter process ID of the process: ");
        scanf("%d", &process_id[i]);
        printf("Burst time of process ID %d: ", process_id[i]);
        scanf("%d", &burst_time[i]);
        printf("\n");
    }

    // Initialize arrival time with 0 (assuming all processes arrive at the same time)
    for (int i = 0; i < n; i++) {
        arrival_time[i] = 0;
    }

    // Initialize burst_time_left with the burst time
    int burst_time_left[n];
    for (int i = 0; i < n; i++) {
        burst_time_left[i] = burst_time[i];
    }

    int current_time = 0;
    int completed_processes = 0;

    while (completed_processes < n) {
        int shortest_burst_index = -1;
        int shortest_burst = INT_MAX;

        // Finding the process with the shortest burst time among the arrived processes
        for (int i = 0; i < n; i++) {
            if (burst_time_left[i] > 0) {
                if (burst_time_left[i] < shortest_burst) {
                    shortest_burst = burst_time_left[i];
                    shortest_burst_index = i;
                }
            }
        }

        if (shortest_burst_index == -1) {
            current_time++; // No process to execute, move to the next second
            continue;
        }

        // Updating completion time
        completion_time[shortest_burst_index] = current_time + burst_time_left[shortest_burst_index];

        // Updating waiting time and turnaround time
        waiting_time[shortest_burst_index] = current_time;
        turnaround_time[shortest_burst_index] = completion_time[shortest_burst_index] - arrival_time[shortest_burst_index];

        // Updating total waiting time and total turnaround time
        total_waiting_time += waiting_time[shortest_burst_index];
        total_turnaround_time += turnaround_time[shortest_burst_index];

        // Mark the process as completed by setting burst time left to 0
        burst_time_left[shortest_burst_index] = 0;

        // Incrementing completed processes count
        completed_processes++;

        // Move to the completion time of the next process
        current_time = completion_time[shortest_burst_index];
    }

    // Printing the table
    printf("\nProcess ID\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", process_id[i], burst_time[i], completion_time[i], waiting_time[i], turnaround_time[i]);
    }

    // Printing the average waiting time and average turnaround time
    printf("\nAverage waiting time: %f\n", (float)total_waiting_time / n);
    printf("Average turnaround time: %f\n", (float)total_turnaround_time / n);

    return 0;
}
