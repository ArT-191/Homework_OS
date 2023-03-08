#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/wait.h>

void sem_wait(int semid, int sem_num) {
    struct sembuf op = {sem_num, -1, 0};
    semop(semid, &op, 1);
}

void sem_signal(int semid, int sem_num) {
    struct sembuf op = {sem_num, 1, 0};
    semop(semid, &op, 1);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s N\n", argv[0]);
        return 1;
    }
    
    int N = atoi(argv[1]);

    int semid = semget(IPC_PRIVATE, N, 0666 | IPC_CREAT);
    if (semid == -1) {
        perror("semget");
        return 1;
    }

    for (int i = 0; i < N; i++) {
        if (semctl(semid, i, SETVAL, 0) == -1) {
            perror("semctl SETVAL");
            return 1;
        }
    }

    for (int i = 0; i < N; i++) {
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            return 1;
        }
        else if (pid == 0) {
            sem_wait(semid, i);
            printf("%d\n", i + 1);
            sem_signal(semid, (i + 1) % N);
            return 0;
        }
    }

    sem_signal(semid, 0);

    for (int i = 0; i < N; i++) {
        wait(NULL);
    }

    if (semctl(semid, 0, IPC_RMID) == -1) {
        perror("semctl IPC_RMID");
        return 1;
    }

    return 0;
}
