#include <stdio.h>

// Process structure to hold process details
struct Process {
    int arrivalTime;
    int burstTime;
    int completionTime;
    int waitingTime;
    int turnaroundTime;
};

// Function to perform SJF scheduling
void sjfScheduling(struct Process processes[], int n) {
    int currentTime = 0; // Current time
    int totalCompletionTime = 0; // Total completion time

    // Loop through each process
    for (int i = 0; i < n; i++) {
        // Find the process with the shortest burst time
        int shortestIndex = -1;
        int shortestBurst = __INT_MAX__;
        for (int j = 0; j < n; j++) {
            if (processes[j].arrivalTime <= currentTime && processes[j].burstTime < shortestBurst && processes[j].completionTime == -1) {
                shortestBurst = processes[j].burstTime;
                shortestIndex = j;
            }
        }

        // If a process is found
        if (shortestIndex != -1) {
            // Update current time
            currentTime += processes[shortestIndex].burstTime;

            // Update completion time, waiting time, and turnaround time
            processes[shortestIndex].completionTime = currentTime;
            processes[shortestIndex].turnaroundTime = processes[shortestIndex].completionTime - processes[shortestIndex].arrivalTime;
            processes[shortestIndex].waitingTime = processes[shortestIndex].turnaroundTime - processes[shortestIndex].burstTime;
            // Update total completion time
            totalCompletionTime += processes[shortestIndex].completionTime;
        }
    }
}

// Function to calculate average waiting time and average turnaround time
void calculateAverages(struct Process processes[], int n, float *avgWaitingTime, float *avgTurnaroundTime) {
    *avgWaitingTime = 0;
    *avgTurnaroundTime = 0;
    for (int i = 0; i < n; i++) {
        *avgWaitingTime += processes[i].waitingTime;
        *avgTurnaroundTime += processes[i].turnaroundTime;
    }
    *avgWaitingTime /= n;
    *avgTurnaroundTime /= n;
}

// Function to display process details
void displayProcesses(struct Process processes[], int n) {
    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, processes[i].arrivalTime, processes[i].burstTime, processes[i].completionTime, processes[i].waitingTime, processes[i].turnaroundTime);
    }
}

int main() {
    int n; // Number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n]; // Array to store processes

    // Input arrival time and burst time for each process
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrivalTime, &processes[i].burstTime);
        processes[i].completionTime = -1; // Initialize completion time to -1
        processes[i].waitingTime = 0;
        processes[i].turnaroundTime = 0;
    }

    // Perform SJF scheduling
    sjfScheduling(processes, n);

    // Calculate average waiting time and average turnaround time
    float avgWaitingTime, avgTurnaroundTime;
    calculateAverages(processes, n, &avgWaitingTime, &avgTurnaroundTime);

    // Display process details
    displayProcesses(processes, n);
    printf("\nAverage Waiting Time: %.2f\n", avgWaitingTime);
    printf("Average Turnaround Time: %.2f\n", avgTurnaroundTime);

    return 0;
}
