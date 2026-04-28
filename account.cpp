#include "Account.h"

Account::Account() {
    accountNumber = 0;
    accountHolderName = "Unknown";
    pin = 0;
    balance = 0.0;
}

Account::Account(int accNo, string name, int pinCode, double bal) {
    accountNumber = accNo;
    accountHolderName = name;
    pin = pinCode;
    balance = bal;
}

Account::~Account() {
}

int Account::getAccountNumber() const {
    return accountNumber;
}

string Account::getName() const {
    return accountHolderName;
}

double Account::getBalance() const {
    return balance;
}

bool Account::checkPin(int enteredPin) const {
    return pin == enteredPin;
}

void Account::deposit(double amount) {
    // TODO: check if amount is positive
    balance += amount;
}

void Account::withdraw(double amount) {
    // TODO: check if amount is positive and balance is enough
    balance -= amount;
}

void Account::displayAccount() const {
    cout << "Account Number: " << accountNumber << endl;
    cout << "Name: " << accountHolderName << endl;
    cout << "Balance: " << balance << endl;
}