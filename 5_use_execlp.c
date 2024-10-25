#include <stdio.h>  
#include <unistd.h>  

int main() {  
    printf("Use of execlp Command:\n");  
    
    // Replace the current process with the "ls" command
    execlp("ls", "ls", NULL);  

    // If execlp() fails, this line will be executed
    perror("execlp failed");  

    return 0;  
}
