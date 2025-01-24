#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    pid_t pid1, pid2;

    printf("Parent process (PID: %d)\n", getpid());

    pid1 = fork();  // Create first child

    if (pid1 < 0) {
        perror("Fork failed");
        exit(1);
    } 
    else if (pid1 == 0) {
        // First child process
        printf("First Child (PID: %d, Parent PID: %d)\n", getpid(), getppid());

        pid2 = fork();  // Create grandchild

        if (pid2 < 0) {
            perror("Fork failed");
            exit(1);
        } 
        else if (pid2 == 0) {
            // Grandchild process
            printf("Grandchild (PID: %d, Parent PID: %d)\n", getpid(), getppid());
            exit(0);
        }
        exit(0);
    } 
    else {
        // Parent process
        pid2 = fork();  // Create second child

        if (pid2 < 0) {
            perror("Fork failed");
            exit(1);
        } 
        else if (pid2 == 0) {
            // Second child process
            printf("Second Child (PID: %d, Parent PID: %d)\n", getpid(), getppid());
            exit(0);
        }
    }

    // Parent process waits for child processes to terminate
    wait(NULL);
    wait(NULL);

    return 0;
}
