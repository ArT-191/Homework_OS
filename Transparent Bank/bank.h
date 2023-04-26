#pragma once

#include <iostream>

struct Account {
    int current_balance;
    int min_balance;
    int max_balance;
    bool frozen;

    Account() : current_balance(0), min_balance(0), max_balance(0), frozen(false) {}

    Account(int cb, int mb, int xb) : current_balance(cb), min_balance(mb), max_balance(xb), frozen(false) {}

    friend std::ostream& operator<<(std::ostream& os, const Account& acc) {
        os << "Current Balance: " << acc.current_balance << " | ";
        os << "Min Balance: " << acc.min_balance << " | ";
        os << "Max Balance: " << acc.max_balance << " | ";
        os << (acc.frozen ? "Frozen" : "Not Frozen");
        return os;
    }
};

class Bank {
public:
    Bank(int num_accounts);
    ~Bank();

    Account* get_account(int acc_num);

    bool freeze_account(int acc_num);
    bool unfreeze_account(int acc_num);

    bool transfer_funds(int acc_num_from, int acc_num_to, int amount);

    void credit_all_accounts(int amount);
    void write_off_all_accounts(int amount);

    bool set_min_balance(int acc_num, int min_balance);
    bool set_max_balance(int acc_num, int max_balance);

private:
    Account* accounts_;
    int num_accounts_;
    int shmid_;
};
