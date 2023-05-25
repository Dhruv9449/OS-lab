// Dhruv Rajeshkumar Shah
// 21BCE0611

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int file_descriptor;
    ssize_t bytes_read, bytes_written;
    char buffer[1024];

    // Open a file in read-only mode
    file_descriptor = open("input.txt", O_RDONLY);
    if (file_descriptor < 0) {
        perror("Failed to open the file");
        exit(1);
    }

    // Read from the file
    bytes_read = read(file_descriptor, buffer, sizeof(buffer));
    if (bytes_read < 0) {
        perror("Failed to read from the file");
        exit(1);
    }

    // Print the contents read from the file
    printf("Contents of the file:\n");
    write(STDOUT_FILENO, buffer, bytes_read);

    // Close the file
    if (close(file_descriptor) < 0) {
        perror("Failed to close the file");
        exit(1);
    }

    // Open a file in write-only mode, creating it if it doesn't exist
    file_descriptor = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (file_descriptor < 0) {
        perror("Failed to open the file");
        exit(1);
    }

    // Write to the file
    bytes_written = write(file_descriptor, buffer, bytes_read);
    if (bytes_written < 0) {
        perror("Failed to write to the file");
        exit(1);
    }

    printf("Bytes written to the file: %ld\n", bytes_written);

    // Close the file
    if (close(file_descriptor) < 0) {
        perror("Failed to close the file");
        exit(1);
    }

    return 0;
}
