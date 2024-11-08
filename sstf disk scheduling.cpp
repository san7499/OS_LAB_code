#include <stdio.h>
#include <stdlib.h>

int findShortestSeek(int request[], int n, int current, int visited[]) {
    int minDistance = __INT_MAX__, index = -1;
    for (int i = 0; i < n; i++) {
        if (!visited[i] && abs(request[i] - current) < minDistance) {
            minDistance = abs(request[i] - current);
            index = i;
        }
    }
    return index;
}

int main() {
    int n, i, current, totalSeekTime = 0;
    int request[20], visited[20] = {0};

    printf("Enter the number of requests: ");
    scanf("%d", &n);

    printf("Enter the request queue: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &request[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &current);

    printf("\nOrder of service: %d", current);

    for (i = 0; i < n; i++) {
        int index = findShortestSeek(request, n, current, visited);
        if (index != -1) {
            visited[index] = 1;
            totalSeekTime += abs(request[index] - current);
            current = request[index];
            printf(" -> %d", current);
        }
    }

    printf("\nTotal Seek Time: %d\n", totalSeekTime);
    return 0;
}

