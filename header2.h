#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

// ================= ACCOUNT =================

class Account {
protected:
    int accountNumber;
    string accountHolderName;
    int pin;
    double balance;

public:
    Account() {
        accountNumber = 0;
        accountHolderName = "Unknown";
        pin = 0;
        balance = 0.0;
    }

    Account(int accNo, string name, int pinCode, double bal) {
        accountNumber = accNo;
        accountHolderName = name;
        pin = pinCode;
        balance = bal;
    }

    virtual ~Account() {}

    int getAccountNumber() const {
        return accountNumber;
    }

    string getName() const {
        return accountHolderName;
    }

    double getBalance() const {
        return balance;
    }

    bool checkPin(int enteredPin) const {
        return pin == enteredPin;
    }

    virtual void deposit(double amount) {
        if (amount <= 0) {
            cout << "Invalid deposit amount!\n";
            return;
        }
        balance += amount;
    }

    virtual void withdraw(double amount) {
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

    virtual void displayAccount() const {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Name: " << accountHolderName << endl;
        cout << "Balance: " << balance << endl;
    }

    virtual double calculateInterest() const = 0;
};

// ================= SAVINGS ACCOUNT =================

class SavingsAccount : public Account {
private:
    double interestRate;

public:
    SavingsAccount() : Account() {
        interestRate = 0.05;
    }

    SavingsAccount(int accNo, string name, int pinCode, double bal, double rate)
        : Account(accNo, name, pinCode, bal) {
        interestRate = rate;
    }

    double calculateInterest() const override {
        return balance * interestRate;
    }

    void displayAccount() const override {
        Account::displayAccount();
        cout << "Account Type: Savings Account" << endl;
        cout << "Interest Rate: " << interestRate << endl;
    }
};

// ================= CURRENT ACCOUNT =================

class CurrentAccount : public Account {
private:
    double overdraftLimit;

public:
    CurrentAccount() : Account() {
        overdraftLimit = 500.0;
    }

    CurrentAccount(int accNo, string name, int pinCode, double bal, double limit)
        : Account(accNo, name, pinCode, bal) {
        overdraftLimit = limit;
    }

    void withdraw(double amount) override {
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

    double calculateInterest() const override {
        return 0.0;
    }

    void displayAccount() const override {
        Account::displayAccount();
        cout << "Account Type: Current Account" << endl;
        cout << "Overdraft Limit: " << overdraftLimit << endl;
    }
};

// ================= EXCEPTION =================

class BankException {
private:
    string message;

public:
    BankException(string msg) {
        message = msg;
    }

    string what() const {
        return message;
    }
};

// ================= TRANSACTION =================

class Transaction {
private:
    int transactionId;
    int accountNumber;
    string type;
    double amount;
    string date;

public:
    Transaction() {
        transactionId = 0;
        accountNumber = 0;
        type = "Unknown";
        amount = 0.0;
        date = "Unknown";
    }

    Transaction(int id, int accNo, string t, double amt, string d) {
        transactionId = id;
        accountNumber = accNo;
        type = t;
        amount = amt;
        date = d;
    }

    void displayTransaction() const {
        cout << "Transaction ID: " << transactionId << endl;
        cout << "Account Number: " << accountNumber << endl;
        cout << "Type: " << type << endl;
        cout << "Amount: " << amount << endl;
        cout << "Date: " << date << endl;
    }
};

// ================= BANK =================

class Bank {
private:
    vector<Account*> accounts;
    vector<Transaction> transactions;

public:
    Bank() {}

    ~Bank() {
        for (int i = 0; i < accounts.size(); i++) {
            delete accounts[i];
        }
    }

    Account* findAccount(int accNo) {
        for (int i = 0; i < accounts.size(); i++) {
            if (accounts[i]->getAccountNumber() == accNo) {
                return accounts[i];
            }
        }
        return nullptr;
    }

    void createAccount() {
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

    void depositMoney() {
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

    void withdrawMoney() {
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

    void transferMoney() {
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

    void displayAllAccounts() {
        if (accounts.empty()) {
            cout << "No accounts available!\n";
            return;
        }

        for (int i = 0; i < accounts.size(); i++) {
            cout << "\n-----------------\n";
            accounts[i]->displayAccount();
        }
    }

    void deleteAccount() {
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

    void checkBalance() {
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

    void searchAccount() {
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

    void showTransactionHistory() {
        cout << "Transaction history is not added yet.\n";
    }

    void saveAccountsToFile() {
        ofstream file("accounts.txt");

        for (int i = 0; i < accounts.size(); i++) {
            file << accounts[i]->getAccountNumber() << " "
                 << accounts[i]->getName() << " "
                 << accounts[i]->getBalance() << endl;
        }

        file.close();
        cout << "Data saved successfully!\n";
    }

    void loadAccountsFromFile() {
        ifstream file("accounts.txt");

        int accNo;
        string name;
        double balance;

        while (file >> accNo >> name >> balance) {
            accounts.push_back(new SavingsAccount(accNo, name, 0, balance, 0.05));
        }

        file.close();
    }
};
