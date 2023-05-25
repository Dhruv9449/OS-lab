// Dhruv Rajeshkumar Shah
// 21BCE0611

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

void listFiles() {
    DIR* directory;
    struct dirent* entry;

    // Open the current working directory
    directory = opendir(".");
    if (directory == NULL) {
        perror("Failed to open directory");
        exit(1);
    }

    // Read directory entries
    while ((entry = readdir(directory)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    // Close the directory
    closedir(directory);
}

void grepFile(const char* pattern, const char* filename) {
    char line[256];
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open file");
        exit(1);
    }

    while (fgets(line, sizeof(line), file) != NULL) {
        if (strstr(line, pattern) != NULL) {
            printf("%s", line);
        }
    }

    fclose(file);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <option> [arguments]\n", argv[0]);
        printf("Options:\n");
        printf("  -ls: List files in the current directory\n");
        printf("  -grep <pattern> <filename>: Search for pattern in the file\n");
        return 1;
    }

    if (strcmp(argv[1], "-ls") == 0) {
        listFiles();
    } else if (strcmp(argv[1], "-grep") == 0) {
        if (argc != 4) {
            printf("Invalid number of arguments for -grep option\n");
            return 1;
        }
        grepFile(argv[2], argv[3]);
    } else {
        printf("Invalid option: %s\n", argv[1]);
        return 1;
    }

    return 0;
}
