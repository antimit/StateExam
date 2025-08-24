// deadlock_demo.c
// Compile:  gcc -pthread deadlock_demo.c -o deadlock_demo
// Run:      ./deadlock_demo deadlock
//           ./deadlock_demo fixed

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

static pthread_mutex_t A = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t B = PTHREAD_MUTEX_INITIALIZER;

static volatile int done1 = 0, done2 = 0;

static void* lock_A_then_B(void* arg) {
    long id = (long)arg;
    printf("[T%ld] trying lock A\n", id);
    pthread_mutex_lock(&A);
    printf("[T%ld] locked A\n", id);

    // widen the window to trigger deadlock when the other thread has B
    sleep(1);

    printf("[T%ld] trying lock B\n", id);
    pthread_mutex_lock(&B);
    printf("[T%ld] locked B\n", id);

    // critical section using A+B
    printf("[T%ld] in critical section (A+B)\n", id);
    usleep(200 * 1000);

    pthread_mutex_unlock(&B);
    pthread_mutex_unlock(&A);
    printf("[T%ld] released B then A\n", id);

    if (id == 1) done1 = 1; else done2 = 1;
    return NULL;
}

static void* lock_B_then_A(void* arg) {
    long id = (long)arg;
    printf("[T%ld] trying lock B\n", id);
    pthread_mutex_lock(&B);
    printf("[T%ld] locked B\n", id);

    // widen the window to trigger deadlock when the other thread has A
    sleep(1);

    printf("[T%ld] trying lock A\n", id);
    pthread_mutex_lock(&A);
    printf("[T%ld] locked A\n", id);

    // critical section using B+A
    printf("[T%ld] in critical section (B+A)\n", id);
    usleep(200 * 1000);

    pthread_mutex_unlock(&A);
    pthread_mutex_unlock(&B);
    printf("[T%ld] released A then B\n", id);

    if (id == 1) done1 = 1; else done2 = 1;
    return NULL;
}

int main(int argc, char** argv) {
    int mode_deadlock = 1; // default
    if (argc >= 2 && strcmp(argv[1], "fixed") == 0) {
        mode_deadlock = 0;
    } else if (argc >= 2 && strcmp(argv[1], "deadlock") != 0) {
        fprintf(stderr, "Usage: %s [deadlock|fixed]\n", argv[0]);
        return 1;
    }

    pthread_t t1, t2;

    if (mode_deadlock) {
        printf("MODE: deadlock (T1 locks A->B, T2 locks B->A)\n");
        // Opposite lock order → high chance of deadlock
        pthread_create(&t1, NULL, lock_A_then_B, (void*)1L);
        pthread_create(&t2, NULL, lock_B_then_A, (void*)2L);

        // Wait a bit; if neither thread finishes, we likely deadlocked.
        sleep(3);
        if (!done1 || !done2) {
            printf("\nLikely DEADLOCK detected: threads are waiting on each other.\n");
            printf("This happens because T1 holds A and waits for B, while T2 holds B and waits for A.\n");
            printf("Exiting without join to avoid hanging forever.\n");
            // Note: intentionally not joining/destroying; process exit will reclaim resources.
            return 2;
        }

        // If we somehow avoided the deadlock (timing), join them.
        pthread_join(t1, NULL);
        pthread_join(t2, NULL);
        printf("No deadlock occurred (timing luck).\n");
    } else {
        printf("MODE: fixed (both threads lock A->B in the same order)\n");
        // Same lock order in all threads → no deadlock
        pthread_create(&t1, NULL, lock_A_then_B, (void*)1L);
        pthread_create(&t2, NULL, lock_A_then_B, (void*)2L);

        pthread_join(t1, NULL);
        pthread_join(t2, NULL);
        printf("\nCompleted without deadlock.\n");
    }

    return 0;
}
