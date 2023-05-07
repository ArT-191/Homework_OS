#include "bank.h"
#include <cstdlib>
#include <iostream>

void run_client(bank_t *bank);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <num_accounts> <max_balance>" << std::endl;
        return EXIT_FAILURE;
    }

    size_t num_accounts = std::stoi(argv[1]);
    int max_balance = std::stoi(argv[2]);

    bank_t *bank = create_bank(num_accounts, max_balance);

    if (bank == NULL) {
        std::cerr << "Failed to create bank" << std::endl;
        return EXIT_FAILURE;
    }

    // call the client function
    run_client(bank);

    destroy_bank(bank);
    return EXIT_SUCCESS;
}
