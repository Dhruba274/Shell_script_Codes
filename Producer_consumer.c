#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include<stdlib.h>

#define BUFFER_SIZE 5
#define NUM_PRODUCERS 3
#define NUM_CONSUMERS 3
#define TOTAL_ITEMS 5

int buffer[BUFFER_SIZE], in = 0, out = 0;

pthread_mutex_t mutex;
sem_t empty_slots, full_slots;

void* producer(void* arg) {
    int id = *(int*)arg;
    for (int i = 0; i < TOTAL_ITEMS; i++) {
        sem_wait(&empty_slots);
        pthread_mutex_lock(&mutex);

        buffer[in] = id * 100 + i;
        printf("Producer %d -> Item %d at buffer[%d]\n", id, buffer[in], in);
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&full_slots);
        sleep(1);
    }
    return NULL;
}

void* consumer(void* arg) {
    int id = *(int*)arg;
    for (int i = 0; i < TOTAL_ITEMS; i++) {
        sem_wait(&full_slots);
        pthread_mutex_lock(&mutex);

        int item = buffer[out];
        printf("Consumer %d <- Item %d from buffer[%d]\n", id, item, out);
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty_slots);
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t producers[NUM_PRODUCERS], consumers[NUM_CONSUMERS];
    int ids[NUM_PRODUCERS];

    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty_slots, 0, BUFFER_SIZE);
    sem_init(&full_slots, 0, 0);

    for (int i = 0; i < NUM_PRODUCERS; i++) {
        ids[i] = i + 1;
        pthread_create(&producers[i], NULL, producer, &ids[i]);
        pthread_create(&consumers[i], NULL, consumer, &ids[i]);
    }

    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_join(producers[i], NULL);
        pthread_join(consumers[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty_slots);
    sem_destroy(&full_slots);

    printf("Execution completed.\n");
    return 0;
}
