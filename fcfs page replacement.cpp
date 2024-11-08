#include <stdio.h>

int main() {
    int pages[30], frames[10], n, f, pageFaults = 0;
    int i, j, k = 0;

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
            if (frames[j] == pages[i]) {
                found = 1; // Page hit
                break;
            }
        }

        if (!found) { // Page fault
            frames[k] = pages[i];
            k = (k + 1) % f; // Replace in a circular manner
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

