#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t chopstick[5];  // Array of semaphores representing chopsticks.

void *philos(void *n);  // Function executed by each philosopher thread.
void eat(int ph);        // Simulates eating by a philosopher.

int main() {
    int i, n[5];  
    pthread_t T[5];  // Array of threads for the 5 philosophers.

    // Initialize all chopstick semaphores to 1 (available).
    for (i = 0; i < 5; i++)
        sem_init(&chopstick[i], 0, 1);

    // Create threads for the philosophers.
    for (i = 0; i < 5; i++) {
        n[i] = i;  // Assign philosopher number.
        pthread_create(&T[i], NULL, philos, (void *)&n[i]);
    }

    // Wait for all philosopher threads to complete.
    for (i = 0; i < 5; i++)
        pthread_join(T[i], NULL);

    return 0;
}
void *philos(void *n) {
    int ph = *(int *)n;  // Extract philosopher ID from argument.

    printf("Philosopher %d wants to eat\n", ph);
    printf("Philosopher %d tries to pick left chopstick\n", ph);
    sem_wait(&chopstick[ph]);  // Acquire left chopstick.
    printf("Philosopher %d picks the left chopstick\n", ph);

    printf("Philosopher %d tries to pick the right chopstick\n", ph);
    sem_wait(&chopstick[(ph + 1) % 5]);  // Acquire right chopstick.
    printf("Philosopher %d picks the right chopstick\n", ph);

    eat(ph);  // Philosopher eats.
    sleep(2);  // Simulate eating time.

    printf("Philosopher %d has finished eating\n", ph);

    sem_post(&chopstick[(ph + 1) % 5]);  // Release right chopstick.
    printf("Philosopher %d leaves the right chopstick\n", ph);

    sem_post(&chopstick[ph]);  // Release left chopstick.
    printf("Philosopher %d leaves the left chopstick\n", ph);

    return NULL;
}

void eat(int ph) {
    printf("Philosopher %d begins to eat\n", ph);
}
