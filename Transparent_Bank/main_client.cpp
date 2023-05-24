#include "bank.h"

bank_t *connect_bank();
void run_client(bank_t *bank);

int main() {
    bank* b = connect_bank();
    run_client(b);
}