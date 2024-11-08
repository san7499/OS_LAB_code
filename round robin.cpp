#include <stdio.h>
#define MAX 10

typedef struct {
    int pid, arrival, burst, remaining, completion, waiting, turnaround;
} Process;

void roundRobin(Process p[], int n, int quantum) {
    int time = 0, completed = 0, queue[MAX], front = 0, rear = 0;
    int visited[MAX] = {0};

    for (int i = 0; i < n; i++) {
        p[i].remaining = p[i].burst;
    }

    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].remaining > 0 && !visited[i]) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }

        if (front < rear) {
            int index = queue[front++];
            int execTime = p[index].remaining < quantum ? p[index].remaining : quantum;
            time += execTime;
            p[index].remaining -= execTime;

            if (p[index].remaining == 0) {
                completed++;
                p[index].completion = time;
                p[index].turnaround = time - p[index].arrival;
                p[index].waiting = p[index].turnaround - p[index].burst;
            } else {
                for (int i = 0; i < n; i++) {
                    if (p[i].arrival <= time && p[i].remaining > 0 && !visited[i]) {
                        queue[rear++] = i;
                        visited[i] = 1;
                    }
                }
                queue[rear++] = index;
            }
        } else {
            time++;
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
    int n, quantum;
    Process p[MAX];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter arrival and burst time for P%d: ", p[i].pid);
        scanf("%d %d", &p[i].arrival, &p[i].burst);
    }

    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    roundRobin(p, n, quantum);
    display(p, n);
    return 0;
}

