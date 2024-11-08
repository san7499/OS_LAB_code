#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#define FIFO1 "fifo1"
#define FIFO2 "fifo2"
#define BUFFER_SIZE 1024

// Function to count characters, words, and lines in a string
void count_text(const char *text, int *char_count, int *word_count, int *line_count) {
    *char_count = *word_count = *line_count = 0;
    int in_word = 0;
    
    for (int i = 0; text[i] != '\0'; i++) {
        (*char_count)++;
        
        if (text[i] == ' ' || text[i] == '\n' || text[i] == '\t') {
            if (in_word) {
                (*word_count)++;
                in_word = 0;
            }
            if (text[i] == '\n') (*line_count)++;
        } else {
            in_word = 1;
        }
    }
    
    if (in_word) (*word_count)++;
}

// First process: Takes user input and writes to FIFO1, then reads results from FIFO2
void process1() {
    char buffer[BUFFER_SIZE];
    int fd1, fd2;
    
    // Create FIFOs if they don't exist
    mkfifo(FIFO1, 0666);
    mkfifo(FIFO2, 0666);

    printf("Enter text (type 'exit' to quit): ");
    while (1) {
        fgets(buffer, BUFFER_SIZE, stdin);
        
        if (strncmp(buffer, "exit", 4) == 0) break;

        // Write the input to FIFO1
        fd1 = open(FIFO1, O_WRONLY);
        write(fd1, buffer, strlen(buffer) + 1);
        close(fd1);

        // Read the result from FIFO2
        fd2 = open(FIFO2, O_RDONLY);
        read(fd2, buffer, BUFFER_SIZE);
        printf("Received from process 2:\n%s\n", buffer);
        close(fd2);
    }
}

// Second process: Reads from FIFO1, counts characters/words/lines, writes result to FIFO2
void process2() {
    char buffer[BUFFER_SIZE];
    int char_count, word_count, line_count;
    int fd1, fd2;

    // Create FIFOs if they don't exist
    mkfifo(FIFO1, 0666);
    mkfifo(FIFO2, 0666);

    FILE *output_file = fopen("output.txt", "w");

    while (1) {
        // Read from FIFO1
        fd1 = open(FIFO1, O_RDONLY);
        read(fd1, buffer, BUFFER_SIZE);
        close(fd1);

        if (strncmp(buffer, "exit", 4) == 0) break;

        // Count characters, words, and lines
        count_text(buffer, &char_count, &word_count, &line_count);

        // Write results to output file
        output_file = fopen("output.txt", "w");
        fprintf(output_file, "Characters: %d\nWords: %d\nLines: %d\n", char_count, word_count, line_count);
        fclose(output_file);

        // Read the output file and write to FIFO2
        output_file = fopen("output.txt", "r");
        fread(buffer, sizeof(char), BUFFER_SIZE, output_file);
        fclose(output_file);

        fd2 = open(FIFO2, O_WRONLY);
        write(fd2, buffer, strlen(buffer) + 1);
        close(fd2);
    }
    
    unlink(FIFO1);
    unlink(FIFO2);
}

int main() {
    pid_t pid = fork();
    
    if (pid > 0) {
        // Parent process
        process1();
    } else if (pid == 0) {
        // Child process
        process2();
    } else {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    return 0;
}

