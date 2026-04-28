#include "Bank.h"
#include "SavingsAccount.h"
#include "CurrentAccount.h"
#include <iostream>
#include <fstream>
using namespace std;

// Constructor
Bank::Bank() {}

// Destructor
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

    try {
        acc->deposit(amount);
        cout << "Deposit successful!\n";
    }
    catch (...) {
        cout << "Deposit failed!\n";
    }
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

    try {
        acc->withdraw(amount);
        cout << "Withdraw successful!\n";
    }
    catch (...) {
        cout << "Withdraw failed!\n";
    }
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

    try {
        sender->withdraw(amount);
        receiver->deposit(amount);
        cout << "Transfer successful!\n";
    }
    catch (...) {
        cout << "Transfer failed!\n";
    }
}   
void Bank::displayAllAccounts() {
    if (accounts.empty()) {
        cout << "No accounts available!\n";
        return;
    }

    for (int i = 0; i < accounts.size(); i++) {
        cout << "-----------------\n";
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

    int pin, type;

    while (file >> accNo >> name >> pin >> balance >> type) {
    if (type == 1) {
        accounts.push_back(new SavingsAccount(accNo, name, pin, balance, 0.05));
    } else {
        accounts.push_back(new CurrentAccount(accNo, name, pin, balance, 500));
    }
}

    file.close();
}