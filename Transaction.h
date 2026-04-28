#include <string>
using namespace std;

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
