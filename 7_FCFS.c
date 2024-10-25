#include <stdio.h>

struct Process {
    int pid, arrivalTime, burstTime, completionTime, turnAroundTime, waitingTime;
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
    }

    // Sorting processes by Arrival Time (FCFS basis)
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].arrivalTime > p[j].arrivalTime) {
                struct Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    // Gantt Chart with Time
    printf("\nGantt Chart:\n|");
    int currTime = 0, totalTaT = 0, totalWT = 0;

    for (int i = 0; i < n; i++) {
        // Adjust current time if a process arrives later than the current time
        if (currTime < p[i].arrivalTime) {
            currTime = p[i].arrivalTime;
        }
        printf(" P%d |", p[i].pid);
        
        // Process calculations
        currTime += p[i].burstTime;
        p[i].completionTime = currTime;
        p[i].turnAroundTime = p[i].completionTime - p[i].arrivalTime;
        p[i].waitingTime = p[i].turnAroundTime - p[i].burstTime;

        totalTaT += p[i].turnAroundTime;
        totalWT += p[i].waitingTime;
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
