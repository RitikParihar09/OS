#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();  

    if (pid < 0) {
        
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        
        printf("Child Process: PID = %d, Parent PID = %d\n", getpid(), getppid());
    } else {
        
        printf("Parent Process: PID = %d, Child PID = %d\n", getpid(), pid);
    }

    return 0;
}
