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

void scanAlgorithm(int requests[], int n, int initial, int direction) {
    sortRequests(requests, n);
    int totalSeekTime = 0, current = initial;

    printf("Initial Head Position: %d\n", current);
    printf("Order of service: %d -> ", current);

    // Move in the specified direction
    if (direction) { // Right
        for (int i = 0; i < n; i++) {
            if (requests[i] >= current) {
                totalSeekTime += abs(requests[i] - current);
                current = requests[i];
                printf("%d -> ", current);
            }
        }
        totalSeekTime += abs(199 - current);
        current = 199;
        printf("199 -> ");

        for (int i = n - 1; i >= 0; i--) {
            if (requests[i] < 199) {
                totalSeekTime += abs(requests[i] - current);
                current = requests[i];
                printf("%d -> ", current);
            }
        }
    } else { // Left
        for (int i = n - 1; i >= 0; i--) {
            if (requests[i] <= current) {
                totalSeekTime += abs(requests[i] - current);
                current = requests[i];
                printf("%d -> ", current);
            }
        }
        totalSeekTime += abs(0 - current);
        current = 0;
        printf("0 -> ");

        for (int i = 0; i < n; i++) {
            if (requests[i] > 0) {
                totalSeekTime += abs(requests[i] - current);
                current = requests[i];
                printf("%d -> ", current);
            }
        }
    }

    printf("\nTotal Seek Time: %d\n", totalSeekTime);
}

int main() {
    int n, initial, direction;
    int requests[20];

    printf("Enter the number of requests: ");
    scanf("%d", &n);
    printf("Enter the request queue: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }
    printf("Enter the initial head position: ");
    scanf("%d", &initial);
    printf("Enter the direction (1 for right, 0 for left): ");
    scanf("%d", &direction);

    scanAlgorithm(requests, n, initial, direction);
    return 0;
}

