#include "bank.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <iostream>

 void destroy_bank() {   
    int shmid;
    key_t key = ftok(".", 'R');
    if (key == -1) {
        perror("Error: Failed to generate key with ftok");
        return ;
    }

    std::cout << key;
    
    // create shared memory segment
    if ((shmid = shmget(key, 0, 0666)) == -1) {
        perror("Error: Failed to create shared memory segment for bank and accounts");
        return ;
    }

    shmctl(shmid, IPC_RMID, nullptr);
    
}

int main(){
    destroy_bank();
}
