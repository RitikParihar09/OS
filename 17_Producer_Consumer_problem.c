#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutex;   // Semaphore for mutual exclusion
sem_t full;    // Semaphore to track full buffer slots
sem_t empty;   // Semaphore to track empty buffer slots

int buffer_size = 5;  // Size of the buffer
int x = 0;  // Variable to store the current item produced

void producer() {
    sem_wait(&empty);  // Wait for an empty slot
    sem_wait(&mutex);  // Lock the critical section (mutual exclusion)
    
    x++;
    printf("Producer produces item %d\n", x);

    sem_post(&mutex);  // Release the lock
    sem_post(&full);   // Signal that a full slot is available
}

void consumer() {
    sem_wait(&full);   // Wait for a full slot
    sem_wait(&mutex);  // Lock the critical section (mutual exclusion)
    
    printf("Consumer consumes item %d\n", x);
    x--;

    sem_post(&mutex);  // Release the lock
    sem_post(&empty);  // Signal that an empty slot is available
}

int main() {
    int n;
    
    // Initialize semaphores
    sem_init(&mutex, 0, 1);    // Binary semaphore for mutex
    sem_init(&empty, 0, buffer_size);  // Buffer has 'buffer_size' empty slots initially
    sem_init(&full, 0, 0);     // Initially, the buffer is empty, so full slots = 0

    while (1) {
        printf("\n1 for producer\n2 for consumer\n3 for exit");
        printf("\nEnter your choice: ");
        scanf("%d", &n);

        switch (n) {
            case 1:
                if (sem_trywait(&empty) == 0) {  // Try to produce if there's space
                    sem_post(&empty);  // Revert empty to avoid double decrement by producer
                    producer();
                } else {
                    printf("Buffer is full.\n");
                }
                break;
            case 2:
                if (sem_trywait(&full) == 0) {  // Try to consume if there's a full slot
                    sem_post(&full);  // Revert full to avoid double decrement by consumer
                    consumer();
                } else {
                    printf("Buffer is empty.\n");
                }
                break;
            case 3:
                printf("Exiting...\n");
                sem_destroy(&mutex);  // Destroy semaphores
                sem_destroy(&empty);
                sem_destroy(&full);
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}