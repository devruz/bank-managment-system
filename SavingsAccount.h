#include "Account.h"

class SavingsAccount : public Account {
private:
    double interestRate;

public:
    SavingsAccount();
    SavingsAccount(int accNo, string name, int pinCode, double bal, double rate);

    double calculateInterest() const override;
    void displayAccount() const override;
};