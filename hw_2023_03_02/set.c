#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024

int main() {
    key_t key = ftok("file.txt", 'R');
    if (key == -1) {
        perror("Failed to generate key");
        exit(EXIT_FAILURE);
    }
    int shmid = shmget(key, SHM_SIZE, 0);
    if (shmid == -1) {
        perror("Failed to get shared memory segment");
        exit(EXIT_FAILURE);
    }
    char *data = (char*)shmat(shmid, NULL, 0);
    if (data == (char*)(-1)) {
        perror("Failed to attach shared memory segment");
        exit(EXIT_FAILURE);
    }
    char input[SHM_SIZE];
    while (fgets(input, SHM_SIZE, stdin)) {
        strncpy(data, input, SHM_SIZE-1);
        data[SHM_SIZE-1] = '\0';
    }
    if (shmdt(data) == -1) {
        perror("Failed to detach shared memory segment");
        exit(EXIT_FAILURE);
    }
    return 0;
}

