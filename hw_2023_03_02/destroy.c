#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main() {
    key_t key = ftok("file.txt", 'R');
    if (key == -1) {
        perror("Failed to generate key");
        exit(EXIT_FAILURE);
    }
    int shmid = shmget(key, 0, 0);
    if (shmid == -1) {
        perror("Failed to get shared memory segment");
        exit(EXIT_FAILURE);
    }
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("Failed to mark shared memory segment for removal");
        exit(EXIT_FAILURE);
    }
    if (remove("file.txt") == -1) {
        perror("Failed to remove file");
        exit(EXIT_FAILURE);
    }
    printf("Shared memory segment and file removed successfully\n");
    return 0;
}

