#include <iostream>
#include <fstream>
#include "header1.h"
using namespace std;

// ================= ACCOUNT =================

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

Account::~Account() {}

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
    if (amount <= 0) {
        cout << "Invalid deposit amount!\n";
        return;
    }
    balance += amount;
}

void Account::withdraw(double amount) {
    if (amount <= 0) {
        cout << "Invalid withdraw amount!\n";
        return;
    }

    if (amount > balance) {
        cout << "Insufficient balance!\n";
        return;
    }

    balance -= amount;
}

void Account::displayAccount() const {
    cout << "Account Number: " << accountNumber << endl;
    cout << "Name: " << accountHolderName << endl;
    cout << "Balance: " << balance << endl;
}

// ================= SAVINGS ACCOUNT =================

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

// ================= CURRENT ACCOUNT =================

CurrentAccount::CurrentAccount() : Account() {
    overdraftLimit = 500.0;
}

CurrentAccount::CurrentAccount(int accNo, string name, int pinCode, double bal, double limit)
    : Account(accNo, name, pinCode, bal) {
    overdraftLimit = limit;
}

void CurrentAccount::withdraw(double amount) {
    if (amount <= 0) {
        cout << "Invalid withdraw amount!\n";
        return;
    }

    if (amount > balance + overdraftLimit) {
        cout << "Overdraft limit exceeded!\n";
        return;
    }

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

// ================= TRANSACTION =================

Transaction::Transaction() {
    transactionId = 0;
    accountNumber = 0;
    type = "Unknown";
    amount = 0.0;
    date = "Unknown";
}

Transaction::Transaction(int id, int accNo, string t, double amt, string d) {
    transactionId = id;
    accountNumber = accNo;
    type = t;
    amount = amt;
    date = d;
}

void Transaction::displayTransaction() const {
    cout << "Transaction ID: " << transactionId << endl;
    cout << "Account Number: " << accountNumber << endl;
    cout << "Type: " << type << endl;
    cout << "Amount: " << amount << endl;
    cout << "Date: " << date << endl;
}

// ================= BANK =================

Bank::Bank() {}

Bank::~Bank() {
    for (int i = 0; i < accounts.size(); i++) {
        delete accounts[i];
    }
}

Account* Bank::findAccount(int accNo) {
    for (int i = 0; i < accounts.size(); i++) {
        if (accounts[i]->getAccountNumber() == accNo) {
            return accounts[i];
        }
    }
    return nullptr;
}

void Bank::createAccount() {
    int accNo, pin, type;
    string name;
    double balance;

    cout << "Enter Account Number: ";
    cin >> accNo;

    if (findAccount(accNo) != nullptr) {
        cout << "Account already exists!\n";
        return;
    }

    cout << "Enter Name: ";
    cin >> name;

    cout << "Enter PIN: ";
    cin >> pin;

    cout << "Enter Balance: ";
    cin >> balance;

    cout << "1. Savings\n2. Current\nChoose type: ";
    cin >> type;

    if (type == 1) {
        accounts.push_back(new SavingsAccount(accNo, name, pin, balance, 0.05));
    }
    else if (type == 2) {
        accounts.push_back(new CurrentAccount(accNo, name, pin, balance, 500));
    }
    else {
        cout << "Invalid type!\n";
    }
}

void Bank::depositMoney() {
    int accNo;
    double amount;

    cout << "Enter Account Number: ";
    cin >> accNo;

    Account* acc = findAccount(accNo);

    if (acc == nullptr) {
        cout << "Account not found!\n";
        return;
    }

    cout << "Enter Amount: ";
    cin >> amount;

    acc->deposit(amount);
    cout << "Deposit completed!\n";
}

void Bank::withdrawMoney() {
    int accNo;
    double amount;

    cout << "Enter Account Number: ";
    cin >> accNo;

    Account* acc = findAccount(accNo);

    if (acc == nullptr) {
        cout << "Account not found!\n";
        return;
    }

    cout << "Enter Amount: ";
    cin >> amount;

    acc->withdraw(amount);
}

void Bank::transferMoney() {
    int fromAcc, toAcc;
    double amount;

    cout << "From Account: ";
    cin >> fromAcc;

    cout << "To Account: ";
    cin >> toAcc;

    cout << "Amount: ";
    cin >> amount;

    Account* sender = findAccount(fromAcc);
    Account* receiver = findAccount(toAcc);

    if (sender == nullptr || receiver == nullptr) {
        cout << "Account not found!\n";
        return;
    }

    sender->withdraw(amount);
    receiver->deposit(amount);

    cout << "Transfer completed!\n";
}

void Bank::displayAllAccounts() {
    if (accounts.empty()) {
        cout << "No accounts available!\n";
        return;
    }

    for (int i = 0; i < accounts.size(); i++) {
        cout << "\n-----------------\n";
        accounts[i]->displayAccount();
    }
}

void Bank::deleteAccount() {
    int accNo;
    cout << "Enter Account Number: ";
    cin >> accNo;

    for (int i = 0; i < accounts.size(); i++) {
        if (accounts[i]->getAccountNumber() == accNo) {
            delete accounts[i];
            accounts.erase(accounts.begin() + i);
            cout << "Account deleted!\n";
            return;
        }
    }

    cout << "Account not found!\n";
}

void Bank::checkBalance() {
    int accNo;
    cout << "Enter Account Number: ";
    cin >> accNo;

    Account* acc = findAccount(accNo);

    if (acc == nullptr) {
        cout << "Account not found!\n";
        return;
    }

    cout << "Balance: " << acc->getBalance() << endl;
}

void Bank::searchAccount() {
    int accNo;
    cout << "Enter Account Number: ";
    cin >> accNo;

    Account* acc = findAccount(accNo);

    if (acc == nullptr) {
        cout << "Account not found!\n";
        return;
    }

    acc->displayAccount();
}

void Bank::showTransactionHistory() {
    cout << "Transaction history is not added yet.\n";
}

void Bank::saveAccountsToFile() {
    ofstream file("accounts.txt");

    for (int i = 0; i < accounts.size(); i++) {
        file << accounts[i]->getAccountNumber() << " "
             << accounts[i]->getName() << " "
             << accounts[i]->getBalance() << endl;
    }

    file.close();
    cout << "Data saved successfully!\n";
}

void Bank::loadAccountsFromFile() {
    ifstream file("accounts.txt");

    int accNo;
    string name;
    double balance;

    while (file >> accNo >> name >> balance) {
        accounts.push_back(new SavingsAccount(accNo, name, 0, balance, 0.05));
    }

    file.close();
}

// ================= MAIN =================

int main() {
    Bank bank;
    int choice;

    bank.loadAccountsFromFile();

    do {
        cout << "\n========== BANK MANAGEMENT SYSTEM ==========\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Transfer Money\n";
        cout << "5. Check Balance\n";
        cout << "6. Search Account\n";
        cout << "7. Display All Accounts\n";
        cout << "8. Delete Account\n";
        cout << "9. Show Transaction History\n";
        cout << "10. Save Data to File\n";
        cout << "0. Exit\n";
        cout << "Choose option: ";
        cin >> choice;

        switch (choice) {
        case 1:
            bank.createAccount();
            break;
        case 2:
            bank.depositMoney();
            break;
        case 3:
            bank.withdrawMoney();
            break;
        case 4:
            bank.transferMoney();
            break;
        case 5:
            bank.checkBalance();
            break;
        case 6:
            bank.searchAccount();
            break;
        case 7:
            bank.displayAllAccounts();
            break;
        case 8:
            bank.deleteAccount();
            break;
        case 9:
            bank.showTransactionHistory();
            break;
        case 10:
            bank.saveAccountsToFile();
            break;
        case 0:
            bank.saveAccountsToFile();
            cout << "Thank you for using Bank Management System!\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }

    } while (choice != 0);

    return 0;
}