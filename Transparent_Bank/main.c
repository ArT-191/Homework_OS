#include "bank.h"

int main() {
    bank_t *bank = create_bank(10, 10000);
    display_balance(bank, 5);
    set_min_balance(bank, 5, -5000);
    display_balance(bank, 5);
    set_max_balance(bank, 5, 20000);
    display_balance(bank, 5);
    credit(bank, 1000);
    display_balance(bank, 5);
    debit(bank, 500);
    display_balance(bank, 5);
    transfer(bank, 5, 3, 2000);
    display_balance(bank, 5);
    freeze_account(bank, 5);
    display_balance(bank, 5);
    unfreeze_account(bank, 5);
    display_balance(bank, 5);
    destroy_bank(bank);
    return 0;
}
