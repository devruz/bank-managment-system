
#include <iostream>
#include <vector>
#include <string>

#include "Account.h"
#include "SavingsAccount.h"
#include "CurrentAccount.h"
#include "Transaction.h"
#include "Exception.h"

using namespace std;

class Bank {
private:
    vector<Account*> accounts;
    vector<Transaction> transactions;

public:
    // Constructor and Destructor
    Bank();
    ~Bank();

    // Account management
    void createAccount();
    void deleteAccount();
    void updateAccount();
    void searchAccount();
    void displayAllAccounts();

    // Helper function
    Account* findAccount(int accNo);

    // Banking operations
    void depositMoney();
    void withdrawMoney();
    void transferMoney();
    void checkBalance();

    // File handling
    void saveAccountsToFile();
    void loadAccountsFromFile();

    // Transaction handling
    void addTransaction(int accNo, string type, double amount);
    void showTransactionHistory();

    // Admin
    void adminPanel();
};
