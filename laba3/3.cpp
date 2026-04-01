#include <iostream>

using namespace std;

enum PaymentType {
    Cash,
    Card,
    BankTransfer
};

union PaymentDetails {
    char currency[10];
    char cardNumber[20];
    char iban[30];
};

struct Payment {
    int paymentID;
    double amount;
    PaymentType type;
    PaymentDetails details;
};

int main() {
    const int N = 3;
    Payment payments[N];

    int cashCount = 0, cardCount = 0, transferCount = 0;

    cout << "Enter payment data" << endl;
    for (int i = 0; i < N; i++) {
        cout << "\nPayment #" << i + 1 << endl;

        cout << "Payment ID: ";
        cin >> payments[i].paymentID;

        cout << "Amount: ";
        cin >> payments[i].amount;

        cout << "Payment type (0-Cash, 1-Card, 2-Transfer): ";
        int typeChoice;
        cin >> typeChoice;
        payments[i].type = (PaymentType) typeChoice;

        switch (payments[i].type) {
            case Cash:
                cout << "Enter currency: ";
                cin >> payments[i].details.currency;
                cashCount++;
                break;
            case Card:
                cout << "Enter card number: ";
                cin >> payments[i].details.cardNumber;
                cardCount++;
                break;
            case BankTransfer:
                cout << "Enter IBAN: ";
                cin >> payments[i].details.iban;
                transferCount++;
                break;
        }
    }

    cout << "\nPayment information" << endl;
    for (int i = 0; i < N; i++) {
        cout << "ID: " << payments[i].paymentID
                << " | Amount: " << payments[i].amount
                << " | Details: ";

        switch (payments[i].type) {
            case Cash:
                cout << "Cash, Currency: " << payments[i].details.currency << endl;
                break;
            case Card:
                cout << "Card, Number: " << payments[i].details.cardNumber << endl;
                break;
            case BankTransfer:
                cout << "Transfer, IBAN: " << payments[i].details.iban << endl;
                break;
        }
    }

    cout << "\nPayment statistics" << endl;
    cout << "Cash: " << cashCount << endl;
    cout << "Card: " << cardCount << endl;
    cout << "Bank transfer: " << transferCount << endl;

    return 0;
}
