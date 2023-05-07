#ifndef BANK_H
#define BANK_H

#include <stddef.h>

typedef struct account account_t;
typedef struct bank bank_t;

bank_t *create_bank(size_t num_accounts, int max_balance);
void destroy_bank(bank_t *bank);
void display_balance(const bank_t *bank, size_t account_num);
void freeze_account(bank_t *bank, size_t account_num);
void unfreeze_account(bank_t *bank, size_t account_num);
void transfer(bank_t *bank, size_t from_account_num, size_t to_account_num, int amount);
void credit(bank_t *bank, int amount);
void debit(bank_t *bank, int amount);
void set_min_balance(bank_t *bank, size_t account_num, int min_balance);
void set_max_balance(bank_t *bank, size_t account_num, int max_balance);

struct account {
    int balance;
    int min_balance;
    int max_balance;
    int frozen;
};

struct bank {
    size_t num_accounts;
    account_t *accounts;
};

#endif

