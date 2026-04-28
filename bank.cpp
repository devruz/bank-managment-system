#include "Bank.h"
#include "SavingsAccount.h"
#include "CurrentAccount.h"
#include <iostream>
#include <fstream>
using namespace std;

// Constructor
Bank::Bank() {}

// Destructor (free memory)
Bank::~Bank() {
    for (int i = 0; i < accounts.size(); i++) {
        delete accounts[i];
    }
}

// Find account by account number
Account* Bank::findAccount(int accNo) {
    for (int i = 0; i < accounts.size(); i++) {
        if (accounts[i]->getAccountNumber() == accNo) {
            return accounts[i];
        }
    }
    return nullptr;
}