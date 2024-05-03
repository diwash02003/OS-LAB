#include <stdio.h>
#include <stdlib.h>

struct process {
    int pid;
    int arrival_time;
    int burst_time;
    int start_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
};
int compare1(const void *a, const void *b) {
    struct process *p1 = (struct process *)a;
    struct process *p2 = (struct process *)b;
    return (p1->arrival_time - p2->arrival_time);
}
int compare2(const void *a, const void *b) {
    struct process *p1 = (struct process *)a;
    struct process *p2 = (struct process *)b;
    return (p1->pid - p2->pid);
}
int main() {
    int n, tq, idx;
    float avg_turnaround_time, avg_waiting_time, avg_response_time, cpu_utilisation, throughput;
    int total_turnaround_time = 0, total_waiting_time = 0, total_response_time = 0, total_idle_time = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter time quantum: ");
    scanf("%d", &tq);
    struct process p[100];
    int burst_remaining[100];
    int mark[100] = {0};
    int current_time = 0, completed = 0;
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time of process %d:  ", i + 1);
        scanf("%d", &p[i].arrival_time);
        printf("Enter burst time of process %d:    ", i + 1);
        scanf("%d", &p[i].burst_time);
        burst_remaining[i] = p[i].burst_time;
        p[i].pid = i + 1;
    }

    qsort(p, n, sizeof(struct process), compare1);

    int q[100], front = -1, rear = -1;
    q[++rear] = 0;
    mark[0] = 1;

    while (completed != n) {
        idx = q[++front];

        if (burst_remaining[idx] == p[idx].burst_time) {
            p[idx].start_time = (current_time > p[idx].arrival_time) ? current_time : p[idx].arrival_time;
            total_idle_time += p[idx].start_time - current_time;
            current_time = p[idx].start_time;
        }

        if (burst_remaining[idx] - tq > 0) {
            burst_remaining[idx] -= tq;
            current_time += tq;
        } else {
            current_time += burst_remaining[idx];
            burst_remaining[idx] = 0;
            completed++;

            p[idx].completion_time = current_time;
            p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
            p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
            p[idx].response_time = p[idx].start_time - p[idx].arrival_time;

            total_turnaround_time += p[idx].turnaround_time;
            total_waiting_time += p[idx].waiting_time;
            total_response_time += p[idx].response_time;
        }

        for (int i = 1; i < n; i++) {
            if (burst_remaining[i] > 0 && p[i].arrival_time <= current_time && mark[i] == 0) {
                q[++rear] = i;
                mark[i] = 1;
            }
        }
        if (burst_remaining[idx] > 0) {
            q[++rear] = idx;
        }

        if (front == rear) {
            for (int i = 1; i < n; i++) {
                if (burst_remaining[i] > 0) {
                    q[++rear] = i;
                    mark[i] = 1;
                    break;
                }
            }
        }
    }

    avg_turnaround_time = (float)total_turnaround_time / n;
    avg_waiting_time = (float)total_waiting_time / n;
    avg_response_time = (float)total_response_time / n;
    cpu_utilisation = ((p[n - 1].completion_time - total_idle_time) / (float)p[n - 1].completion_time) * 100;
    throughput = (float)n / (p[n - 1].completion_time - p[0].arrival_time);

    qsort(p, n, sizeof(struct process), compare2);

    printf("\n#P\tArrival Time\tBurst Time\tStart Time\tCompletion Time\tTurnaround Time\tWaiting Time\tResponse Time\n\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].arrival_time, p[i].burst_time, p[i].start_time, p[i].completion_time, p[i].turnaround_time, p[i].waiting_time, p[i].response_time);
    }

    printf("Average Turnaround Time = %.2f\n", avg_turnaround_time);
    printf("Average Waiting Time = %.2f\n", avg_waiting_time);
    printf("Average Response Time = %.2f\n", avg_response_time);
    printf("CPU Utilization = %.2f%%\n", cpu_utilisation);
    printf("Throughput = %.2f process/unit time\n", throughput);

    return 0;
}
