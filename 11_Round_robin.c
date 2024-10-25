#include <stdio.h>

struct Process {
    int pid, arrivalTime, burstTime, remainingTime, completionTime, turnAroundTime, waitingTime;
};

int main() {
    int n, quantum;
    printf("Enter Number of Processes: ");
    scanf("%d", &n);
    struct Process p[n];

    // Taking input: Arrival Time and Burst Time
    for (int i = 0; i < n; i++) {
        printf("Enter Arrival Time and Burst Time for Process %d: ", i + 1);
        scanf("%d %d", &p[i].arrivalTime, &p[i].burstTime);
        p[i].pid = i + 1; // PID starts from 1 for better user readability
        p[i].remainingTime = p[i].burstTime; // Initialize remaining time
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &quantum);

    // Variables for time tracking
    int currTime = 0, completed = 0, totalTaT = 0, totalWT = 0;

    printf("\nGantt Chart:\n|");

    // Loop until all processes are completed
    while (completed < n) {
        int done = 0; // To check if any process was executed in this iteration

        for (int i = 0; i < n; i++) {
            // Check if the process has arrived and has remaining time
            if (p[i].arrivalTime <= currTime && p[i].remainingTime > 0) {
                done = 1; // Mark that a process has been executed
                if (p[i].remainingTime > quantum) {
                    // Execute for the time quantum
                    printf(" P%d |", p[i].pid);
                    currTime += quantum;
                    p[i].remainingTime -= quantum;
                } else {
                    // Execute for the remaining time
                    printf(" P%d |", p[i].pid);
                    currTime += p[i].remainingTime;
                    p[i].completionTime = currTime;
                    p[i].turnAroundTime = p[i].completionTime - p[i].arrivalTime;
                    p[i].waitingTime = p[i].turnAroundTime - p[i].burstTime;

                    totalTaT += p[i].turnAroundTime;
                    totalWT += p[i].waitingTime;
                    p[i].remainingTime = 0; // Mark process as completed
                    completed++;
                }
            }
        }

        // If no process was executed, increment the current time (idle time)
        if (!done) {
            currTime++;
        }
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