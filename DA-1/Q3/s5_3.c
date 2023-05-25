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
        printf("Child process.");
        sleep(10); // Sleep for 10 seconds to demonstrate orphan process behavior
    } else {
        // Parent process
        printf("Parent process.");
    }
    printf("\n");

    return 0;
}
