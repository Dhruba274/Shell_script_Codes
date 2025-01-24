#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

// Function to generate Fibonacci series up to 'n' terms
void generate_fibonacci(int n) {
    int a = 0, b = 1, next;
    printf("Parent: Fibonacci sequence (%d terms):\n", n);
    for (int i = 0; i < n; i++) {
        printf("%d ", a);
        next = a + b;
        a = b;
        b = next;
    }
    printf("\n");
}

// Function to check if a number is prime
bool is_prime(int num) {
    if (num < 2) return false;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0)
            return false;
    }
    return true;
}

int main() {
    pid_t pid;
    int n, number;

    printf("Enter the number of terms for Fibonacci series: ");
    scanf("%d", &n);

    printf("Enter a number to check if it's prime: ");
    scanf("%d", &number);

    pid = fork();  // Create child process

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid > 0) {  // Parent process
        wait(NULL);  // Wait for child process to finish
        generate_fibonacci(n);
    } 
    else {  // Child process
        if (is_prime(number))
            printf("Child: %d is a prime number.\n", number);
        else
            printf("Child: %d is NOT a prime number.\n", number);
        
        exit(0);
    }

    return 0;
}
