#include "bank.h"
#include <stdlib.h>

void destroy_bank(bank_t *bank) {
    // Free memory used by account array
    for (size_t i = 0; i < bank->num_accounts; i++) {
        free(bank->accounts[i]);
    }
    free(bank->accounts);

    // Free memory used by bank structure
    free(bank);
}
