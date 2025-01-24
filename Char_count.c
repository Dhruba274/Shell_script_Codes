#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include<sys/wait.h>
#define BUFFER_SIZE 100

// Function to count alphabets, digits, and special characters in a string
void count_characters(const char *str, int *alphabets, int *digits, int *specials) {
    *alphabets = *digits = *specials = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (isalpha(str[i])) {
            (*alphabets)++;
        } else if (isdigit(str[i])) {
            (*digits)++;
        } else if (str[i] == '#' || str[i] == '&') {
            (*specials)++;
        }
    }
}

int main() {
    int fd[2];  // File descriptors for pipe
    pid_t pid;
    char input_str[BUFFER_SIZE];

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

        printf("Parent: Enter a string: ");
        fgets(input_str, BUFFER_SIZE, stdin);
        input_str[strcspn(input_str, "\n")] = '\0';  // Remove newline character

        write(fd[1], input_str, strlen(input_str) + 1);  // Send string to child
        close(fd[1]);  // Close write end after sending

        wait(NULL);  // Wait for child process to complete
    } 
    else {  // Child process
        close(fd[1]);  // Close unused write end

        char received_str[BUFFER_SIZE];
        read(fd[0], received_str, BUFFER_SIZE);  // Read string from parent
        close(fd[0]);  // Close read end after reading

        int alphabets, digits, specials;
        count_characters(received_str, &alphabets, &digits, &specials);

        printf("Child: Number of alphabets = %d\n", alphabets);
        printf("Child: Number of digits = %d\n", digits);
        printf("Child: Number of special characters (#, &) = %d\n", specials);

        exit(0);
    }

    return 0;
}
