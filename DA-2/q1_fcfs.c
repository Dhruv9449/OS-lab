// Dhruv Rajeshkumar Shah
// 21BCE0611

#include <stdio.h>
#include <stdlib.h>


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
        printf("Arrival time of process ID %d: ", process_id[i]);
        scanf("%d", &arrival_time[i]);
        printf("Burst time of process ID %d: ", process_id[i]);
        scanf("%d", &burst_time[i]);
        printf("\n");
    }

    // Sort based on arrival time of processes
    for (int i = 0; i < n; i++) {
        for(int j=i+1; j < n; j++) {
            if(arrival_time[i] > arrival_time[j]) {
                int temp = arrival_time[i];
                arrival_time[i] = arrival_time[j];
                arrival_time[j] = temp;

                temp = burst_time[i];
                burst_time[i] = burst_time[j];
                burst_time[j] = temp;

                temp = process_id[i];
                process_id[i] = process_id[j];
                process_id[j] = temp;
            }
        }
    }

    // Calculating completion time
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            completion_time[i] = arrival_time[i] + burst_time[i];
        } else {
            if (arrival_time[i] > completion_time[i-1]) {
                completion_time[i] = arrival_time[i] + burst_time[i];
            } else {
                completion_time[i] = completion_time[i-1] + burst_time[i];
            }
        }
    }

    // Calculating waiting time and turnaround time
    for (int i = 0; i < n; i++) {
        waiting_time[i] = completion_time[i] - arrival_time[i] - burst_time[i];
        turnaround_time[i] = completion_time[i] - arrival_time[i];
        total_waiting_time += waiting_time[i];
        total_turnaround_time += turnaround_time[i];
    }

    // Printing the table
    printf("\nProcess ID\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", process_id[i], arrival_time[i], burst_time[i], completion_time[i], waiting_time[i], turnaround_time[i]);
    }

    // Printing the average waiting time and average turnaround time
    printf("\nAverage waiting time: %f\n", (float)total_waiting_time / n);
    printf("Average turnaround time: %f\n", (float)total_turnaround_time / n);

    return 0;
}