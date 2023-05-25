#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
    pid_t f;
    f = fork();

    if (f < 0) {
        printf("Failed to fork\n");
        _exit(1);
    } else if (f == 0) {
        int i;
        printf("\nChild: PID is %d\n", getpid());
        for (i = 0; i < 10; i++) {
            printf("child ");
            if (i == 5)
                sleep(2);
        }
        printf("\n");
        _exit(0);
    } else {
        int j;
        printf("\nParent: PID is %d\n", getpid());
        for (j = 0; j < 10; j++) {
            printf("Parent ");
        }
        printf("\n");
    }

    return 0;
}
