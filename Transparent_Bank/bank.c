#include "bank.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>


bank_t *create_bank(size_t num_accounts, int max_balance) {
    int shmid;
    key_t key = ftok(".", 'R');
    if (key == -1) {
        perror("Error: Failed to generate key with ftok");
        return NULL;
    }

    size_t size = sizeof(bank_t) + num_accounts * sizeof(account_t);

    // create shared memory segment
    if ((shmid = shmget(key, size, IPC_CREAT | 0666)) == -1) {
        perror("Error: Failed to create shared memory segment for bank and accounts");
        return NULL;
    }

    // attach shared memory segment to process address space
    void *mem = shmat(shmid, NULL, 0);
    if (mem == (void *) -1) {
        perror("Error: Failed to attach shared memory segment for bank and accounts");
        return NULL;
    }

    // set pointers for bank and accounts
    bank_t *bank = (bank_t *) mem;
    account_t *accounts = (account_t *) ((char *) mem + sizeof(bank_t));

    // initialize bank and accounts
    bank->num_accounts = num_accounts;
    bank->accounts = accounts;

    for (size_t i = 0; i < num_accounts; i++) {
        accounts[i].balance = 0;
        accounts[i].min_balance = 0;
        accounts[i].max_balance = max_balance;
        accounts[i].frozen = 0;
    }

    return bank;
}



void destroy_bank(bank_t *bank) {
    key_t key = ftok("bank.h", 'R');
    int shmid = shmget(key, sizeof(bank_t) + bank->num_accounts * sizeof(account_t), 0666);
    if (shmid == -1) {
        perror("Error: Failed to get shared memory segment for bank and accounts");
        return;
    }

    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("Error: Failed to delete shared memory segment for bank and accounts");
        return;
    }

    printf("Shared memory segment for bank and accounts has been deleted\n");
}

void display_balance(const bank_t *bank, size_t account_num) {
    if (account_num >= bank->num_accounts) {
        printf("Error: Invalid account number\n");
        return;
    }

    printf("Account %zu: Current balance = %d, Minimum balance = %d, Maximum balance = %d\n",
           account_num, bank->accounts[account_num].balance, bank->accounts[account_num].min_balance,
           bank->accounts[account_num].max_balance);
}

void freeze_account(bank_t *bank, size_t account_num) {
    if (account_num >= bank->num_accounts) {
        printf("Error: Invalid account number\n");
        return;
    }

    bank->accounts[account_num].frozen = 1;
    printf("Account %zu has been frozen\n", account_num);
}

void unfreeze_account(bank_t *bank, size_t account_num) {
    if (account_num >= bank->num_accounts) {
        printf("Error: Invalid account number\n");
        return;
    }

    bank->accounts[account_num].frozen = 0;
    printf("Account %zu has been unfrozen\n", account_num);
}

void transfer(bank_t *bank, size_t from_account_num, size_t to_account_num, int amount) {
    if (from_account_num >= bank->num_accounts || to_account_num >= bank->num_accounts) {
        printf("Error: Invalid account number\n");
        return;
}
    if (bank->accounts[from_account_num].frozen || bank->accounts[to_account_num].frozen) {
    printf("Error: One or both accounts are frozen\n");
    return;
    }   
    if (bank->accounts[from_account_num].balance - amount < bank->accounts[from_account_num].min_balance) {
        printf("Error: Insufficient funds\n");
        return;
    }

    if (bank->accounts[to_account_num].balance + amount > bank->accounts[to_account_num].max_balance) {
        printf("Error: Account balance exceeds maximum\n");
        return;
    }

    bank->accounts[from_account_num].balance -= amount;
    bank->accounts[to_account_num].balance += amount;

    printf("Transferred %d from account %zu to account %zu\n", amount, from_account_num, to_account_num);
}

void credit(bank_t *bank, int amount) {
    for (size_t i = 0; i < bank->num_accounts; i++) {
        if (!bank->accounts[i].frozen) {
            bank->accounts[i].balance += amount;
        }
    }   
        printf("Credited all accounts with %d\n", amount);
}

void debit(bank_t *bank, int amount) {
    for (size_t i = 0; i < bank->num_accounts; i++) {
        if (!bank->accounts[i].frozen && bank->accounts[i].balance - amount >= bank->accounts[i].min_balance) {
            bank->accounts[i].balance -= amount;
        }
    }
        printf("Debited all accounts with %d\n", amount);
}

void set_min_balance(bank_t *bank, size_t account_num, int min_balance) {
    if (account_num >= bank->num_accounts) {
        printf("Error: Invalid account number\n");
        return;
    }
    bank->accounts[account_num].min_balance = min_balance;
    printf("Set minimum balance of account %zu to %d\n", account_num, min_balance);
}

void set_max_balance(bank_t *bank, size_t account_num, int max_balance) {
    if (account_num >= bank->num_accounts) {
        printf("Error: Invalid account number\n");
        return;
    }
    bank->accounts[account_num].max_balance = max_balance;
    printf("Set maximum balance of account %zu to %d\n", account_num, max_balance);
}



