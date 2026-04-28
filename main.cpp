#include <iostream>
#include "SavingsAccount.h"
#include "CurrentAccount.h"
using namespace std;

int main() {
    SavingsAccount s1(1001, "Behruz", 1234, 1000.0, 0.05);
    CurrentAccount c1(2001, "Ali", 1111, 1500.0, 500.0);

    s1.displayAccount();
    cout << endl;

    c1.displayAccount();

    return 0;
}