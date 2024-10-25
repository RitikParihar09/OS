#include <stdio.h>  
#include <sys/types.h>  
#include <unistd.h> 


int main() { 
    pid_t pid = fork(); 
    if (pid < 0) { 
        printf("Fork failed.\n"); 
    } else if (pid == 0) { 
        printf("Child process created. PID: %d\n", getpid()); 
    } else { 
        printf("Parent process. Child PID: %d\n", pid); 
    } 
    return 0; 
}
