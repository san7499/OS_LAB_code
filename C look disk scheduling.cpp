#include <stdio.h>
#include <stdlib.h>

void sortRequests(int requests[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (requests[j] > requests[j + 1]) {
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }
}

void cLookAlgorithm(int requests[], int n, int initial) {
    sortRequests(requests, n);
    int totalSeekTime = 0, current = initial;

    printf("Initial Head Position: %d\n", current);
    printf("Order of service: ");

    // Service requests in ascending order
    for (int i = 0; i < n; i++) {
        if (requests[i] >= current) {
            totalSeekTime += abs(requests[i] - current);
            current = requests[i];
            printf("%d -> ", current);
        }
    }
    
    // Jump to the first request after the last serviced request
    if (current < requests[n - 1]) {
        totalSeekTime += abs(requests[0] - current);
        current = requests[0];
        printf("%d -> ", current);
    }

    // Service remaining requests
    for (int i = 0; i < n; i++) {
        if (requests[i] > current) {
            totalSeekTime += abs(requests[i] - current);
            current = requests[i];
            printf("%d -> ", current);
        }
    }

    printf("\nTotal Seek Time: %d\n", totalSeekTime);
}

int main() {
    int n, initial;
    int requests[20];

    printf("Enter the number of requests: ");
    scanf("%d", &n);
    printf("Enter the request queue: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }
    printf("Enter the initial head position: ");
    scanf("%d", &initial);

    cLookAlgorithm(requests, n, initial);
    return 0;
}

