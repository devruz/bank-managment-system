#include "CurrentAccount.h"

CurrentAccount::CurrentAccount() : Account() {
    overdraftLimit = 500.0;
}

CurrentAccount::CurrentAccount(int accNo, string name, int pinCode, double bal, double limit)
    : Account(accNo, name, pinCode, bal) {
    overdraftLimit = limit;
}

void CurrentAccount::withdraw(double amount) {
    // TODO: allow withdrawal up to balance + overdraftLimit
    balance -= amount;
}

double CurrentAccount::calculateInterest() const {
    return 0.0;
}

void CurrentAccount::displayAccount() const {
    Account::displayAccount();
    cout << "Account Type: Current Account" << endl;
    cout << "Overdraft Limit: " << overdraftLimit << endl;
}