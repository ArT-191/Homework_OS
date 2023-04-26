#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <windows.h>
#include "bank.h"

int main() {
    // Get the shared memory handle.
    HANDLE hMapFile = CreateFileMapping(
        INVALID_HANDLE_VALUE,    // Use the page file.
        NULL,                    // Default security.
        PAGE_READWRITE,          // Read/write access.
        0,                       // Maximum object size (high-order DWORD).
        sizeof(Bank),            // Maximum object size (low-order DWORD).
        L"Local\\MyFileMappingObject"); // Name of the file mapping object.

    if (hMapFile == NULL) {
        std::cerr << "Error: cannot create shared memory handle" << std::endl;
        exit(1);
    }

    // Connect to the shared memory.
    Bank* bank = (Bank*) MapViewOfFile(
        hMapFile,         // Handle to the file mapping object.
        FILE_MAP_ALL_ACCESS, // Read/write access.
        0,
        0,
        sizeof(Bank));

    if (bank == NULL) {
        std::cerr << "Error: cannot connect to shared memory" << std::endl;
        exit(1);
    }

    // Process commands.
    char cmd;
    int account, account2, amount, min_balance, max_balance;
    while (std::cin >> cmd) {
        switch (cmd) {
            case 'D':
                // Display account balance.
                if (!(std::cin >> account)) {
                    std::cerr << "Error: invalid command" << std::endl;
                    continue;
                }
                if (account < 0 || account >= bank->get_num_accounts()) {
                    std::cerr << "Error: invalid account number" << std::endl;
                    continue;
                }
                std::cout << "Account " << account << " balance: " << bank->get_account(account)->current_balance << std::endl;
                break;

            case 'M':
                // Display account minimum balance.
                if (!(std::cin >> account)) {
                    std::cerr << "Error: invalid command" << std::endl;
                    continue;
                }
                if (account < 0 || account >= bank->num_accounts_) {
                    std::cerr << "Error: invalid account number" << std::endl;
                    continue;
                }
                std::cout << "Account " << account << " minimum balance: " << bank->get_account(account)->min_balance << std::endl;
                break;

            case 'X':
                // Display account maximum balance.
                if (!(std::cin >> account)) {
                    std::cerr << "Error: invalid command" << std::endl;
                    continue;
                }
                if (account < 0 || account >= bank->num_accounts_) {
                    std::cerr << "Error: invalid account number" << std::endl;
                    continue;
                }
                std::cout << "Account " << account << " maximum balance: " << bank->get_account(account)->max_balance << std::endl;
                break;

            case 'F':
                // Freeze account.
                if (!(std::cin >> account)) {
                    std::cerr << "Error: invalid command" << std::endl;
                    continue;
                }
                if (account < 0 || account >= bank->num_accounts_) {
                    std::cerr << "Error: invalid account number" << std::endl;
                    continue;
                }
                if (bank->freeze_account(account)) {
                    std::cout << "Account " << account << " frozen" << std::endl;
                    break;
            case 'U':
                // Unfreeze account.
                if (!(std::cin >> account)) {
                    std::cerr << "Error: invalid command" << std::endl;
                    continue;
                }
                if (account < 0 || account >= bank->num_accounts_) {
                    std::cerr << "Error: invalid account number" << std::endl;
                    continue;
                }
                if (bank->unfreeze_account(account)) {
                    std::cout << "Account " << account << " unfrozen" << std::endl;
                } else {
                    std::cerr << "Error: account is not frozen" << std::endl;
                       }
                break;
                        case 'T':
            // Transfer funds.
            if (!(std::cin >> account >> account2 >> amount)) {
                std::cerr << "Error: invalid command" << std::endl;
                continue;
            }
            if (account < 0 || account >= bank->num_accounts_ ||
                account2 < 0 || account2 >= bank->num_accounts_) {
                std::cerr << "Error: invalid account number" << std::endl;
                continue;
            }
            if (bank->transfer_funds(account, account2, amount)) {
                std::cout << "Transferred " << amount << " from account " << account << " to account " << account2 << std::endl;
            } else {
                std::cerr << "Error: transfer failed" << std::endl;
            }
            break;

        case 'C':
            // Credit all accounts.
            if (!(std::cin >> amount)) {
                std::cerr << "Error: invalid command" << std::endl;
                continue;
            }
            bank->credit_all_accounts(amount);
            std::cout << "Credited all accounts by " << amount << std::endl;
            break;

        case 'W':
            // Write off all accounts.
            if (!(std::cin >> amount)) {
                std::cerr << "Error: invalid command" << std::endl;
                continue;
            }
            bank->write_off_all_accounts(amount);
            std::cout << "Written off all accounts by " << amount << std::endl;
            break;

        case 'N':
            // Set minimum balance.
            if (!(std::cin >> account >> min_balance)) {
                std::cerr << "Error: invalid command" << std::endl;
                continue;
            }
            if (account < 0 || account >= bank->num_accounts_) {
                std::cerr << "Error: invalid account number" << std::endl;
                continue;
            }
            if (bank->set_min_balance(account, min_balance)) {
                std::cout << "Account " << account << " minimum balance set to " << min_balance << std::endl;
            } else {
                std::cerr << "Error: cannot set minimum balance" << std::endl;
            }
            break;

        case 'A':
            // Set maximum balance.
            if (!(std::cin >> account >> max_balance)) {
                std::cerr << "Error: invalid command" << std::endl;
                continue;
            }
            if (account < 0 || account >= bank->num_accounts_) {
                std::cerr << "Error: invalid account number" << std::endl;
                continue;
            }
            if (bank->set_max_balance(account, max_balance)) {
                std::cout << "Account " << account << " maximum balance set to " << max_balance << std::endl;
            } else {
                std::cerr << "Error: cannot set maximum balance" << std::endl;
            }
            break;


        default:
            std::cerr << "Error: invalid command" << std::endl;
            break;
    }
}

// Close the shared memory handle.
CloseHandle(hMapFile);
UnmapViewOfFile(bank);

return 0;
}
}
