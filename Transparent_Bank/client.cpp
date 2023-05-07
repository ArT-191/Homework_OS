#include "bank.h"
#include <cstdlib>
#include <iostream>

void run_client(bank_t *bank) {
    int choice = 0;
    size_t account_num, to_account_num;
    int amount, min_balance, max_balance;

    while (true) {
        std::cout << "Choose an operation:\n";
        std::cout << "1. Display balance\n";
        std::cout << "2. Freeze account\n";
        std::cout << "3. Unfreeze account\n";
        std::cout << "4. Transfer\n";
        std::cout << "5. Credit\n";
        std::cout << "6. Debit\n";
        std::cout << "7. Set minimum balance\n";
        std::cout << "8. Set maximum balance\n";
        std::cout << "9. Quit\n";
        std::cout << "Enter choice: ";

        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter account number: ";
                std::cin >> account_num;
                display_balance(bank, account_num);
                break;
            case 2:
                std::cout << "Enter account number: ";
                std::cin >> account_num;
                freeze_account(bank, account_num);
                break;
            case 3:
                std::cout << "Enter account number: ";
                std::cin >> account_num;
                unfreeze_account(bank, account_num);
                break;
            case 4:
                std::cout << "Enter from account number: ";
                std::cin >> account_num;
                std::cout << "Enter to account number: ";
                std::cin >> to_account_num;
                std::cout << "Enter amount: ";
                std::cin >> amount;
                transfer(bank, account_num, to_account_num, amount);
                break;
            case 5:
                std::cout << "Enter account number: ";
                std::cin >> account_num;
                std::cout << "Enter amount: ";
                std::cin >> amount;
                credit(bank, amount);
                break;
            case 6:
                std::cout << "Enter account number: ";
                std::cin >> account_num;
                std::cout << "Enter amount: ";
                std::cin >> amount;
                debit(bank, amount);
                break;
            case 7:
                std::cout << "Enter account number: ";
                std::cin >> account_num;
                std::cout << "Enter minimum balance: ";
                std::cin >> min_balance;
                set_min_balance(bank, account_num, min_balance);
                break;
            case 8:
                std::cout << "Enter account number: ";
                std::cin >> account_num;
                std::cout << "Enter maximum balance: ";
                std::cin >> max_balance;
                set_max_balance(bank, account_num, max_balance);
                break;
            case 9:
                return;
            default:
                std::cout << "Invalid choice.\n";
        }
    }
}


