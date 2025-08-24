#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define THREAD_COUNT 5

sem_t semaphore; // definice semaforu
int shared_counter = 0; // sdílená proměnná (kritická sekce)

void* worker(void* arg) {
    int id = *(int*)arg;

    // vstup do kritické sekce
    sem_wait(&semaphore);

    printf("Thread %d vstoupil do kritické sekce.\n", id);
    int temp = shared_counter;
    sleep(1); // simulace zpoždění
    shared_counter = temp + 1;
    printf("Thread %d zvýšil counter na %d.\n", id, shared_counter);

    // opuštění kritické sekce
    sem_post(&semaphore);

    return NULL;
}

int main() {
    pthread_t threads[THREAD_COUNT];
    int ids[THREAD_COUNT];

    sem_init(&semaphore, 0, 2); // inicializace semaforu s hodnotou 1 (binární semafor)

    for (int i = 0; i < THREAD_COUNT; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, worker, &ids[i]);
    }

    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&semaphore);

    printf("Konečný counter = %d\n", shared_counter);
    return 0;
}
