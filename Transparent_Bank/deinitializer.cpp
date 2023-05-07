#include <sys/ipc.h>
#include <sys/shm.h>
#include "bank.h"

int destroy_bank() {
    key_t shm_key = ftok("bank.h", 'R');
    if (shm_key == -1) {
        return 1;
    }

    int shm_id = shmget(shm_key, sizeof(bank_t), 0666);
    if (shm_id < 0) {
        return 1;
    }

    if (shmctl(shm_id, IPC_RMID, NULL) < 0) {
        return 1;
    }

    return 0;
}
