#include "header2.h"

int main() {
    Bank bank;
    int choice;

    bank.loadAccountsFromFile();

    do {
        cout << "\n========== BANK MANAGEMENT SYSTEM ==========\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Transfer Money\n";
        cout << "5. Check Balance\n";
        cout << "6. Search Account\n";
        cout << "7. Display All Accounts\n";
        cout << "8. Delete Account\n";
        cout << "9. Show Transaction History\n";
        cout << "10. Save Data to File\n";
        cout << "0. Exit\n";
        cout << "Choose option: ";
        cin >> choice;

        switch (choice) {
        case 1: bank.createAccount(); break;
        case 2: bank.depositMoney(); break;
        case 3: bank.withdrawMoney(); break;
        case 4: bank.transferMoney(); break;
        case 5: bank.checkBalance(); break;
        case 6: bank.searchAccount(); break;
        case 7: bank.displayAllAccounts(); break;
        case 8: bank.deleteAccount(); break;
        case 9: bank.showTransactionHistory(); break;
        case 10: bank.saveAccountsToFile(); break;
        case 0:
            bank.saveAccountsToFile();
            cout << "Thank you for using Bank Management System!\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }

    } while (choice != 0);

    return 0;
}