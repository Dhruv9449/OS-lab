// Dhruv Rajeshkumar Shah
// 21BCE0611

// Priority Scheduling
#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int burst_time[n], priority[n], completion_time[n], waiting_time[n], turnaround_time[n], process_id[n];
    int total_waiting_time = 0, total_turnaround_time = 0;

    // Taking input for burst time and priority
    printf("Enter the burst time and priority of each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Enter process ID of the process: ");
        scanf("%d", &process_id[i]);
        printf("Burst time of process ID %d: ", process_id[i]);
        scanf("%d", &burst_time[i]);
        printf("Priority of process ID %d: ", process_id[i]);
        scanf("%d", &priority[i]);
        printf("\n");
    }

    // Sort the processes based on priority (in ascending order)
    for (int i = 0; i < n; i++) {
        for(int j=i+1; j < n; j++) {
            if(priority[i] > priority[j]) {
                int temp = burst_time[i];
                burst_time[i] = burst_time[j];
                burst_time[j] = temp;

                temp = priority[i];
                priority[i] = priority[j];
                priority[j] = temp;

                temp = process_id[i];
                process_id[i] = process_id[j];
                process_id[j] = temp;
            }
        }
    }

    // Calculating completion time
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            completion_time[i] = burst_time[i];
        } else {
            completion_time[i] = completion_time[i-1] + burst_time[i];
        }
    }

    // Calculating waiting time and turnaround time
    for (int i = 0; i < n; i++) {
        waiting_time[i] = completion_time[i] - burst_time[i];
        turnaround_time[i] = completion_time[i];
        total_waiting_time += waiting_time[i];
        total_turnaround_time += turnaround_time[i];
    }

    // Printing the table
    printf("\nProcess ID\tBurst Time\tPriority\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", process_id[i], burst_time[i], priority[i], completion_time[i], waiting_time[i], turnaround_time[i]);
    }

    // Printing the average waiting time and average turnaround time
    printf("\nAverage waiting time: %f\n", (float)total_waiting_time / n);
    printf("Average turnaround time: %f\n", (float)total_turnaround_time / n);

    return 0;
}
