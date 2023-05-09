#include "bank.h"
#include <stdlib.h>

void destroy_bank(bank_t *bank) {
    // Free each account in the bank
    for (size_t i = 0; i < bank->num_accounts; i++) {
        free(&bank->accounts[i]);
    }

    // Free the array of accounts in the bank
    free(bank->accounts);

    // Free the bank itself
    free(bank);
}


