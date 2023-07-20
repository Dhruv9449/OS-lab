// Dhruv Rajeshkumar Shah
// 21BCE0611

// Page replacement algorithms, hit and miss ratio
#include <stdio.h>
#include <stdlib.h>

// Function to print frames in main memory
void printFrames(int frame[], int capacity)
{
    printf("Frames: ");
    for (int i = 0; i < capacity; i++)
    {
        if (frame[i] == -1)
            printf(" ");
        else
            printf("%d", frame[i]);
    }
    printf("\n");
}

// Function to find the hit and miss using FIFO
void FIFOAlgorithm(int pages[], int n, int capacity)
{
    printf("\nFIFO Algorithm\n");
    // Create an array for given number of pages
    int frame[capacity];

    // Initialize all frames as empty
    for (int i = 0; i < capacity; i++)
        frame[i] = -1;

    // Initialize the number of faults as 0
    int faults = 0;

    // Traverse through all pages
    for (int i = 0; i < n; i++)
    {
        // Find if there is a need to change the frame
        int flag = 0, j;
        for (j = 0; j < capacity; j++)
        {
            if (frame[j] == pages[i])
            {
                flag = 1;
                break;
            }
        }

        // If the page is not present in the frame, replace the page using FIFO
        if (flag == 0)
        {
            frame[faults % capacity] = pages[i];
            faults++;
            printf("Miss |");
        }
        else
        {
            printf("Hit  |");
        }

        // Print the current set of frames
        printf("Page %d | ", pages[i]);
        printFrames(frame, capacity);
    }
    printf("\nNumber of hits = %d", n - faults);
    printf("\nHit Ratio = %f", (float)(n - faults) / n);
    printf("\nNumber of misses = %d", faults);
    printf("\nMiss Ratio = %f\n", (float)faults / n);
}

// Function to find the hit and miss using FIFO
void OptimalAlgorithm(int pages[], int n, int capacity)
{
    printf("\nOptimal Algorithm\n");
    // Create an array for given number of pages
    int frame[capacity];

    // Initialize all frames as empty
    for (int i = 0; i < capacity; i++)
        frame[i] = -1;

    // Initialize the number of faults as 0
    int faults = 0;

    // Traverse through all pages
    for (int i = 0; i < n; i++)
    {
        // Find if there is a need to change the frame
        int flag = 0, j;
        for (j = 0; j < capacity; j++)
        {
            if (frame[j] == pages[i])
            {
                flag = 1;
                break;
            }
        }

        // If the page is not present in the frame, replace the page using FIFO
        if (flag == 0)
        {
            int k;
            int temp = -1;
            for (k = 0; k < capacity; k++)
            {
                int l;
                for (l = i + 1; l < n; l++)
                {
                    if (frame[k] == pages[l])
                    {
                        if (l > temp)
                        {
                            temp = l;
                            j = k;
                        }
                        break;
                    }
                }
                if (l == n)
                {
                    j = k;
                    break;
                }
            }
            frame[j] = pages[i];
            faults++;
            printf("Miss |");
        }
        else
        {
            printf("Hit  |");
        }
        // Print the current set of frames
        printf("Page %d | ", pages[i]);
        printFrames(frame, capacity);
    }
    printf("\nNumber of hits = %d", n - faults);
    printf("\nHit Ratio = %f", (float)(n - faults) / n);
    printf("\nNumber of misses = %d", faults);
    printf("\nMiss Ratio = %f\n", (float)faults / n);
}

// Function to find the hit and miss using LRU
void LRUAlgorithm(int pages[], int n, int capacity)
{
    printf("\nLRU Algorithm\n");
    // Create an array for given number of pages
    int frame[capacity];

    // Initialize all frames as empty
    for (int i = 0; i < capacity; i++)
        frame[i] = -1;

    // Initialize the number of faults as 0
    int faults = 0;

    // Create an array to store the time at which the pages are accessed
    int time[capacity];

    // Initialize all elements of time array as 0
    for (int i = 0; i < capacity; i++)
        time[i] = 0;

    // Traverse through all pages
    for (int i = 0; i < n; i++)
    {
        // Find if there is a need to change the frame
        int flag = 0, j;
        for (j = 0; j < capacity; j++)
        {
            if (frame[j] == pages[i])
            {
                flag = 1;
                time[j] = i + 1;
                break;
            }
        }

        // If the page is not present in the frame, replace the page using FIFO
        if (flag == 0)
        {
            int k;
            int temp = time[0], pos = 0;
            for (k = 1; k < capacity; k++)
            {
                if (time[k] < temp)
                {
                    temp = time[k];
                    pos = k;
                }
            }
            frame[pos] = pages[i];
            time[pos] = i + 1;
            faults++;
            printf("Miss |");
        }
        else
        {
            printf("Hit  |");
        }
        // Print the current set of frames
        printf("Page %d | ", pages[i]);
        printFrames(frame, capacity);
    }
    printf("\nNumber of hits = %d", n - faults);
    printf("\nHit Ratio = %f", (float)(n - faults) / n);
    printf("\nNumber of misses = %d", faults);
    printf("\nMiss Ratio = %f\n", (float)faults / n);
}


// Driver code
int main()
{
    int n, capacity;
    printf("Enter the number of pages: ");
    scanf("%d", &n);
    int pages[n];
    printf("Enter the pages: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);
    printf("Enter the capacity of the main memory: ");
    scanf("%d", &capacity);
    FIFOAlgorithm(pages, n, capacity);
    OptimalAlgorithm(pages, n, capacity);
    LRUAlgorithm(pages, n, capacity);
    return 0;
}