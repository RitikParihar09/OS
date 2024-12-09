#include<stdio.h>
#include<stdlib.h>
void main(){
    int n;
    printf("Enter number of disk requests: ");
    scanf("%d",&n);
    int request[n];
    for(int i=0;i<n;i++){
        scanf("%d",&request[i]);
    }
    printf("Enter head :");
    int head;
    scanf("%d",&head);
    printf("Sequence: %d->",head);
    int seekMovement=0;
    for(int i=0;i<n;i++){
        seekMovement+=abs(request[i]-head);
        head=request[i];
        printf("%d->",head);
    }
    printf("\nSeek Movement: %d",seekMovement);
}