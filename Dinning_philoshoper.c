#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include<sys/wait.h>

#define NUM_PHILOSOPHERS 5

pthread_mutex_t forks[NUM_PHILOSOPHERS];  // Forks as mutex locks

void *philosopher(void *arg) {
    int id = *(int *)arg;
    
    while (1) {
        // Thinking
        printf("Philosopher %d is thinking...\n", id);
        sleep(1);

        // Picking up forks (left first, right second to avoid deadlock)
        pthread_mutex_lock(&forks[id]);
        pthread_mutex_lock(&forks[(id + 1) % NUM_PHILOSOPHERS]);

        // Eating
        printf("Philosopher %d is eating...\n", id);
        sleep(2);

        // Putting down forks
        pthread_mutex_unlock(&forks[(id + 1) % NUM_PHILOSOPHERS]);
        pthread_mutex_unlock(&forks[id]);

        // Thinking again
        printf("Philosopher %d finished eating and starts thinking...\n", id);
    }

    return NULL;
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int ids[NUM_PHILOSOPHERS];

    // Initialize mutex locks (forks)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    // Join philosopher threads (infinite loop so they won't actually terminate)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Destroy mutex locks (not reached in this program)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&forks[i]);
    }

    return 0;
}
