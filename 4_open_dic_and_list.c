#include <stdio.h>  
#include <dirent.h>  

int main() { 
    DIR *dir; 
    struct dirent *entry; 

    // Open the current directory
    dir = opendir(".");  
    if (dir == NULL) { 
        perror("opendir failed");  
        return 1;  
    }

    // Read and print each entry in the directory
    while ((entry = readdir(dir)) != NULL) {  
        printf("%s\n", entry->d_name);  
    }

    // Close the directory stream
    closedir(dir);  
    return 0;  
}
