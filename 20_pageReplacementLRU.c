#include <stdio.h>
int findLRU(int times[],int f){
    int pos=0;int minValue=times[0];
    for(int i=1;i<f;i++){
        if(times[i]<minValue){
            minValue=times[i];
            pos=i;
        }
    }
    return pos;
}

void pageReplacementLRU(int pages[],int n,int f){
    int frames[f];
    int isPageFound;
    int pageFaultCount=0;
    int counter=0;
    int times[f];
    for(int i=0;i<f;i++){
        frames[i]=-1;
    }
    
    for(int i=0;i<n;i++){
        isPageFound=0;
        for(int j=0;j<f;j++){
            if(frames[j]==pages[i]){
                isPageFound=1;
                times[j]=++counter;
                break;
            }
        }
        
        if(!isPageFound){
            if(i<f){
                times[i]=++counter;
                frames[i]=pages[i];
            }else{
                int pos=findLRU(times,f);
                times[pos]=++counter;
                frames[pos]=pages[i];
            }
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
    pageReplacementLRU(pages,n,f);
    return 0;
}
