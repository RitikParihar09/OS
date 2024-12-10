#include <stdio.h>
void pageReplacementFIFO(int pages[],int n,int f){
    int frames[f];
    int isPageFound;
    int pageFaultCount=0;
    int front=0;
    for(int i=0;i<f;i++){
        frames[i]=-1;
    }
    for(int i=0;i<n;i++){
        isPageFound=0;
        for(int j=0;j<f;j++){
            if(frames[j]==pages[i]){
                isPageFound=1;
                break;
            }
        }
        if(!isPageFound){
            frames[front]=pages[i];
            front=(front+1)%f;
            pageFaultCount++;
        }
        printf("Page: %d, Frame: ", pages[i]);
        for(int j=0;j<f;j++){
            if(frames[j]!=-1){
                printf("%d ",frames[j]);
            }else{
                printf("- ");
            }
        }
        printf("\n");
    }
    printf("Page fault: %d",pageFaultCount);
}

int main()
{
    int n,f;
    
    printf("Enter number of frames availabes: ");
    scanf("%d",&f);
    printf("Enter number of requests: ");
    scanf("%d",&n);
    int pages[n];
    for(int i=0;i<n;i++){
        scanf("%d",&pages[i]);
    }
    pageReplacementFIFO(pages,n,f);
    return 0;
}
