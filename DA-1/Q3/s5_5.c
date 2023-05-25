// Dhruv Rajeshkumar Shah
// 21BCE0611

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 256

int main() {
    int pipefd[2];
    pid_t pid;
    char message[] = "Hello, Dhruv Rajeshkumar Shah, this is a message!";
    char buffer[BUFFER_SIZE];

    // Create a pipe
    if (pipe(pipefd) == -1) {
        perror("Pipe creation failed");
        return 1;
    }

    // Fork a child process
    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        // Child process
        close(pipefd[1]); // Close the write end of the pipe

        // Read message from the pipe
        ssize_t bytesRead = read(pipefd[0], buffer, BUFFER_SIZE);
        if (bytesRead > 0) {
            printf("Child received message: %s\n", buffer);
        } else {
            perror("Child failed to read message");
        }

        close(pipefd[0]); // Close the read end of the pipe
    } else {
        // Parent process
        close(pipefd[0]); // Close the read end of the pipe

        // Write message to the pipe
        ssize_t bytesWritten = write(pipefd[1], message, strlen(message) + 1);
        if (bytesWritten > 0) {
            printf("Parent sent message: %s\n", message);
        } else {
            perror("Parent failed to send message");
        }

        close(pipefd[1]); // Close the write end of the pipe
    }

    return 0;
}
