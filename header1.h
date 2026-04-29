#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Account {
protected:
    int accountNumber;
    string accountHolderName;
    int pin;
    double balance;

public:
    Account();
    Account(int accNo, string name, int pinCode, double bal);
    virtual ~Account();

    int getAccountNumber() const;
    string getName() const;
    double getBalance() const;

    bool checkPin(int enteredPin) const;

    virtual void deposit(double amount);
    virtual void withdraw(double amount);
    virtual void displayAccount() const;

    virtual double calculateInterest() const = 0;
};

class SavingsAccount : public Account {
private:
    double interestRate;

public:
    SavingsAccount();
    SavingsAccount(int accNo, string name, int pinCode, double bal, double rate);

    double calculateInterest() const override;
    void displayAccount() const override;
};

class CurrentAccount : public Account {
private:
    double overdraftLimit;

public:
    CurrentAccount();
    CurrentAccount(int accNo, string name, int pinCode, double bal, double limit);

    void withdraw(double amount) override;
    double calculateInterest() const override;
    void displayAccount() const override;
};

class BankException {
private:
    string message;

public:
    BankException(string msg);
    string what() const;
};

class Transaction {
private:
    int transactionId;
    int accountNumber;
    string type;
    double amount;
    string date;

public:
    Transaction();
    Transaction(int id, int accNo, string t, double amt, string d);

    void displayTransaction() const;
};

class Bank {
private:
    vector<Account*> accounts;
    vector<Transaction> transactions;

public:
    Bank();
    ~Bank();

    Account* findAccount(int accNo);

    void createAccount();
    void depositMoney();
    void withdrawMoney();
    void transferMoney();
    void displayAllAccounts();
    void deleteAccount();

    void checkBalance();
    void searchAccount();
    void showTransactionHistory();

    void saveAccountsToFile();
    void loadAccountsFromFile();
};

#endif