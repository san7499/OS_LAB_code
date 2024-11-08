#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t resource_access = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t read_count_access = PTHREAD_MUTEX_INITIALIZER;

int read_count = 0;  // Number of active readers

void* reader(void* arg) {
    int id = *((int*)arg);

    // Reader enters
    pthread_mutex_lock(&read_count_access);
    read_count++;
    if (read_count == 1) {
        pthread_mutex_lock(&resource_access);  // First reader locks the resource
    }
    pthread_mutex_unlock(&read_count_access);

    // Reading section
    printf("Reader %d is reading\n", id);
    sleep(1);  // Simulate reading time
    printf("Reader %d finished reading\n", id);

    // Reader exits
    pthread_mutex_lock(&read_count_access);
    read_count--;
    if (read_count == 0) {
        pthread_mutex_unlock(&resource_access);  // Last reader unlocks the resource
    }
    pthread_mutex_unlock(&read_count_access);

    return NULL;
}

void* writer(void* arg) {
    int id = *((int*)arg);

    // Writer wants to write
    pthread_mutex_lock(&resource_access);

    // Writing section
    printf("Writer %d is writing\n", id);
    sleep(2);  // Simulate writing time
    printf("Writer %d finished writing\n", id);

    pthread_mutex_unlock(&resource_access);

    return NULL;
}

int main() {
    pthread_t r[5], w[2];
    int reader_ids[5] = {1, 2, 3, 4, 5};
    int writer_ids[2] = {1, 2};

    for (int i = 0; i < 5; i++) {
        pthread_create(&r[i], NULL, reader, &reader_ids[i]);
    }
    for (int i = 0; i < 2; i++) {
        pthread_create(&w[i], NULL, writer, &writer_ids[i]);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(r[i], NULL);
    }
    for (int i = 0; i < 2; i++) {
        pthread_join(w[i], NULL);
    }

    pthread_mutex_destroy(&resource_access);
    pthread_mutex_destroy(&read_count_access);

    return 0;
}

