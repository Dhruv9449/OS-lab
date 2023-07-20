#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME_LENGTH 20
#define MAX_FILE_SIZE 1024
#define MAX_BLOCKS 100

typedef struct {
    char name[MAX_FILENAME_LENGTH];
    int size;
    int blocks[MAX_BLOCKS];
} File;

void sequentialAllocation(File* file, int startBlock, int numBlocks) {
    strncpy(file->name, "Sequential", MAX_FILENAME_LENGTH);
    file->size = numBlocks * sizeof(int);
    for (int i = 0; i < numBlocks; i++) {
        file->blocks[i] = startBlock + i;
    }
}

void indexedAllocation(File* file, int startIndexBlock, int numBlocks) {
    strncpy(file->name, "Indexed", MAX_FILENAME_LENGTH);
    file->size = sizeof(int);
    file->blocks[0] = startIndexBlock;

    for (int i = 1; i <= numBlocks; i++) {
        file->blocks[i] = startIndexBlock + i;
        file->size += sizeof(int);
    }
}

void linkedAllocation(File* file, int startIndexBlock, int numBlocks) {
    strncpy(file->name, "Linked", MAX_FILENAME_LENGTH);
    file->size = sizeof(int);
    int currentBlock = startIndexBlock;

    for (int i = 1; i <= numBlocks; i++) {
        file->blocks[i - 1] = currentBlock;
        file->size += sizeof(int);
        currentBlock++;
    }
    file->blocks[numBlocks] = -1; // -1 indicates the end of the file
}

void displayFileDetails(File file, int numBlocks) {
    printf("File Name: %s\n", file.name);
    printf("File Size: %d bytes\n", file.size);
    printf("Blocks Allocated: ");
    for (int i = 0; i < numBlocks; i++) {
        if (file.blocks[i] == -1)
            break;
        printf("%d ", file.blocks[i]);
    }
    printf("\n\n");
}

int main() {
    File sequentialFile, indexedFile, linkedFile;
    int startBlock, numBlocks;

    // Sequential Allocation
    printf("Enter the start block for Sequential Allocation: ");
    scanf("%d", &startBlock);
    printf("Enter the number of blocks for Sequential Allocation: ");
    scanf("%d", &numBlocks);
    sequentialAllocation(&sequentialFile, startBlock, numBlocks);
    displayFileDetails(sequentialFile, numBlocks);

    // Indexed Allocation
    printf("Enter the start index block for Indexed Allocation: ");
    scanf("%d", &startBlock);
    printf("Enter the number of blocks for Indexed Allocation: ");
    scanf("%d", &numBlocks);
    indexedAllocation(&indexedFile, startBlock, numBlocks);
    displayFileDetails(indexedFile, numBlocks + 1); // +1 for the index block

    // Linked Allocation
    printf("Enter the start index block for Linked Allocation: ");
    scanf("%d", &startBlock);
    printf("Enter the number of blocks for Linked Allocation: ");
    scanf("%d", &numBlocks);
    linkedAllocation(&linkedFile, startBlock, numBlocks);
    displayFileDetails(linkedFile, numBlocks + 1); // +1 for the index block

    return 0;
}
