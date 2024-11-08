#include <stdio.h>

int findLRU(int time[], int n) {
    int i, min = time[0], pos = 0;
    for (i = 1; i < n; i++) {
        if (time[i] < min) {
            min = time[i];
            pos = i;
        }
    }
    return pos;
}

int main() {
    int frames[10], pages[30], counter = 0, time[10];
    int n, f, i, j, pos, pageFaults = 0;

    printf("Enter the number of pages: ");
    scanf("%d", &n);

    printf("Enter the reference string: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter the number of frames: ");
    scanf("%d", &f);

    for (i = 0; i < f; i++) {
        frames[i] = -1; // Initialize frames to -1 (empty)
    }

    printf("\nPage Reference String\t");
    for (i = 0; i < f; i++) {
        printf("Frame %d\t", i + 1);
    }
    printf("\n");

    for (i = 0; i < n; i++) {
        int found = 0;
        for (j = 0; j < f; j++) {
            if (frames[j] == pages[i]) { // Page hit
                counter++;
                time[j] = counter;
                found = 1;
                break;
            }
        }

        if (!found) { // Page fault
            if (pageFaults < f) {
                frames[pageFaults] = pages[i];
                time[pageFaults] = ++counter;
            } else {
                pos = findLRU(time, f);
                frames[pos] = pages[i];
                time[pos] = ++counter;
            }
            pageFaults++;
        }

        // Print the current page and the frame content
        printf("%d\t\t\t", pages[i]);
        for (j = 0; j < f; j++) {
            if (frames[j] != -1) {
                printf("%d\t", frames[j]);
            } else {
                printf("-\t");
            }
        }
        printf("\n");
    }

    printf("\nTotal Page Faults: %d\n", pageFaults);
    return 0;
}

