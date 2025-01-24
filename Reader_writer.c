#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_READERS 5
#define NUM_WRITERS 2

int shared_data = 0;  // The shared resource
int reader_count = 0; // Number of active readers

pthread_mutex_t mutex;  // Protects reader_count
sem_t resource;         // Controls access to shared_data

void* reader(void* arg) {
    int id = *(int*)arg;
    while (1) {
        pthread_mutex_lock(&mutex);
        reader_count++;
        if (reader_count == 1)
            sem_wait(&resource);  // First reader locks resource
        pthread_mutex_unlock(&mutex);

        // Reading section
        printf("Reader %d: Read shared data = %d\n", id, shared_data);
        sleep(1);

        pthread_mutex_lock(&mutex);
        reader_count--;
        if (reader_count == 0)
            sem_post(&resource);  // Last reader unlocks resource
        pthread_mutex_unlock(&mutex);

        sleep(1);  // Simulate delay before reading again
    }
    return NULL;
}

void* writer(void* arg) {
    int id = *(int*)arg;
    while (1) {
        sem_wait(&resource);  // Writer locks resource

        // Writing section
        shared_data++;
        printf("Writer %d: Wrote shared data = %d\n", id, shared_data);
        sleep(2);

        sem_post(&resource);  // Release resource
        sleep(2);  // Simulate delay before writing again
    }
    return NULL;
}

int main() {
    pthread_t readers[NUM_READERS], writers[NUM_WRITERS];
    int ids[NUM_READERS > NUM_WRITERS ? NUM_READERS : NUM_WRITERS];

    pthread_mutex_init(&mutex, NULL);
    sem_init(&resource, 0, 1);

    for (int i = 0; i < NUM_READERS; i++) {
        ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &ids[i]);
    }

    for (int i = 0; i < NUM_WRITERS; i++) {
        ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &ids[i]);
    }

    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&resource);

    return 0;
}
