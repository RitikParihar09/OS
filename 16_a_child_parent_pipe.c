#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd[2]; 
    pid_t pid;
    char writeMessage[] = "Hello from Child!";
    char readMessage[100];

    // Create the pipe
    if (pipe(fd) == -1) {
        perror("Pipe failed");
        return 1;
    }

    // Fork the process
    pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) {  // Child process
        close(fd[0]);  // Close the read end in the child
        write(fd[1], writeMessage, strlen(writeMessage) + 1);
        close(fd[1]);  // Close the write end after writing
    } else {  // Parent process
        close(fd[1]);  // Close the write end in the parent
        read(fd[0], readMessage, sizeof(readMessage));
        printf("Parent received: %s\n", readMessage);
        close(fd[0]);  // Close the read end after reading
    }

    return 0;
}
