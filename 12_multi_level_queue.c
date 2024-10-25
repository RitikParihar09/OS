#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>  // For strcat()

struct Process {
    int pid, arrivalTime, burstTime, completionTime, turnAroundTime, waitingTime;
    bool isSystemProcess;  // True for system process, false for user process
};

void fcfs(struct Process p[], int n, int *currTime, char ganttChart[]) {
    for (int i = 0; i < n; i++) {
        if (*currTime < p[i].arrivalTime) {
            *currTime = p[i].arrivalTime;  // Jump to arrival time if CPU is idle
        }
        p[i].completionTime = *currTime + p[i].burstTime;
        p[i].turnAroundTime = p[i].completionTime - p[i].arrivalTime;
        p[i].waitingTime = p[i].turnAroundTime - p[i].burstTime;
        *currTime = p[i].completionTime;

        // Append to the Gantt chart
        char buffer[10];
        sprintf(buffer, " P%d |", p[i].pid);
        strcat(ganttChart, buffer);
    }
}

void calculateAverages(struct Process p[], int n, float *avgWT, float *avgTAT) {
    int totalWT = 0, totalTAT = 0;
    for (int i = 0; i < n; i++) {
        totalWT += p[i].waitingTime;
        totalTAT += p[i].turnAroundTime;
    }
    *avgWT = (float)totalWT / n;
    *avgTAT = (float)totalTAT / n;
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    // Initialize all processes as user processes
    for (int i = 0; i < n; i++) {
        processes[i].isSystemProcess = false;
    }

    // Take burst times as input
    printf("Enter burst times: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &processes[i].burstTime);
        processes[i].pid = i;
    }

    // Take arrival times as input
    printf("Enter arrival times: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &processes[i].arrivalTime);
    }

    // Mark system processes
    printf("Enter process IDs of system processes (space-separated, end with -1): ");
    int pid;
    while (scanf("%d", &pid) && pid != -1) {
        if (pid >= 0 && pid < n) {
            processes[pid].isSystemProcess = true;
        }
    }

    // Separate processes into system and user queues
    struct Process systemQueue[n], userQueue[n];
    int systemCount = 0, userCount = 0;

    for (int i = 0; i < n; i++) {
        if (processes[i].isSystemProcess) {
            systemQueue[systemCount++] = processes[i];
        } else {
            userQueue[userCount++] = processes[i];
        }
    }

    // Initialize Gantt chart
    char ganttChart[1000] = "|";
    int currTime = 0;

    // Schedule system processes (higher priority)
    fcfs(systemQueue, systemCount, &currTime, ganttChart);

    // Schedule user processes (lower priority)
    fcfs(userQueue, userCount, &currTime, ganttChart);

    // Calculate averages for both queues
    float avgWTSystem, avgTATSystem, avgWTUser, avgTATUser;
    calculateAverages(systemQueue, systemCount, &avgWTSystem, &avgTATSystem);
    calculateAverages(userQueue, userCount, &avgWTUser, &avgTATUser);

    // Output the Gantt chart
    printf("\nGantt Chart:\n%s\n", ganttChart);

    // Output the averages
    printf("System Processes - Average Waiting Time: %.2f\n", avgWTSystem);
    printf("System Processes - Average Turnaround Time: %.2f\n", avgTATSystem);
    printf("User Processes - Average Waiting Time: %.2f\n", avgWTUser);
    printf("User Processes - Average Turnaround Time: %.2f\n", avgTATUser);

    return 0;
}
