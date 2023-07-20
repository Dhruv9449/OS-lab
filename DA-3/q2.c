// Dhruv Rajeshkumar Shah
// 21BCE0611

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_PHILOSOPHERS 10

// Define the mutex and condition variables
pthread_mutex_t forks[MAX_PHILOSOPHERS];
pthread_cond_t philosophers[MAX_PHILOSOPHERS];

// Define the state of each philosopher
typedef enum {
    THINKING,
    HUNGRY,
    EATING
} PhilosopherState;
PhilosopherState states[MAX_PHILOSOPHERS];

// Number of philosophers and the maximum time each philosopher spends eating
int numPhilosophers;
int maxEatingTime;

// Function prototypes
void *philosopher(void *arg);
void pickForks(int philosopherID);
void returnForks(int philosopherID);
void test(int philosopherID);

int main() {
    int i;
    pthread_t threads[MAX_PHILOSOPHERS];

    // Read the number of philosophers from the user
    printf("Enter the number of philosophers (2-10): ");
    scanf("%d", &numPhilosophers);
    if (numPhilosophers < 2 || numPhilosophers > MAX_PHILOSOPHERS) {
        printf("Invalid number of philosophers. Program exiting.\n");
        return 1;
    }

    // Read the maximum eating time from the user
    printf("Enter the maximum eating time for each philosopher (in seconds): ");
    scanf("%d", &maxEatingTime);
    if (maxEatingTime <= 0) {
        printf("Invalid maximum eating time. Program exiting.\n");
        return 1;
    }

    // Initialize the mutex and condition variables
    for (i = 0; i < numPhilosophers; i++) {
        pthread_mutex_init(&forks[i], NULL);
        pthread_cond_init(&philosophers[i], NULL);
    }

    // Create philosopher threads
    for (i = 0; i < numPhilosophers; i++) {
        int *philosopherID = malloc(sizeof(int));
        *philosopherID = i;
        pthread_create(&threads[i], NULL, philosopher, philosopherID);
    }

    // Wait for philosopher threads to finish
    for (i = 0; i < numPhilosophers; i++) {
        pthread_join(threads[i], NULL);
    }

    // Clean up
    for (i = 0; i < numPhilosophers; i++) {
        pthread_mutex_destroy(&forks[i]);
        pthread_cond_destroy(&philosophers[i]);
    }

    return 0;
}

void *philosopher(void *arg) {
    int philosopherID = *((int *)arg);
    free(arg);

    while (1) {
        // Philosopher is thinking
        printf("Philosopher %d is thinking.\n", philosopherID);
        sleep(rand() % 3); // Simulate thinking time

        // Philosopher is hungry
        printf("Philosopher %d is hungry.\n", philosopherID);
        pickForks(philosopherID);

        // Philosopher is eating
        printf("Philosopher %d is eating.\n", philosopherID);
        sleep(rand() % maxEatingTime + 1); // Simulate eating time

        // Philosopher finished eating
        printf("Philosopher %d finished eating.\n", philosopherID);
        returnForks(philosopherID);
    }
}

void pickForks(int philosopherID) {
    pthread_mutex_lock(&forks[philosopherID]);
    states[philosopherID] = HUNGRY;
    test(philosopherID);
    while (states[philosopherID] != EATING) {
        pthread_cond_wait(&philosophers[philosopherID], &forks[philosopherID]);
    }
    pthread_mutex_unlock(&forks[philosopherID]);
}

void returnForks(int philosopherID) {
    pthread_mutex_lock(&forks[philosopherID]);
    states[philosopherID] = THINKING;
    test((philosopherID + numPhilosophers - 1) % numPhilosophers);
    test((philosopherID + 1) % numPhilosophers);
    pthread_mutex_unlock(&forks[philosopherID]);
}

void test(int philosopherID) {
    if (states[philosopherID] == HUNGRY &&
        states[(philosopherID + numPhilosophers - 1) % numPhilosophers] != EATING &&
        states[(philosopherID + 1) % numPhilosophers] != EATING) {
        states[philosopherID] = EATING;
        pthread_cond_signal(&philosophers[philosopherID]);
    }
}
