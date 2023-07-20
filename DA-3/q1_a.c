// Dhruv Rajeshkumar Shah
// 21BCE0611

#include <stdio.h>

void calculateSafeSequence(int processes, int resources, int alloc[processes][resources], int max[processes][resources], int avail[resources]) {
    int i, j, k;
    int need[processes][resources];
    int f[processes], ans[processes], ind = 0;

    // Initialize the finish array
    for (k = 0; k < processes; k++) {
        f[k] = 0;
    }

    // Calculate the need matrix
    for (i = 0; i < processes; i++) {
        for (j = 0; j < resources; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    int y = 0;
    for (k = 0; k < processes; k++) {
        for (i = 0; i < processes; i++) {
            if (f[i] == 0) {
                int flag = 0;
                for (j = 0; j < resources; j++) {
                    if (need[i][j] > avail[j]) {
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0) {
                    ans[ind++] = i;
                    for (y = 0; y < resources; y++) {
                        avail[y] += alloc[i][y];
                    }
                    f[i] = 1;
                }
            }
        }
    }

    int flag = 1;
    for (int i = 0; i < processes; i++) {
        if (f[i] == 0) {
            flag = 0;
            printf("The system is not safe.\n");
            return;
        }
    }

    printf("Following is the SAFE Sequence:\n");
    for (i = 0; i < processes - 1; i++) {
        printf("P%d -> ", ans[i] + 1); // Add 1 to process index to match user-friendly labeling
    }
    printf("P%d\n", ans[processes - 1] + 1); // Add 1 to process index to match user-friendly labeling
}

int main() {
    int n, m, i, j;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the number of resources: ");
    scanf("%d", &m);

    int alloc[n][m], max[n][m], avail[m];

    printf("Enter the allocation matrix:\n");

    // Display allocation matrix headings
    printf("  ");
    for (j = 0; j < m; j++) {
        printf("R%d ", j);
    }
    printf("\n");

    for (i = 0; i < n; i++) {
        printf("P%d ", i + 1); // Add 1 to process index for user-friendly labeling
        for (j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
        printf("\n");
    }

    printf("Enter the maximum matrix:\n");

    // Display maximum matrix headings
    printf("  ");
    for (j = 0; j < m; j++) {
        printf("R%d ", j);
    }
    printf("\n");

    for (i = 0; i < n; i++) {
        printf("P%d ", i + 1); // Add 1 to process index for user-friendly labeling
        for (j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
        printf("\n");
    }

    printf("Enter the available resources:\n");
    for (j = 0; j < m; j++) {
        scanf("%d", &avail[j]);
    }

    calculateSafeSequence(n, m, alloc, max, avail);

    return 0;
}
