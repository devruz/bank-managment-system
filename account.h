#include <iostream>
#include <string>
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
