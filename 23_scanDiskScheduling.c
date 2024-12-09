#include <stdio.h>
#include <stdlib.h>

void scanDiskScheduling(int requests[], int n, int head, int disk_size, int direction) {
    int seek_sequenece[n+1];
    int seekCount=0;
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            if(requests[j]>requests[j+1]){
                int temp=requests[j];
                requests[j]=requests[j+1];
                requests[j+1]=temp;
            }
        }
    }
    int start=-1;
    for(int i=0;i<n;i++){
        if(requests[i]>=head){
            start=i;
            break;
        }
    }
    if(direction==1){
        for(int i=start;i<n;i++){
            seek_sequenece[seekCount++]=requests[i];
        }
        if(start > 0){
          seek_sequenece[seekCount++]=disk_size-1;
          for(int i=start-1;i>=0;i--){
            seek_sequenece[seekCount++]=requests[i];
          }
        }
    }else{
        for(int i=start-1;i>=0;i--){
            seek_sequenece[seekCount++]=requests[i];
        }
        if (start < n){
        seek_sequenece[seekCount++]=0;
        for(int i=start;i<n;i++){
            seek_sequenece[seekCount++]=requests[i];
        }
        }
    }
    int seekMovement=0;
    int currentVal=head;
    for(int i=0;i<seekCount;i++){
        seekMovement+=abs(seek_sequenece[i]-currentVal);
        currentVal=seek_sequenece[i];
        printf("%d ",currentVal);
    }
    printf("\nseek Movement: %d",seekMovement);
}

int main() {
    int n, head, disk_size=200, direction;

    printf("Enter number of requests: ");
    scanf("%d", &n);
    int requests[n];

    printf("Enter the requests: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter current position of head: ");
    scanf("%d", &head);


    printf("Enter direction (1 for high, 0 for low): ");
    scanf("%d", &direction);

    scanDiskScheduling(requests, n, head, disk_size, direction);

    return 0;
}
