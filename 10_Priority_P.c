#include <stdio.h>
#include <limits.h>

struct Process {
    int pid, arrivalTime, burstTime, completionTime, turnAroundTime, waitingTime, remainingTime, priority;
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
        p[i].remainingTime = p[i].burstTime;
    }

    printf("\nGantt Chart:\n|");
    int currTime = 0, completed = 0, totalTaT = 0, totalWT = 0;

    while (completed < n) {
        int highestPriority = INT_MAX; // Smaller value means higher priority
        int shortest = -1;

        // Select the process with the highest priority that has arrived
        for (int i = 0; i < n; i++) {
            if (p[i].arrivalTime <= currTime && p[i].remainingTime > 0 && p[i].priority < highestPriority) {
                highestPriority = p[i].priority;
                shortest = i;
            }
        }

        // If no process is available, increment time (idle)
        if (shortest == -1) {
            currTime++;
            continue;
        }

        // Execute the selected process for 1 unit of time
        printf(" P%d |", p[shortest].pid);
        p[shortest].remainingTime--;
        currTime++;

        // If the process finishes, calculate its metrics
        if (p[shortest].remainingTime == 0) {
            p[shortest].completionTime = currTime;
            p[shortest].turnAroundTime = p[shortest].completionTime - p[shortest].arrivalTime;
            p[shortest].waitingTime = p[shortest].turnAroundTime - p[shortest].burstTime;

            totalTaT += p[shortest].turnAroundTime;
            totalWT += p[shortest].waitingTime;
            completed++;
        }
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
