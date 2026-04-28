#include "SavingsAccount.h"

SavingsAccount::SavingsAccount() : Account() {
    interestRate = 0.05;
}

SavingsAccount::SavingsAccount(int accNo, string name, int pinCode, double bal, double rate)
    : Account(accNo, name, pinCode, bal) {
    interestRate = rate;
}

double SavingsAccount::calculateInterest() const {
    return balance * interestRate;
}

void SavingsAccount::displayAccount() const {
    Account::displayAccount();
    cout << "Account Type: Savings Account" << endl;
    cout << "Interest Rate: " << interestRate << endl;
}