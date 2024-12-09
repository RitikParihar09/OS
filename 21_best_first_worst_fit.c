#include <stdio.h>
void firstFit(int block[], int process[] ,int block_size,int process_size){
    int allocation[process_size];
    int usedBlock[block_size];
    for(int i=0;i<process_size;i++) allocation[i]=-1;
    for(int i=0;i<block_size;i++) usedBlock[i]=0;
    
    for(int i=0;i<process_size;i++){
        for(int j=0;j<block_size;j++){
            if(!usedBlock[j]&&block[j]>=process[i]){
                usedBlock[j]=1;
                allocation[i]=j;
                break;
            }
        }
    }
    
    for(int i=0;i<process_size;i++){
        if(allocation[i]!=-1){
            printf("%d - %d\n",process[i],allocation[i]+1);
        }else{
            printf("%d - no free block allocted.\n",process[i]);
        }
    }
}
void bestFit(int block[], int process[] ,int block_size,int process_size){
    int allocation[process_size];
    int usedBlock[block_size];
    for(int i=0;i<process_size;i++) allocation[i]=-1;
    for(int i=0;i<block_size;i++) usedBlock[i]=0;
    
    for(int i=0;i<process_size;i++){
        int bestIndex=-1;
        for(int j=0;j<block_size;j++){
            if(!usedBlock[j]&&block[j]>=process[i]){
                if(bestIndex==-1||block[j]<block[bestIndex]){
                    bestIndex=j;
                }
            }
        }
        if(bestIndex!=-1){
            allocation[i]=bestIndex;
            usedBlock[bestIndex]=1;
        }
    }
    
    for(int i=0;i<process_size;i++){
        if(allocation[i]!=-1){
            printf("%d - %d\n",process[i],allocation[i]+1);
        }else{
            printf("%d - no free block allocted.\n",process[i]);
        }
    }
}

void worstFit(int block[], int process[] ,int block_size,int process_size){
    int allocation[process_size];
    int usedBlock[block_size];
    for(int i=0;i<process_size;i++) allocation[i]=-1;
    for(int i=0;i<block_size;i++) usedBlock[i]=0;
    
    for(int i=0;i<process_size;i++){
        int bestIndex=-1;
        for(int j=0;j<block_size;j++){
            if(!usedBlock[j]&&block[j]>=process[i]){
                if(bestIndex==-1||block[j]>block[bestIndex]){
                    bestIndex=j;
                }
            }
        }
        if(bestIndex!=-1){
            allocation[i]=bestIndex;
            usedBlock[bestIndex]=1;
        }
    }
    
    for(int i=0;i<process_size;i++){
        if(allocation[i]!=-1){
            printf("%d - %d\n",process[i],allocation[i]+1);
        }else{
            printf("%d - no free block allocted.\n",process[i]);
        }
    }
}


int main()
{
    int block_size,process_size;
    printf("Enter number of free blocks availables: ");
    scanf("%d",&block_size);
    int block[block_size];
    for(int i=0;i<block_size;i++){
        scanf("%d",&block[i]);
    }
    printf("Enter number of Process: ");
    scanf("%d",&process_size);
    int process[process_size];
    for(int i=0;i<process_size;i++){
        scanf("%d",&process[i]);
    }
    // test case:
    // 5
    // 100 500 200 300 600
    // 4
    //   212 417 112 426

    printf("Output: \n\n");
    printf("First Fit:\n");
    firstFit(block,process,block_size,process_size);
    printf("Best Fit:\n");
    bestFit(block,process,block_size,process_size);
    printf("Worst Fit:\n");
    worstFit(block,process,block_size,process_size);
    
    return 0;
}