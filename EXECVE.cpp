// main_program.c//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

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

int main(int argc, char *argv[]) {
    int n, i;
    
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d integers:\n", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Sort the array
    bubbleSort(arr, n);
    
    printf("Parent process sorted array:\n");
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Convert sorted array elements to strings for execve
    char *args[n + 2]; // n elements + program name + NULL terminator
    args[0] = "./reverse_display"; // Program name for execve
    for (i = 0; i < n; i++) {
        char *num_str = malloc(10);
        sprintf(num_str, "%d", arr[i]);
        args[i + 1] = num_str;
    }
    args[n + 1] = NULL; // Null terminate the argument list

    // Create child process
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process: use execve to run reverse_display
        if (execve("./reverse_display", args, NULL) == -1) {
            perror("execve failed");
            exit(1);
        }
    } else {
        // Parent process
        wait(NULL); // Wait for child to finish
        printf("Parent process completed.\n");

        // Free allocated memory
        for (i = 1; i <= n; i++) {
            free(args[i]);
        }
    }

    return 0;
}


//reverse_display.c//

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("No elements to display.\n");
        return 1;
    }

    printf("Child process displaying array in reverse order:\n");
    for (int i = argc - 1; i > 0; i--) {
        printf("%s ", argv[i]);
    }
    printf("\n");

    return 0;
}

