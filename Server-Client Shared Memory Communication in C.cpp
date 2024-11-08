//server.c//

// server.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>

#define SHM_KEY 12345  // Unique key for shared memory

int main() {
    int shmid;
    char *shared_memory;

    // Create a shared memory segment
    shmid = shmget(SHM_KEY, 1024, 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget failed");
        exit(1);
    }

    // Attach to the shared memory segment
    shared_memory = (char*) shmat(shmid, NULL, 0);
    if (shared_memory == (char*) -1) {
        perror("shmat failed");
        exit(1);
    }

    // Write a message to shared memory
    strcpy(shared_memory, "Hello from the server!");

    printf("Server: Message written to shared memory.\n");

    // Detach from the shared memory
    shmdt(shared_memory);

    return 0;
}

//client.c//

// client.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#define SHM_KEY 12345  // Must match the server's key

int main() {
    int shmid;
    char *shared_memory;

    // Locate the shared memory segment created by the server
    shmid = shmget(SHM_KEY, 1024, 0666);
    if (shmid == -1) {
        perror("shmget failed");
        exit(1);
    }

    // Attach to the shared memory segment
    shared_memory = (char*) shmat(shmid, NULL, 0);
    if (shared_memory == (char*) -1) {
        perror("shmat failed");
        exit(1);
    }

    // Read the message from shared memory and display it
    printf("Client: Message from shared memory: %s\n", shared_memory);

    // Detach from the shared memory
    shmdt(shared_memory);

    // Optional: remove the shared memory segment
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}

