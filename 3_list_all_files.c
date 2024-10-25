#include <stdio.h>  
#include <stdlib.h>  
#include <unistd.h>  
#include <sys/wait.h>  

int main() {
    pid_t pid1, pid2;

    pid1 = fork();
    if (pid1 == 0) {  
        printf("First child (Running 'ls' command):\n");
        execl("/bin/ls", "ls", NULL);  
        exit(0);  
    } 
    
    wait(NULL);  
    printf("Parent: First child finished.\n");

    
    pid2 = fork();
    if (pid2 == 0) { 
        printf("Second child: My parent will exit soon.\n");
        sleep(2);  
        printf("Second child: I am now an orphan.\n");
        exit(0);
    }

    
    printf("Parent is exiting.\n");
    exit(0);
}
