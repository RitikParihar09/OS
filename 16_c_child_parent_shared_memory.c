#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include<sys/wait.h>

#define SHM_SIZE 100

int main() {
    int shmid;
    char *shm_ptr;
    pid_t pid;

    // Create shared memory segment
    shmid = shmget(IPC_PRIVATE, SHM_SIZE, 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    // Attach shared memory
    shm_ptr = shmat(shmid, NULL, 0);
    if (shm_ptr == (char *)-1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    // Create a child process
    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {  // Child process
        const char *msg = "Message from Child.";
        strncpy(shm_ptr, msg, SHM_SIZE);
        exit(0);
    } else {  // Parent process
        wait(NULL);  // Wait for child process to complete
        printf("Parent received: %s\n", shm_ptr);

        // Detach and remove shared memory
        shmdt(shm_ptr);
        shmctl(shmid, IPC_RMID, NULL);
    }

    return 0;
}
