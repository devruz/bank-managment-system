#include "Transaction.h"
#include <iostream>
using namespace std;

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