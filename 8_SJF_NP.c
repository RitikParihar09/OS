#include <stdio.h>
#include <limits.h>
struct Process {
    int pid, arrivalTime, burstTime, completionTime, turnAroundTime, waitingTime,isCompleted;
};

int main() {
    int n;
    printf("Enter Number of Processes: ");
    scanf("%d", &n);
    struct Process p[n];

    // Taking Arrival Time and Burst Time as input
    for (int i = 0; i < n; i++) {
        printf("Enter Arrival Time and Burst Time for Process %d: ", i);
        scanf("%d %d", &p[i].arrivalTime, &p[i].burstTime);
        p[i].pid = i;
        p[i].isCompleted=0;
    }

    // Gantt Chart with Time
    printf("\nGantt Chart: |");
    int currTime = 0, totalTaT = 0, totalWT = 0,Completed=0;

    while (Completed<n) {
        int shortest=-1;
        int minBurst=INT_MAX;
        for(int i=0;i<n;i++){
            if(p[i].arrivalTime<=currTime&&!p[i].isCompleted&&p[i].burstTime<minBurst){
                minBurst=p[i].burstTime;
                shortest=i;
            }
        }
        if(shortest==-1){
            currTime++;
            continue;
        }
        printf("p%d |",p[shortest].pid);
        // Process calculations
        currTime += p[shortest].burstTime;
        p[shortest].completionTime = currTime;
        p[shortest].turnAroundTime = p[shortest].completionTime - p[shortest].arrivalTime;
        p[shortest].waitingTime = p[shortest].turnAroundTime - p[shortest].burstTime;
        totalTaT += p[shortest].turnAroundTime;
        totalWT += p[shortest].waitingTime;
        
        if(p[shortest].waitingTime<0){
            p[shortest].waitingTime=0;
        }
        
        p[shortest].isCompleted=1;
        Completed++;
    }

    // Print each process's details
    printf("\n\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", 
            p[i].pid, p[i].arrivalTime, p[i].burstTime, 
            p[i].completionTime, p[i].turnAroundTime, p[i].waitingTime);
    }

    // Average Turnaround Time and Waiting Time
    printf("\nAverage Waiting Time: %.2f", (float)totalWT / n);
    printf("\nAverage Turnaround Time: %.2f\n", (float)totalTaT / n);

    return 0;
}
