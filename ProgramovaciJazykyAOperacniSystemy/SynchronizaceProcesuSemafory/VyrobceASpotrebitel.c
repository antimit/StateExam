#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

sem_t empty;  // počet volných míst
sem_t full;   // počet obsazených míst
pthread_mutex_t mutex; // ochrana bufferu

void* producer(void* arg) {
    for (int i = 0; i < 10; i++) {
        sem_wait(&empty);             // čekej, dokud není volné místo (down)
        pthread_mutex_lock(&mutex);

        buffer[in] = i;
        printf("Producent vložil %d\n", i);
      
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&full);              // zvýší počet obsazených míst (up)

        sleep(1);
    }
    return NULL;
}

void* consumer(void* arg) {
    for (int i = 0; i < 10; i++) {
        sem_wait(&full);              // čekej, dokud není co číst (down)
        pthread_mutex_lock(&mutex);

        int item = buffer[out];
        printf("Konzument odebral %d\n", item);
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);             // zvýší počet volných míst (up)

        sleep(2);
    }
    return NULL;
}

int main() {
    pthread_t prod,prod1, cons,cons1;

    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&prod1, NULL, producer, NULL);


    pthread_create(&cons, NULL, consumer, NULL);
    pthread_create(&cons1, NULL, consumer, NULL);

    pthread_join(prod, NULL);
     pthread_join(prod1, NULL);
    pthread_join(cons, NULL);
     pthread_join(cons1, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
