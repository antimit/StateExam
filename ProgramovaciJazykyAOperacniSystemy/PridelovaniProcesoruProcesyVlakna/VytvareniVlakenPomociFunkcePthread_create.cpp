#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Funkce, která poběží ve vlákně
void* worker(void* arg) {
    int value = *(int*)arg;  // převedeme ukazatel zpět na int
    printf("Hello from thread! Value = %d\n", value);
    return NULL; // návratová hodnota vlákna
}

int main() {
    pthread_t tid;    // ID vlákna
    int x = 42;

    // Vytvoření vlákna
    if (pthread_create(&tid, NULL, worker, &x) != 0) {
        perror("pthread_create failed");
        return 1;
    }

    // Počkáme, až vlákno skončí
    pthread_join(tid, NULL);

    printf("Main thread finished.\n");
    return 0;
}
