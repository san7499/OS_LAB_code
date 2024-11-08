#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void bubbleSort(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void selectionSort(int arr[], int n) {
    int i, j, minIdx, temp;
    for (i = 0; i < n - 1; i++) {
        minIdx = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        temp = arr[minIdx];
        arr[minIdx] = arr[i];
        arr[i] = temp;
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int n, i;
    
    printf("Enter the number of elements to sort: ");
    scanf("%d", &n);
    int arr[n];
    
    printf("Enter %d integers:\n", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    pid_t pid = fork();
    
    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }
    
    if (pid == 0) {
        // Child process: orphaned when parent finishes first.
        sleep(2); // Delay to show orphan state after parent exits
        printf("Child process is sorting using selection sort:\n");
        selectionSort(arr, n);
        printArray(arr, n);
        printf("Child process completed.\n");
        exit(0);
    } else {
        // Parent process
        printf("Parent process is sorting using bubble sort:\n");
        bubbleSort(arr, n);
        printArray(arr, n);
        
        printf("Parent process waiting for child to complete...\n");
        wait(NULL); // Wait for child process to complete, demonstrating zombie state if parent does not call wait
        printf("Parent process completed.\n");
    }
    
    return 0;
}

