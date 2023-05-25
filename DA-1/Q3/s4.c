// Dhruv Rajeshkumar Shah
// 21BCE0611

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void displayFileContents(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open file");
        exit(1);
    }

    printf("File contents:\n");
    char line[256];
    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line);
    }

    fclose(file);
}

void removeExtraSpaces(char* filename) {
    char tempFilename[] = "temp.txt";

    // Open the input file for reading
    FILE* inputFile = fopen(filename, "r");
    if (inputFile == NULL) {
        perror("Failed to open input file");
        exit(1);
    }

    // Open the temporary file for writing
    FILE* tempFile = fopen(tempFilename, "w");
    if (tempFile == NULL) {
        perror("Failed to open temporary file");
        fclose(inputFile);
        exit(1);
    }

    char line[256];
    while (fgets(line, sizeof(line), inputFile) != NULL) {
        // Remove extra spaces from the line
        int length = strlen(line);
        char modifiedLine[256];
        int modifiedIndex = 0;
        int spaceCount = 0;

        for (int i = 0; i < length; i++) {
            if (line[i] == ' ') {
                spaceCount++;
                if (spaceCount > 1) {
                    continue; // Skip additional spaces
                }
            } else {
                spaceCount = 0;
            }

            modifiedLine[modifiedIndex++] = line[i];
        }

        modifiedLine[modifiedIndex] = '\0';

        // Write the modified line to the temporary file
        fputs(modifiedLine, tempFile);
    }

    // Close the input and temporary files
    fclose(inputFile);
    fclose(tempFile);

    // Remove the original file
    if (remove(filename) != 0) {
        perror("Failed to remove the original file");
        exit(1);
    }

    // Rename the temporary file to the original filename
    if (rename(tempFilename, filename) != 0) {
        perror("Failed to rename the temporary file");
        exit(1);
    }
}

int main() {
    char filename[] = "input2.txt";

    printf("Before removing extra spaces:\n");
    displayFileContents(filename);

    removeExtraSpaces(filename);

    printf("\nAfter removing extra spaces:\n");
    displayFileContents(filename);

    return 0;
}
