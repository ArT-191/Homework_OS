#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <windows.h>

class Account {
public:
    Account(int balance, int min_balance, int max_balance)
        : current_balance(balance),
          min_balance(min_balance),
          max_balance(max_balance),
          frozen(false) {}

    int current_balance;
    int min_balance;
    int max_balance;
    bool frozen;
};

class Bank {
public:
    Bank(int num_accounts, int min_balance, int max_balance)
        : num_accounts_(num_accounts) {
        accounts_ = new Account*[num_accounts_];
        for (int i = 0; i < num_accounts_; ++i) {
            accounts_[i] = new Account(0, min_balance, max_balance);
        }
    }

    ~Bank() {
        for (int i = 0; i < num_accounts_; ++i) {
            delete accounts_[i];
        }
        delete[] accounts_;
    }

    Account* get_account(int account) {
        return accounts_[account];
    }

    int get_num_accounts() {
        return num_accounts_;
    }

    bool freeze_account(int account) {
        if (account < 0 || account >= num_accounts_) {
            return false;
        }
        accounts_[account]->frozen = true;
        return true;
    }

    bool deposit(int account, int amount) {
        if (account < 0 || account >= num_accounts_) {
            return false;
        }
        if (accounts_[account]->frozen) {
            return false;
        }
        accounts_[account]->current_balance += amount;
        return true;
    }

    bool withdraw(int account, int amount) {
        if (account < 0 || account >= num_accounts_) {
            return false;
        }
        if (accounts_[account]->frozen) {
            return false;
        }
        if (accounts_[account]->current_balance - amount < accounts_[account]->min_balance) {
            return false;
        }
        accounts_[account]->current_balance -= amount;
        return true;
    }

    bool transfer(int account1, int account2, int amount) {
        if (account1 < 0 || account1 >= num_accounts_ || account2 < 0 || account2 >= num_accounts_) {
            return false;
        }
        if (accounts_[account1]->frozen || accounts_[account2]->frozen) {
            return false;
        }
        if (accounts_[account1]->current_balance - amount < accounts_[account1]->min_balance) {
            return false;
        }
        accounts_[account1]->current_balance -= amount;
        accounts_[account2]->current_balance += amount;
        return true;
    }

private:
    Account** accounts_;
    int num_accounts_;
};
