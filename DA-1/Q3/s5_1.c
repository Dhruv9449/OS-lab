// Dhruv Rajeshkumar Shah
// 21BCE0611

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    pid_t pid;

    // Fork a child process
    pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork failed\n");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("Child process ID: %d\n", getpid());
    } else {
        // Parent process
        printf("Parent process ID: %d\n", getpid());
    }

    return 0;
}
