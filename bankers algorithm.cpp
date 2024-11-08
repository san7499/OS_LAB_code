#include <stdio.h>
#define MAX_PROCESSES 5
#define MAX_RESOURCES 3

int available[MAX_RESOURCES];
int maximum[MAX_PROCESSES][MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];

void calculateNeed(int p, int r) {
    for (int i = 0; i < p; i++)
        for (int j = 0; j < r; j++)
            need[i][j] = maximum[i][j] - allocation[i][j];
}

int isSafe(int p, int r) {
    int work[MAX_RESOURCES], finish[MAX_PROCESSES] = {0}, safeSequence[MAX_PROCESSES], count = 0;
    for (int i = 0; i < r; i++) work[i] = available[i];

    while (count < p) {
        int found = 0;
        for (int i = 0; i < p; i++) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < r; j++)
                    if (need[i][j] > work[j]) break;
                
                if (j == r) {
                    for (int k = 0; k < r; k++) work[k] += allocation[i][k];
                    safeSequence[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if (!found) {
            printf("System is not in a safe state.\n");
            return 0;
        }
    }

    printf("System is in a safe state.\nSafe sequence: ");
    for (int i = 0; i < p; i++) printf("%d ", safeSequence[i]);
    printf("\n");
    return 1;
}

int main() {
    int p, r;
    printf("Enter number of processes and resources: ");
    scanf("%d %d", &p, &r);

    printf("Enter available resources: ");
    for (int i = 0; i < r; i++) scanf("%d", &available[i]);

    printf("Enter maximum resources for each process:\n");
    for (int i = 0; i < p; i++)
        for (int j = 0; j < r; j++)
            scanf("%d", &maximum[i][j]);

    printf("Enter allocated resources for each process:\n");
    for (int i = 0; i < p; i++)
        for (int j = 0; j < r; j++)
            scanf("%d", &allocation[i][j]);

    calculateNeed(p, r);
    isSafe(p, r);
    return 0;
}

