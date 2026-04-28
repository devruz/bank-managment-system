#include "Account.h"

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