#include <string>
using namespace std;

class BankException {
private:
    string message;

public:
    // Constructor
    BankException(string msg) {
        message = msg;
    }

    // Function to return error message
    string what() const {
        return message;
    }
};