#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include<sys/wait.h>

// Function to check if a number is an Armstrong number
int is_armstrong(int num) {
    int originalNum = num, sum = 0, digits = 0;

    // Count number of digits
    while (originalNum != 0) {
        originalNum /= 10;
        digits++;
    }

    originalNum = num;

    // Compute sum of power of digits
    while (originalNum != 0) {
        int digit = originalNum % 10;
        sum += pow(digit, digits);
        originalNum /= 10;
    }

    return (sum == num);
}

int main() {
    int fd[2];  // File descriptors for pipe (fd[0] - read, fd[1] - write)
    pid_t pid;
    int number;

    // Create a pipe
    if (pipe(fd) == -1) {
        perror("Pipe failed");
        return 1;
    }

    pid = fork();  // Create child process

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid > 0) {  // Parent process
        close(fd[0]);  // Close unused read end

        printf("Parent: Enter a number: ");
        scanf("%d", &number);

        write(fd[1], &number, sizeof(number));  // Send number to child
        close(fd[1]);  // Close write end after sending

        wait(NULL);  // Wait for child process to finish
    } 
    else {  // Child process
        close(fd[1]);  // Close unused write end

        read(fd[0], &number, sizeof(number));  // Read number from parent
        close(fd[0]);  // Close read end after reading

        if (is_armstrong(number))
            printf("Child: %d is an Armstrong number\n", number);
        else
            printf("Child: %d is NOT an Armstrong number\n", number);

        exit(0);
    }

    return 0;
}
