#include <stdio.h>
#define MAX 10

typedef struct {
    int pid, arrival, burst, remaining, completion, waiting, turnaround;
} Process;

void sortByArrival(Process p[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (p[j].arrival > p[j + 1].arrival) {
                Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
}

void sjfPreemptive(Process p[], int n) {
    int completed = 0, time = 0, minIndex;
    
    sortByArrival(p, n);
    while (completed != n) {
        minIndex = -1;
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].remaining > 0 && 
                (minIndex == -1 || p[i].remaining < p[minIndex].remaining)) {
                minIndex = i;
            }
        }

        if (minIndex == -1) {
            time++;
            continue;
        }

        p[minIndex].remaining--;
        time++;

        if (p[minIndex].remaining == 0) {
            completed++;
            p[minIndex].completion = time;
            p[minIndex].turnaround = time - p[minIndex].arrival;
            p[minIndex].waiting = p[minIndex].turnaround - p[minIndex].burst;
        }
    }
}

void display(Process p[], int n) {
    float totalWait = 0, totalTurnaround = 0;
    printf("PID\tArrival\tBurst\tCompletion\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        totalWait += p[i].waiting;
        totalTurnaround += p[i].turnaround;
        printf("%d\t%d\t%d\t%d\t\t%d\t%d\n", p[i].pid, p[i].arrival, p[i].burst, 
               p[i].completion, p[i].waiting, p[i].turnaround);
    }
    printf("Avg Waiting Time: %.2f\n", totalWait / n);
    printf("Avg Turnaround Time: %.2f\n", totalTurnaround / n);
}

int main() {
    int n;
    Process p[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter arrival and burst time for P%d: ", p[i].pid);
        scanf("%d %d", &p[i].arrival, &p[i].burst);
        p[i].remaining = p[i].burst;
    }

    sjfPreemptive(p, n);
    display(p, n);
    return 0;
}

