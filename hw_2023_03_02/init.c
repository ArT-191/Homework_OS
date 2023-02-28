#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define SHM_SIZE 1024

int main() {
    int fd = open("file.txt", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("Failed to create file");
        exit(EXIT_FAILURE);
    }
    key_t key = ftok("file.txt", 'R');
    if (key == -1) {
        perror("Failed to generate key");
        exit(EXIT_FAILURE);
    }
    int shmid = shmget(key, SHM_SIZE, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
    if (shmid == -1) {
        perror("Failed to create shared memory segment");
        exit(EXIT_FAILURE);
    }
    printf("Shared memory segment created successfully\n");
    return 0;
}

