// Dhruv Rajeshkumar Shah
// 21BCE0611

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>

int main() {
    pid_t pid;
    DIR* directory;
    struct dirent* entry;
    struct stat file_info;

    // Fork a child process
    pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork failed\n");
        exit(1);
    } else if (pid == 0) {
        // Child process

        // Get the child process ID
        pid_t child_pid = getpid();
        printf("Child process ID: %d\n", child_pid);

        // Execute a command using exec system call
        char* args[] = {"/bin/ls", "-l", NULL};
        execv(args[0], args);

        // execv replaces the current process, so the following code is never executed
        fprintf(stderr, "Exec failed\n");
        exit(1);
    } else {
        // Parent process

        // Get the parent process ID
        pid_t parent_pid = getpid();
        printf("Parent process ID: %d\n", parent_pid);

        // Wait for the child process to complete
        int status;
        wait(&status);
        printf("Child process exited with status: %d\n", WEXITSTATUS(status));

        // Open the current working directory
        directory = opendir(".");
        if (directory == NULL) {
            fprintf(stderr, "Failed to open directory\n");
            exit(1);
        }

        // Read directory entries
        while ((entry = readdir(directory)) != NULL) {
            // Exclude the current directory and parent directory
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
                printf("File: %s\n", entry->d_name);
                char filepath[256];
                snprintf(filepath, sizeof(filepath), "%s/%s", ".", entry->d_name);

                // Get file information using stat system call
                if (stat(filepath, &file_info) == 0) {
                    printf("Size: %lld bytes\n", file_info.st_size);
                    printf("Permissions: %o\n", file_info.st_mode & 0777);
                    printf("--------\n");
                } else {
                    fprintf(stderr, "Failed to get file information for %s\n", entry->d_name);
                    closedir(directory);
                    exit(1);
                }
            }
        }

        // Close the directory
        if (closedir(directory) != 0) {
            fprintf(stderr, "Failed to close directory\n");
            exit(1);
        }
    }

    return 0;
}
