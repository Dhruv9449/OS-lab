// Dhruv Rajeshkumar Shah
// 21BCE0611

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    // Fork a process
    pid_t id;
    id = fork();

    if (id < 0) {
        printf("Fork failed\n");
        return 1;
    }

    if (id > 0) {
        // Parent process
        printf("Parent will sleep");
        sleep(5);
    }
    if (id == 0){
        // Zombie 
        printf("I am child");
    }
    printf("\n");
    return 0;
}
