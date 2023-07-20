// Dhruv Rajeshkumar Shah
// 21BCE0611

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int size;
    int allocated;
} Partition;

typedef struct {
    int size;
    int allocated;
    int partition_index;
} Process;

void printMemoryLayout(Partition partitions[], int num_partitions, Process processes[], int num_processes) {
    printf("\nMemory Layout:\n");
    for (int i = 0; i < num_partitions; i++) {
        printf("Partition %d: ", i + 1);
        if (partitions[i].allocated) {
            printf("Allocated to Process %d (Size: %d)\n", partitions[i].allocated, partitions[i].size);
        } else {
            printf("Free (Size: %d)\n", partitions[i].size);
        }
    }
    printf("\n");
    for (int i = 0; i < num_processes; i++) {
        printf("Process %d: ", i + 1);
        if (processes[i].allocated) {
            printf("Allocated in Partition %d (Size: %d)\n", processes[i].partition_index, processes[i].size);
        } else {
            printf("Not Allocated (Size: %d)\n", processes[i].size);
        }
    }
    printf("\n");
}

// Empty partitions and processes arrays
void emptyArrays(Partition partitions[], int num_partitions, Process processes[], int num_processes) {
    for (int i = 0; i < num_partitions; i++) {
        partitions[i].allocated = 0;
    }
    for (int i = 0; i < num_processes; i++) {
        processes[i].allocated = 0;
        processes[i].partition_index = -1;
    }
}

void firstFit(Partition partitions[], int num_partitions, Process processes[], int num_processes) {
    for (int i = 0; i < num_processes; i++) {
        for (int j = 0; j < num_partitions; j++) {
            if (!partitions[j].allocated && partitions[j].size >= processes[i].size) {
                partitions[j].allocated = i + 1;
                processes[i].allocated = 1;
                processes[i].partition_index = j + 1;
                break;
            }
        }
    }
    printMemoryLayout(partitions, num_partitions, processes, num_processes);
}

void bestFit(Partition partitions[], int num_partitions, Process processes[], int num_processes) {
    for (int i = 0; i < num_processes; i++) {
        int best_fit_index = -1;
        int best_fit_size = INT_MAX;
        for (int j = 0; j < num_partitions; j++) {
            if (!partitions[j].allocated && partitions[j].size >= processes[i].size && partitions[j].size < best_fit_size) {
                best_fit_index = j;
                best_fit_size = partitions[j].size;
            }
        }
        if (best_fit_index != -1) {
            partitions[best_fit_index].allocated = i + 1;
            processes[i].allocated = 1;
            processes[i].partition_index = best_fit_index + 1;
        }
    }
    printMemoryLayout(partitions, num_partitions, processes, num_processes);
}

void worstFit(Partition partitions[], int num_partitions, Process processes[], int num_processes) {
    for (int i = 0; i < num_processes; i++) {
        int worst_fit_index = -1;
        int worst_fit_size = -1;
        for (int j = 0; j < num_partitions; j++) {
            if (!partitions[j].allocated && partitions[j].size >= processes[i].size && partitions[j].size > worst_fit_size) {
                worst_fit_index = j;
                worst_fit_size = partitions[j].size;
            }
        }
        if (worst_fit_index != -1) {
            partitions[worst_fit_index].allocated = i + 1;
            processes[i].allocated = 1;
            processes[i].partition_index = worst_fit_index + 1;
        }
    }
    printMemoryLayout(partitions, num_partitions, processes, num_processes);
}

int calculateWastedMemory(Partition partitions[], int num_partitions) {
    int wasted_memory = 0;
    for (int i = 0; i < num_partitions; i++) {
        if (!partitions[i].allocated) {
            wasted_memory += partitions[i].size;
        }
    }
    return wasted_memory;
}

int calculateNumUnallocatedProcesses(Process processes[], int num_processes) {
    int num_unallocated_processes = 0;
    for (int i = 0; i < num_processes; i++) {
        if (!processes[i].allocated) {
            num_unallocated_processes++;
        }
    }
    return num_unallocated_processes;
}

int main() {
    int num_partitions, num_processes;

    printf("Enter the number of partitions: ");
    scanf("%d", &num_partitions);

    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);

    int num_unallocatted[3] = {num_processes, num_processes, num_processes};
    int wasted_memory[3] = {0, 0, 0};

    Partition *partitions = malloc(num_partitions * sizeof(Partition));
    Process *processes = malloc(num_processes * sizeof(Process));

    printf("\nEnter the sizes of the partitions:\n");
    for (int i = 0; i < num_partitions; i++) {
        printf("Partition %d size: ", i + 1);
        scanf("%d", &(partitions[i].size));
        partitions[i].allocated = 0;
    }

    printf("\nEnter the sizes of the processes:\n");
    for (int i = 0; i < num_processes; i++) {
        printf("Process %d size: ", i + 1);
        scanf("%d", &(processes[i].size));
        processes[i].allocated = 0;
        processes[i].partition_index = -1;
    }

    printf("\nInitial Memory Layout:\n");
    printMemoryLayout(partitions, num_partitions, processes, num_processes);

    printf("\n\nFirst Fit:\n");
    firstFit(partitions, num_partitions, processes, num_processes);
    wasted_memory[0] = calculateWastedMemory(partitions, num_partitions);
    num_unallocatted[0] = calculateNumUnallocatedProcesses(processes, num_processes);
    printf("Wasted Memory: %d\n", wasted_memory[0]);
    printf("Unallocated Processes: %d\n", num_unallocatted[0]);
    emptyArrays(partitions, num_partitions, processes, num_processes);

    printf("\n\nBest Fit:\n");
    bestFit(partitions, num_partitions, processes, num_processes);
    wasted_memory[1] = calculateWastedMemory(partitions, num_partitions);
    num_unallocatted[1] = calculateNumUnallocatedProcesses(processes, num_processes);
    printf("Wasted Memory: %d\n", wasted_memory[1]);
    printf("Unallocated Processes: %d\n", num_unallocatted[1]);
    emptyArrays(partitions, num_partitions, processes, num_processes);

    printf("\n\nWorst Fit:\n");
    worstFit(partitions, num_partitions, processes, num_processes);
    wasted_memory[2] = calculateWastedMemory(partitions, num_partitions);
    num_unallocatted[2] = calculateNumUnallocatedProcesses(processes, num_processes);
    printf("Wasted Memory: %d\n", wasted_memory[2]);
    printf("Unallocated Processes: %d\n", num_unallocatted[2]);
    emptyArrays(partitions, num_partitions, processes, num_processes);

    free(partitions);
    free(processes);
    
    return 0;
}
