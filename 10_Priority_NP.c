#include <stdio.h>

struct Process {
    int pid, arrivalTime, burstTime, completionTime, turnAroundTime, waitingTime, priority;
};

int main() {
    int n;
    printf("Enter Number of Processes: ");
    scanf("%d", &n);
    struct Process p[n];

    // Taking input: Arrival Time, Burst Time, and Priority
    for (int i = 0; i < n; i++) {
        printf("Enter Arrival Time, Burst Time, and Priority for Process %d: ", i);
        scanf("%d %d %d", &p[i].arrivalTime, &p[i].burstTime, &p[i].priority);
        p[i].pid = i;
    }

    // Variables for time tracking
    int currTime = 0, completed = 0, totalTaT = 0, totalWT = 0;

    printf("\nGantt Chart:\n|");

    // Loop until all processes are completed
    while (completed < n) {
        int highestPriority = 10000;  // A large number to compare priorities
        int selected = -1;

        // Select the highest priority process that has arrived and is not completed
        for (int i = 0; i < n; i++) {
            if (p[i].arrivalTime <= currTime && p[i].priority < highestPriority && p[i].completionTime == 0) {
                highestPriority = p[i].priority;
                selected = i;
            }
        }

        // If no process is available, increment the current time (idle time)
        if (selected == -1) {
            currTime++;
            continue;
        }

        // Execute the selected process completely
        printf(" P%d |", p[selected].pid);
        currTime += p[selected].burstTime;
        p[selected].completionTime = currTime;
        p[selected].turnAroundTime = p[selected].completionTime - p[selected].arrivalTime;
        p[selected].waitingTime = p[selected].turnAroundTime - p[selected].burstTime;

        totalTaT += p[selected].turnAroundTime;
        totalWT += p[selected].waitingTime;
        completed++;
    }

    // Print each process's details
    printf("\n\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].arrivalTime, p[i].burstTime, p[i].priority,
               p[i].completionTime, p[i].turnAroundTime, p[i].waitingTime);
    }

    // Average Turnaround Time and Waiting Time
    printf("\nAverage Waiting Time: %.2f", (float)totalWT / n);
    printf("\nAverage Turnaround Time: %.2f\n", (float)totalTaT / n);

    return 0;
}
